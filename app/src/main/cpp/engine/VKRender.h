
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:59.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKRENDER_H
#define A4VULKANCAMERA_VKRENDER_H

#include <stdint.h>
#include <memory>
#include "common/vulkan_wrapper/vulkan_wrapper.h"

class VKDeviceManager;
class VKSwapChainManager;
class VKBufferManager;
class VKOffScreen;
class VulkanFilter;
class OffScreenFilter;
class EffectFilter;

class VKRender {

public:
    VKRender();
    ~VKRender();

public:
    int createRenderPass(VKDeviceManager *deviceInfo, VKSwapChainManager *swapChainInfo);
    int createCommandPool(VKDeviceManager *deviceInfo, VKSwapChainManager *swapChainInfo,
                          VKBufferManager *bufferInfo,
                          VKOffScreen *vkOffScreenInfo,
                          VulkanFilter * filter, OffScreenFilter* offScreenFilter, VulkanFilter* effectFilter);
    int deleteCommandPool(VKDeviceManager *deviceInfo);
    void setImageLayout(VkCommandBuffer cmdBuffer,
                        VkImage image,
                        VkImageLayout oldImageLayout,
                        VkImageLayout newImageLayout,
                        VkPipelineStageFlags srcStages,
                        VkPipelineStageFlags destStages);
public:
    VkRenderPass renderPass;
    VkCommandPool cmdPool;
    std::unique_ptr<VkCommandBuffer[]> cmdBuffer;
    uint32_t cmdBufferLen;
    VkSemaphore semaphore;
    VkFence fence;
};


#endif //A4VULKANCAMERA_VKRENDER_H
