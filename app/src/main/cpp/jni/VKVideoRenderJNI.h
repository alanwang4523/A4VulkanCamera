
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:08.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKVIDEORENDERJNI_H
#define A4VULKANCAMERA_VKVIDEORENDERJNI_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JNIMETHOD(rettype, name)                                             \
  rettype JNIEXPORT JNICALL Java_com_alanwang4523_a4vulkancamera_render_VKVideoRenderer_##name

JNIMETHOD(void, nativeCreate)(JNIEnv * env, jobject obj);
JNIMETHOD(void, nativeDestroy)(JNIEnv * env, jobject obj);
JNIMETHOD(void, nativeInit)(JNIEnv * env, jobject obj, jobject surface, jint width, jint height,jobject);
JNIMETHOD(void, nativeDraw)(JNIEnv * env, jobject obj, jbyteArray data, jint width, jint height, jint rotation);
JNIMETHOD(void, nativeSetFilterType)(JNIEnv * env, jobject obj, jint filterType);
JNIMETHOD(void, nativeSetProgress)(JNIEnv * env, jobject obj, jint params);

#ifdef __cplusplus
}
#endif


#endif //A4VULKANCAMERA_VKVIDEORENDERJNI_H
