
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:08.
 * Mail: alanwang4523@gmail.com
 */

#include <android/native_window_jni.h>
#include "utils/Log.h"
#include "VKVideoRenderJNI.h"
#include "engine/VKVideoRenderer.h"

struct fields_st {
    jfieldID context;
};
static fields_st gFields;

JNIMETHOD(void, nativeCreate)(JNIEnv * env, jobject obj)
{
    LOGE("nativeCreate");
    jclass cls = env->GetObjectClass(obj);
    if (NULL == cls) {
        LOGE("Could not find com/alanwang4523/a4vulkancamera/render/VKVideoRenderer.");
        return;
    }
    gFields.context = env->GetFieldID(cls, "mNativeContext", "J");
    if (NULL == gFields.context) {
        LOGE("Could not find mNativeContext.");
        return;
    }
    auto * vkVideoRenderer = new VKVideoRenderer();
    env->SetLongField(obj, gFields.context, (jlong)vkVideoRenderer);
}

JNIMETHOD(void, nativeDestroy)(JNIEnv * env, jobject obj)
{
    LOGE("nativeDestroy");
    auto * vkVideoRenderer = (VKVideoRenderer *)env->GetLongField(obj, gFields.context);
    if (vkVideoRenderer) {
        delete vkVideoRenderer;
    }
    env->SetLongField(obj, gFields.context, (jlong)0);
}

JNIMETHOD(void, nativeInit)(JNIEnv * env, jobject obj, jobject surface, jint width, jint height,jobject assetManager)
{
    LOGE("nativeInit");
    auto * vkVideoRenderer = (VKVideoRenderer *)env->GetLongField(obj, gFields.context);

    ANativeWindow *window = surface ? ANativeWindow_fromSurface(env, surface) : nullptr;
    AAssetManager *manager = AAssetManager_fromJava(env,assetManager);

    if (vkVideoRenderer) {
        vkVideoRenderer->init(window, (size_t)width, (size_t)height, manager);
    }
}

JNIMETHOD(void, nativeDraw)(JNIEnv * env, jobject obj, jbyteArray data, jint width, jint height, jint rotation)
{
    jbyte* bufferPtr = env->GetByteArrayElements(data, nullptr);
    jsize arrayLength = env->GetArrayLength(data);

    auto * vkVideoRenderer = (VKVideoRenderer *)env->GetLongField(obj, gFields.context);
    if (vkVideoRenderer) {
        vkVideoRenderer->draw((uint8_t *)bufferPtr, (size_t)arrayLength, (size_t)width, (size_t)height, rotation);
    }

    env->ReleaseByteArrayElements(data, bufferPtr, 0);
}

JNIMETHOD(void, nativeSetFilterType)(JNIEnv * env, jobject obj, jint filterType)
{
    LOGE("nativeSetFilterType");
    auto * vkVideoRenderer = (VKVideoRenderer *)env->GetLongField(obj, gFields.context);
    if (vkVideoRenderer) {
        vkVideoRenderer->setFilterType(filterType);
    }
}

JNIMETHOD(void, nativeSetProgress)(JNIEnv * env, jobject obj, jint params)
{
    LOGE("nativeSetProgress");
    auto* vkVideoRenderer = (VKVideoRenderer *)env->GetLongField(obj, gFields.context);
    if (vkVideoRenderer) {
        vkVideoRenderer->setProcess(params);
    }
}
