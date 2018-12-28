/*************************************************************************
	> File Name: mic_array.h
	> Author: 
	> Mail: 
	> Created Time: Mon May  4 14:19:38 2015
 ************************************************************************/

#ifndef ANDROID_MIC_ARRAY_H
#define ANDROID_MIC_ARRAY_H

#include <stdint.h>
#include <hardware/hardware.h>

__BEGIN_DECLS

#define MIC_ARRAY_HARDWARE_MODULE_ID "mic_array"

struct mic_array_module_t {
    struct hw_module_t common;
};

struct mic_array_device_t {
    struct hw_device_t common;
    int channels;
    int sample_rate;
    int bit;
    unsigned int frame_cnt;
    struct pcm *pcm;


    int (*get_stream_buff_size) (struct mic_array_device_t *dev);
    int (*start_stream) (struct mic_array_device_t *dev);
    int (*stop_stream) (struct mic_array_device_t *dev);
    int (*finish_stream) (struct mic_array_device_t * dev);
    int (*resume_stream) (struct mic_array_device_t *dev);
    int (*read_stream) (struct mic_array_device_t *dev, char *buff, unsigned int frame_cnt);
    int (*config_stream) (struct mic_array_device_t *dev, int cmd, char *cmd_buff);
};
__END_DECLS
#endif
