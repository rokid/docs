LOCAL_PATH := $(call my-dir)

$(shell mkdir -p $(TARGET_OUT)/bin)
$(shell cp $(LOCAL_PATH)/turenproc $(TARGET_OUT)/bin)
