
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:54.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKUTILS_H
#define A4VULKANCAMERA_VKUTILS_H

#include <cstddef>
#include "common/vulkan_wrapper/vulkan_wrapper.h"

void mat4f_load_ortho(float left, float right, float bottom, float top, float near, float far, float* mat4f);
void mat4f_load_rotation_z(int rotation, float* mat4f);
void mat4f_load_scale(float scaleX, float scaleY, float scaleZ, float* mat4f);
float aspect_ratio_correction(bool fillScreen, size_t backingWidth, size_t backingHeight, size_t width, size_t height);

VkResult buildShader(const char *data, VkShaderStageFlagBits type, VkDevice vkDevice, VkShaderModule* shaderOut);

#endif //A4VULKANCAMERA_VKUTILS_H
