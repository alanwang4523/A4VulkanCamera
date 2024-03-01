
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:47.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKDEFINES_H
#define A4VULKANCAMERA_VKDEFINES_H

#include "utils/Log.h"

#define CALL_VK(func)                                         \
  if (VK_SUCCESS != (func)) {                                 \
    LOGE("Error File[%s], line[%d]", __FILE__, __LINE__);     \
    assert(false);                                            \
  }

// A macro to check value is VK_SUCCESS
#define VK_CHECK(x) CALL_VK(x)

struct Vertex {
    float pos[3];
    float uv[2];
};

struct UniformBufferObject {
    float projection[16];
    float rotation[16];
    float scale[16];
};


struct RGBBufferObject{
    float red;
    float green;
    float blue;
};

#endif //A4VULKANCAMERA_VKDEFINES_H
