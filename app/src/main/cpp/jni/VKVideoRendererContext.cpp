
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:17.
 * Mail: alanwang4523@gmail.com
 */
#include "VKVideoRendererContext.h"
#include "utils/Log.h"

VKVideoRendererContext::jni_fields_t VKVideoRendererContext::jni_fields = { 0L };

VKVideoRendererContext::VKVideoRendererContext(int type)
{
    mVKVideoRenderer = VideoRenderer::create(type);
}

VKVideoRendererContext::~VKVideoRendererContext()
{

}

void VKVideoRendererContext::init(ANativeWindow* window, size_t width, size_t height,AAssetManager* manager)
{
    mVKVideoRenderer->init(window, width, height,manager);
}

void VKVideoRendererContext::render()
{
    mVKVideoRenderer->render();
}

void VKVideoRendererContext::draw(uint8_t *buffer, size_t length, size_t width, size_t height, int rotation)
{
    mVKVideoRenderer->draw(buffer, length, width, height, rotation);
}

void VKVideoRendererContext::setParameters(uint32_t params)
{
    mVKVideoRenderer->setParameters(params);
}

uint32_t VKVideoRendererContext::getParameters()
{
    return mVKVideoRenderer->getParameters();
}

void VKVideoRendererContext::createContext(JNIEnv *env, jobject obj, jint type)
{
    VKVideoRendererContext* context = new VKVideoRendererContext(type);

    storeContext(env, obj, context);
}

void VKVideoRendererContext::storeContext(JNIEnv *env, jobject obj, VKVideoRendererContext *context)
{
    // Get a reference to this object's class
    jclass cls = env->GetObjectClass(obj);

    if (NULL == cls)
    {
        LOGE("Could not find com/alanwang4523/a4vulkancamera/render/VideoRenderer.");
        return;
    }

    // Get the Field ID of the "mNativeContext" variable
    jni_fields.context = env->GetFieldID(cls, "mNativeContext", "J");
    if (NULL == jni_fields.context)
    {
        LOGE("Could not find mNativeContext.");
        return;
    }

    env->SetLongField(obj, jni_fields.context, (jlong)context);
}

void VKVideoRendererContext::deleteContext(JNIEnv *env, jobject obj)
{
    if (NULL == jni_fields.context)
    {
        LOGE("Could not find mNativeContext.");
        return;
    }

    VKVideoRendererContext* context = reinterpret_cast<VKVideoRendererContext*>(env->GetLongField(obj, jni_fields.context));

    if (context) delete context;

    env->SetLongField(obj, jni_fields.context, 0L);
}

VKVideoRendererContext* VKVideoRendererContext::getContext(JNIEnv *env, jobject obj)
{
    if (NULL == jni_fields.context)
    {
        LOGE("Could not find mNativeContext.");
        return NULL;
    }

    VKVideoRendererContext* context = reinterpret_cast<VKVideoRendererContext*>(env->GetLongField(obj, jni_fields.context));

    return context;
}

void VKVideoRendererContext::setProcess(uint32_t params) {
    mVKVideoRenderer->setProcess(params);
}
