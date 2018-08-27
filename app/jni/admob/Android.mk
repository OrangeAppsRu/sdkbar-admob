LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := firebase
ifeq ($(APP_STL), c++_static)
    LOCAL_SRC_FILES := libs_c++_static/$(TARGET_ARCH_ABI)/libapp.a
else
    LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libapp.a
endif
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := admob
ifeq ($(APP_STL), c++_static)
    LOCAL_SRC_FILES := libs_c++_static/$(TARGET_ARCH_ABI)/libadmob.a
else
    LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libadmob.a
endif
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := remote_config
ifeq ($(APP_STL), c++_static)
    LOCAL_SRC_FILES := libs_c++_static/$(TARGET_ARCH_ABI)/libremote_config.a
else
    LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libremote_config.a
endif
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)

