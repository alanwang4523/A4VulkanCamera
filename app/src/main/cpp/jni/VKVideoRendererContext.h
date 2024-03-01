
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:17.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKVIDEORENDERERCONTEXT_H
#define A4VULKANCAMERA_VKVIDEORENDERERCONTEXT_H

//#include "VideoRenderer.h"

#include <memory>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_window.h>

class VKVideoRendererContext {
public:
    struct jni_fields_t
    {
        jfieldID context;
    };

    VKVideoRendererContext(int type);
    ~VKVideoRendererContext();

    void init(ANativeWindow* window, size_t width, size_t height,AAssetManager* manager);
    void render();
    void draw(uint8_t *buffer, size_t length, size_t width, size_t height, int rotation);
    void setParameters(uint32_t params);
    void setProcess(uint32_t params);
    uint32_t getParameters();

    static void createContext(JNIEnv *env, jobject obj, jint type);
    static void storeContext(JNIEnv *env, jobject obj, VKVideoRendererContext *context);
    static void deleteContext(JNIEnv *env, jobject obj);
    static VKVideoRendererContext* getContext(JNIEnv *env, jobject obj);

    AAssetManager* manager ;

private:
    std::unique_ptr<VKVideoRenderer> mVKVideoRenderer;

    static jni_fields_t jni_fields;

};


#endif //A4VULKANCAMERA_VKVIDEORENDERERCONTEXT_H
