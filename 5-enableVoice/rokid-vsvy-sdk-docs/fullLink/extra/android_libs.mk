LOCAL_PATH := $(call my-dir)

ifeq ($(TARGET_ARCH),arm64)
    $(shell mkdir -p $(TARGET_OUT)/lib64)
    $(shell cp -r $(LOCAL_PATH)/arm64-v8a/ $(TARGET_OUT)/lib64)
else
    $(shell mkdir -p $(TARGET_OUT)/lib)
    $(shell cp -r $(LOCAL_PATH)/armeabi-v7a/* $(TARGET_OUT)/lib)
endif
