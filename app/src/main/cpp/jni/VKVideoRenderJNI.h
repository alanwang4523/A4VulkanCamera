
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
  rettype JNIEXPORT JNICALL Java_com_alanwang4523_a4vulkancamera_render_VideoRenderer_##name

JNIMETHOD(void, create)(JNIEnv * env, jobject obj, jint type);
JNIMETHOD(void, destroy)(JNIEnv * env, jobject obj);
JNIMETHOD(void, init)(JNIEnv * env, jobject obj, jobject surface, jint width, jint height,jobject);
JNIMETHOD(void, render)(JNIEnv * env, jobject obj);
JNIMETHOD(void, draw)(JNIEnv * env, jobject obj, jbyteArray data, jint width, jint height, jint rotation);
JNIMETHOD(void, setParameters)(JNIEnv * env, jobject obj, jint params);
JNIMETHOD(void, setProgress)(JNIEnv * env, jobject obj, jint params);
JNIMETHOD(jint, getParameters)(JNIEnv * env, jobject obj);

#ifdef __cplusplus
}
#endif


#endif //A4VULKANCAMERA_VKVIDEORENDERJNI_H
