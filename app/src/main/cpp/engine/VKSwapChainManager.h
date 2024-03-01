
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:56.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKSWAPCHAINMANAGER_H
#define A4VULKANCAMERA_VKSWAPCHAINMANAGER_H

#include "VKRender.h"
#include "VKDeviceManager.h"

class VKSwapChainManager {
public:
    VKSwapChainManager();
    ~VKSwapChainManager();

    int createSwapChain(VKDeviceManager* info);
    int createFrameBuffer(VKDeviceManager *deviceInfo, VKRender * renderInfo, VkImageView depthView =  VK_NULL_HANDLE);
public:
    VkSwapchainKHR swapchain;
    uint32_t swapchainLength;

    VkExtent2D displaySize;
    VkFormat displayFormat;

    // array of frame buffers and views
    std::unique_ptr<VkFramebuffer[]> framebuffers;
    std::unique_ptr<VkImage[]> displayImages;
    std::unique_ptr<VkImageView[]> displayViews;
};


#endif //A4VULKANCAMERA_VKSWAPCHAINMANAGER_H
