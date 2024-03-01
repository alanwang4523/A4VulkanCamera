
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:19.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_FILTERDEFINE_H
#define A4VULKANCAMERA_FILTERDEFINE_H


#include "common/vulkan_wrapper/vulkan_wrapper.h"

typedef struct  FilterPipeline{
    VkDescriptorSetLayout descLayout_;
    VkDescriptorPool descPool_;
    VkDescriptorSet descSet_;
    VkPipelineLayout layout_;
    VkPipeline pipeline_;
    VkPipelineCache cache_;
} FilterPipeline;

typedef struct FilterContext{
    VkRenderPass renderPass;
    VkDevice  device;
    VkFramebuffer framebuffer;
} FilterContext;


typedef struct FilterBuffer{
    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;
    int indexCount;
} FilterBuffer;

typedef struct FilterFramebuffer{
    VkFramebuffer framebuffer;
    int width;
    int height;
} FilterFramebuffer;


#endif //A4VULKANCAMERA_FILTERDEFINE_H
