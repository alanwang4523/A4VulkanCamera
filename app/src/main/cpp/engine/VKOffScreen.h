
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:02.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKOFFSCREEN_H
#define A4VULKANCAMERA_VKOFFSCREEN_H

#include <vector>
#include "common/vulkan_wrapper/vulkan_wrapper.h"

class VKDeviceManager;
class VKSwapChainManager;
class VKBufferManager;
class VKTextureManager;

class VKOffScreen {

public:
    struct FrameBufferAttachment {
        VkImage image;
        VkDeviceMemory mem;
        VkImageView view;
    };

    struct OffscreenPass {
        int32_t width, height;
        std::vector<VkFramebuffer> frameBuffer;
        std::vector<FrameBufferAttachment> color;
        std::vector<VkSampler> sampler;
        std::vector<VkDescriptorImageInfo> descriptor;
        VkRenderPass renderPass;
    } offscreenPass;


    struct VulkanGfxPipelineInfo {
        VkDescriptorSetLayout dscLayout_;
        VkDescriptorPool descPool_;
        VkDescriptorSet descSet_;
        VkPipelineLayout layout_;
        VkPipelineCache cache_;
        VkPipeline pipeline_;
    };

public:
    void createOffscreen(VKDeviceManager*deviceInfo, VKSwapChainManager *swapChainInfo);
    int updateOffScreenDescriptorSet(VKDeviceManager *deviceInfo, VKBufferManager *bufferInfo, VKTextureManager *textureInfo);
    VkResult allocateMemoryTypeFromProperties(VKDeviceManager *deviceInfo, uint32_t typeBits,
                                              VkFlags requirements_mask,
                                              uint32_t *typeIndex);

    VulkanGfxPipelineInfo offscreenPipeline;
    int num = 2;
};


#endif //A4VULKANCAMERA_VKOFFSCREEN_H
