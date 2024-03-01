
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:08.
 * Mail: alanwang4523@gmail.com
 */
#include "VKVideoRenderJNI.h"
#include "VKVideoRendererContext.h"
#include <android/native_window_jni.h>
#include "utils/Log.h"

JNIMETHOD(void, create)(JNIEnv * env, jobject obj, jint type)
{
    LOGE("create");
    VKVideoRendererContext::createContext(env, obj, type);
}

JNIMETHOD(void, destroy)(JNIEnv * env, jobject obj)
{
    LOGE("destroy");
    VKVideoRendererContext::deleteContext(env, obj);
}

JNIMETHOD(void, init)(JNIEnv * env, jobject obj, jobject surface, jint width, jint height,jobject assetManager)
{
    LOGE("init");
    VKVideoRendererContext* context = VKVideoRendererContext::getContext(env, obj);

    ANativeWindow *window = surface ? ANativeWindow_fromSurface(env, surface) : nullptr;

    AAssetManager*manager = AAssetManager_fromJava(env,assetManager);

    if (context) context->init(window, (size_t)width, (size_t)height, manager);
}

JNIMETHOD(void, render)(JNIEnv * env, jobject obj)
{
    LOGE("render");
    VKVideoRendererContext* context = VKVideoRendererContext::getContext(env, obj);

    if (context) context->render();
}

JNIMETHOD(void, draw)(JNIEnv * env, jobject obj, jbyteArray data, jint width, jint height, jint rotation)
{
//	LOGE("draw");
    jbyte* bufferPtr = env->GetByteArrayElements(data, 0);

    jsize arrayLength = env->GetArrayLength(data);

    VKVideoRendererContext* context = VKVideoRendererContext::getContext(env, obj);

    if (context) context->draw((uint8_t *)bufferPtr, (size_t)arrayLength, (size_t)width, (size_t)height, rotation);

    env->ReleaseByteArrayElements(data, bufferPtr, 0);
}

JNIMETHOD(void, setParameters)(JNIEnv * env, jobject obj, jint params)
{
    LOGE("setParameters");
    VKVideoRendererContext* context = VKVideoRendererContext::getContext(env, obj);

    if (context) context->setParameters((uint32_t)params);
}

JNIMETHOD(void, setProgress)(JNIEnv * env, jobject obj, jint params)
{
    LOGE("setParameters");
    VKVideoRendererContext* context = VKVideoRendererContext::getContext(env, obj);

    if (context) context->setProcess((uint32_t)params);
}

JNIMETHOD(jint, getParameters)(JNIEnv * env, jobject obj)
{
LOGE("getParameters");
VKVideoRendererContext* context = VKVideoRendererContext::getContext(env, obj);

if (context) return context->getParameters();

return 0;
}
