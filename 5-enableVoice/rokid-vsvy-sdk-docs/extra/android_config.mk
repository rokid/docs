LOCAL_PATH := $(call my-dir)

$(shell mkdir -p $(TARGET_OUT))
$(shell cp -r $(LOCAL_PATH)/workdir_asr_cn $(TARGET_OUT)/)
