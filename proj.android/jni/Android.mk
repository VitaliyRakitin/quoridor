LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/NetworkListener.cpp \
                   ../../Classes/UIAdapter.cpp \
                   ../../Classes/LogInScene.cpp \
                   ../../Classes/GameLogic.cpp \
                   ../../Classes/StartScene.cpp

MY_PHOTON_PATH = /home/grin/projects/technosfera/advcpp/quorridor/Photon-AndroidNDK-Sdk_v4-0-4-1/

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes $(MY_PHOTON_PATH)

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static photon-cpp-static-prebuilt common-cpp-static-prebuilt loadbalancing-cpp-static-prebuilt

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, /home/grin/bin/cocos2d-x-3.8.1/cocos/prebuilt-mk)
$(call import-module,.)

$(call import-add-path, $(MY_PHOTON_PATH)/Photon-cpp/lib)
$(call import-module, photon-cpp-prebuilt)

$(call import-add-path, $(MY_PHOTON_PATH)/Common-cpp/lib)
$(call import-module, common-cpp-prebuilt)

$(call import-add-path, $(MY_PHOTON_PATH)/LoadBalancing-cpp/lib)
$(call import-module, loadbalancing-cpp-prebuilt)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
