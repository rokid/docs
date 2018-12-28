/*************************************************************************
        > File Name: mic_array.c
        > Author:
        > Mail:
        > Created Time: Mon May  4 14:22:33 2015
 ************************************************************************/
#define LOG_TAG "mic_array"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <hardware/hardware.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <string.h>
#include <errno.h>
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <cutils/properties.h>

#include <time.h>
#include <tinyalsa/asoundlib.h>
#include <system/audio.h>
#include <hardware/audio.h>

#include "r2hw/mic_array.h"

#define MODULE_NAME "mic_array"
#define MODULE_AUTHOR "jiaqi@rokid.com"

#define MIC_CHANNEL 8
#define MIC_SAMPLE_RATE 48000

#define PCM_CARD 0
#define PCM_DEVICE 0

static struct pcm_config pcm_config_in = {
    .channels = MIC_CHANNEL,
    .rate = MIC_SAMPLE_RATE,
    .period_size = 1024,
    .period_count = 8,
    .format = PCM_FORMAT_S32_LE,
};

static struct pcm_config pcm_config_iis = {
    .channels = MIC_CHANNEL,
    .rate = MIC_SAMPLE_RATE,
    .period_size = 480,
    .period_count = 8,
    .format = PCM_FORMAT_S24_LE,
};

static struct pcm_config pcm_config_xmos = {
    .channels = MIC_CHANNEL,
    .rate = MIC_SAMPLE_RATE,
    .period_size = 1024,
    .period_count = 8,
    .format = PCM_FORMAT_S32_LE,
};

static struct mic_array_device_ex {
    struct mic_array_device_t mic_array;

    int pts;
    char* buffer;
};

static int mic_array_device_open(const struct hw_module_t* module,
    const char* name, struct hw_device_t** device);

static int mic_array_device_close(struct hw_device_t* device);

static int mic_array_device_start_stream(struct mic_array_device_t* dev);

static int mic_array_device_stop_stream(struct mic_array_device_t* dev);

static int mic_array_device_finish_stream(struct mic_array_device_t* dev);

static int mic_array_device_read_stream(
    struct mic_array_device_t* dev, char* buff, unsigned int frame_cnt);

static int mic_array_device_config_stream(
    struct mic_array_device_t* dev, int cmd, char* cmd_buff);

static int mic_array_device_get_stream_buff_size(
    struct mic_array_device_t* dev);

static int mic_array_device_resume_stream(struct mic_array_device_t* dev);

static struct hw_module_methods_t mic_array_module_methods = {
    .open = mic_array_device_open,
};

static int debug_fd = 0;

static int mic_timeout_count = 0;

static pthread_t log_th;
struct mic_array_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .version_major = 1,
        .version_minor = 0,
        .id = MIC_ARRAY_HARDWARE_MODULE_ID,
        .name = MODULE_NAME,
        .author = MODULE_AUTHOR,
        .methods = &mic_array_module_methods,
    },
};

int find_snd(const char* snd)
{
    char* path = "/proc/asound/cards";
    FILE* fs;
    char buf[4096];
    char *b, *e;
    int card = -1;
    int len;

    if (!(fs = fopen(path, "r"))) {
        ALOGE("%s  :  %s", __FUNCTION__, strerror(errno));
        return errno;
    }

    len = fread(buf, 1, sizeof(buf) - 1, fs);
    buf[len - 1] = '\0';
    fclose(fs);

    b = buf;
    while (e = strchr(b, '\n')) {
        *e = '\0';
        if (strstr(b, snd)) {
            card = atoi(b);
            break;
        }
        b = e + 1;
    }
    ALOGI("find -> %d", card);
    return card;
}

static void tinymix_set_value(struct mixer* mixer, const char* control,
    char** values, unsigned int num_values)
{
    struct mixer_ctl* ctl;
    enum mixer_ctl_type type;
    unsigned int num_ctl_values;
    unsigned int i;

    if (isdigit(control[0]))
        ctl = mixer_get_ctl(mixer, atoi(control));
    else
        ctl = mixer_get_ctl_by_name(mixer, control);

    if (!ctl) {
        ALOGE("Invalid mixer control\n");
        return;
    }

    type = mixer_ctl_get_type(ctl);
    num_ctl_values = mixer_ctl_get_num_values(ctl);

    if (isdigit(values[0][0])) {
        if (num_values == 1) {
            /* Set all values the same */
            int value = atoi(values[0]);

            for (i = 0; i < num_ctl_values; i++) {
                if (mixer_ctl_set_value(ctl, i, value)) {
                    ALOGE("Error: invalid value  %s\n", strerror(errno));
                    return;
                }
            }
        } else {
            /* Set multiple values */
            if (num_values > num_ctl_values) {
                ALOGE("Error: %d values given, but control only takes %d\n",
                    num_values, num_ctl_values);
                return;
            }
            for (i = 0; i < num_values; i++) {
                if (mixer_ctl_set_value(ctl, i, atoi(values[i]))) {
                    ALOGE("Error: invalid value for index %d\n", i);
                    return;
                }
            }
        }
    } else {
        if (type == MIXER_CTL_TYPE_ENUM) {
            if (num_values != 1) {
                ALOGE("Enclose strings in quotes and try again\n");
                return;
            }
            if (mixer_ctl_set_enum_by_string(ctl, values[0]))
                ALOGE("Error: invalid enum value\n");
        } else {
            ALOGE("Error: only enum types can be set with strings\n");
        }
    }
}

static int mic_array_device_open(const struct hw_module_t* module,
    const char* name, struct hw_device_t** device)
{
    int i = 0;
    char value[PROPERTY_VALUE_MAX];
    struct mic_array_device_ex* dev_ex = NULL;
    struct mic_array_device_t* dev = NULL;
    dev_ex = (struct mic_array_device_ex*)malloc(
        sizeof(struct mic_array_device_ex));
    dev = (struct mic_array_device_t*)dev_ex;

    if (!dev_ex) {
        ALOGE("MIC_ARRAY: FAILED TO ALLOC SPACE");
        return -1;
    }

    memset(dev, 0, sizeof(struct mic_array_device_ex));
    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (hw_module_t*)module;
    dev->common.close = mic_array_device_close;
    dev->start_stream = mic_array_device_start_stream;
    dev->stop_stream = mic_array_device_stop_stream;
    dev->finish_stream = mic_array_device_finish_stream;
    dev->resume_stream = mic_array_device_resume_stream;
    dev->read_stream = mic_array_device_read_stream;
    dev->config_stream = mic_array_device_config_stream;
    dev->get_stream_buff_size = mic_array_device_get_stream_buff_size;

    dev->channels = MIC_CHANNEL;
    dev->sample_rate = MIC_SAMPLE_RATE;
    dev->bit = pcm_format_to_bits(pcm_config_in.format);
    dev->pcm = NULL;
    *device = &(dev->common);
    return 0;
}

static void resetBuffer(struct mic_array_device_ex* dev) { dev->pts = 0; }

static int mic_array_device_close(struct hw_device_t* device)
{
    ALOGI("pcm close");

    struct mic_array_device_t* mic_array_device
        = (struct mic_array_device_t*)device;
    struct mic_array_device_ex* dev_ex
        = (struct mic_array_device_ex*)mic_array_device;

    if (dev_ex != NULL) {
        free(dev_ex->buffer);
        free(mic_array_device);
        mic_array_device = NULL;
        dev_ex = NULL;
    }
    return 0;
}

static int mic_array_device_start_stream(struct mic_array_device_t* dev)
{
    char value[PROPERTY_VALUE_MAX];
    struct mixer* mixer;
    char** values = "1";
    int card = PCM_CARD;
    struct pcm* pcm = NULL;
    struct mic_array_device_ex* dev_ex = (struct mic_array_device_t*)dev;

    //qualcom pebble xCORE is Xmos, value == 1
    //qualcom pebble msm8974-taiko-m is iis, value == 0
    //amlogic pebble-c AML-M8AUDIO, no value
    property_get("ro.boardinfo.usbaudio", value, "x");
    ALOGE("[stupid_FSC]mic_array_device_start_stream - begin");

	if (dev->pcm != NULL && pcm_is_ready(dev->pcm)) {
	    ALOGE("[stupid_FSC]mic_array_device_start_stream, not closed");
        //mic_array_device_stop_stream(dev)
	    return 0;
	}

    if (strcmp(value, "1") == 0) {
        //qualcom pebble xmos version
        card = find_snd("xCORE");
        if (card  < 0) {
            ALOGE("Can't find qualcom xmos sound card");
            return -1;
        } else {
            ALOGI("find qualcom xmos card with %d", card);
        }
        pcm = pcm_open (card, PCM_DEVICE, PCM_IN, &pcm_config_xmos);
    } else if (strcmp(value, "0") == 0) {
        //qualcom pebble iis version
        card = find_snd("msm8974-taiko-m");
        if (card < 0) {
            ALOGE("Can't find qualcom iis sound card");
            return -1;
        } else {
            ALOGI("find qualcom iis card with %d", card);
        }
        mixer = mixer_open(card);
        if (!mixer) {
            ALOGE("Failed to open mixer +++%s\n", strerror(errno));
            return -1; 
        }
        tinymix_set_value(mixer, "MultiMedia1 Mixer QUAT_MI2S_TX", &values, 1);
        mixer_close(mixer);
        pcm = pcm_open(card, PCM_DEVICE, PCM_IN, &pcm_config_iis);
    } else {
        //amlogic pebble-c iis direct link cpu
        card = find_snd("AML-M8AUDIO");
        if (card < 0) {
            ALOGE("Can't find amlogic iis sound card");
            return -1;
        } else {
            ALOGI("find amlogic iis card with %d", card);
        }
        pcm = pcm_open(card, PCM_DEVICE, PCM_IN, &pcm_config_in);
    }
    
    if (pcm == NULL && !pcm_is_ready(pcm)) {
        ALOGE("pcm open failed");
        if (pcm != NULL) {
            pcm_close(pcm);
            ALOGE("[stupidi_FSC]pcm open failed and pcm_close!");
            dev->pcm = NULL;
        }
        return -1;
    }
    
    dev->pcm = pcm;
    dev->frame_cnt = pcm_frames_to_bytes(pcm, pcm_get_buffer_size(pcm));
    ALOGI("alloc frame buffer size %d", dev->frame_cnt);
    dev_ex->buffer = (char*)malloc(dev->frame_cnt);
    return 0;
}

static int mic_array_device_stop_stream(struct mic_array_device_t* dev)
{
    struct mic_array_device_ex* dev_ex = (struct mic_array_device_t*)dev;
    if (dev->pcm != NULL) {
        pcm_close(dev->pcm);
        dev->pcm = NULL;
        dev->frame_cnt = 0;
        free(dev_ex->buffer);
        dev_ex->buffer = NULL;
        dev_ex->pts = 0;
    }
    return 0;
}

static int mic_array_device_finish_stream(struct mic_array_device_t* dev)
{
    ALOGE("finish stream is no use");
    return -1;
}

static int read_frame(struct mic_array_device_t* dev, char* buffer)
{
    return pcm_read(dev->pcm, buffer, dev->frame_cnt);
}

static int read_left_frame(
    struct mic_array_device_ex* dev, char* buff, int left)
{
    int ret = 0;
    if (dev->pts == 0) {
        if ((ret = read_frame(dev, dev->buffer)) != 0) {
            ALOGE("read_frame %s", strerror(errno));
            resetBuffer(dev);
            return ret;
        }
        memcpy(buff, dev->buffer, left);
        memcpy(
            dev->buffer, dev->buffer + left, dev->mic_array.frame_cnt - left);
        dev->pts = dev->mic_array.frame_cnt - left;
    } else {
        if (dev->pts >= left) {
            memcpy(buff, dev->buffer, left);
            dev->pts -= left;
            if (dev->pts != 0) {
                memcpy(dev->buffer, dev->buffer + left, dev->pts);
            }
        } else {
            memcpy(buff, dev->buffer, dev->pts);
            left -= dev->pts;
            if ((ret = read_frame(dev, dev->buffer)) != 0) {
                ALOGE("read_frame %s", strerror(errno));
                resetBuffer(dev);
                return ret;
            }
            memcpy(buff + dev->pts, dev->buffer, left);
            memcpy(dev->buffer, dev->buffer + left,
                dev->mic_array.frame_cnt - left);
            dev->pts = dev->mic_array.frame_cnt - left;
        }
    }
    return 0;
}

static int mic_array_device_read_stream(
    struct mic_array_device_t* dev, char* buff, unsigned int frame_cnt)
{
    struct pcm* pcm = dev->pcm;
    struct mic_array_device_ex* dev_ex = (struct mic_array_device_ex*)dev;
    char* target = NULL;

    int ret = 0;
    int left = 0;
    int size = dev->frame_cnt;
    if (size <= 0) {
        ALOGE("frame cnt lt 0");
        return -1;
    }

    if (buff == NULL) {
        ALOGE("null buffer");
        return -1;
    }

    if (frame_cnt >= size) {
        int cnt = frame_cnt / size;
        int i;
        left = frame_cnt % size;

        if (dev_ex->pts > left) {
            --cnt;
        }
        if (dev_ex->pts > 0) {
            memcpy(buff, dev_ex->buffer, dev_ex->pts);
        }

        for (i = 0; i < cnt; i++) {
            if ((ret = read_frame(dev, buff + dev_ex->pts + i * size)) != 0) {
                ALOGE("read_frame %s", strerror(errno));
                resetBuffer(dev_ex);
                return ret;
            }
        }
        if (frame_cnt - (dev_ex->pts + cnt * size) == 0) {
            dev_ex->pts = 0;
            return ret;
        }
        //		ALOGE("-------------------cnt : %d, left : %d, cache :
        //%d, frame_cnt : %d", cnt, left, dev_ex->pts, frame_cnt);
        target = buff + dev_ex->pts + cnt * size;
        left = frame_cnt - (dev_ex->pts + cnt * size);
        dev_ex->pts = 0;
    } else {
        target = buff;
        left = frame_cnt;
    }

    if ((ret = read_left_frame(dev_ex, target, left)) != 0) {
        ALOGE("read frame return %d, pcm read error", ret);
        resetBuffer(dev_ex);
        return ret;
    }

    return ret;
}

static int mic_array_device_config_stream(
    struct mic_array_device_t* dev, int cmd, char* cmd_buff)
{
    return -1;
}

static int mic_array_device_get_stream_buff_size(
    struct mic_array_device_t* dev)
{
    return dev->frame_cnt;
}

static int mic_array_device_resume_stream(struct mic_array_device_t* dev)
{
    ALOGI("not implmentation");
    return -1;
}
