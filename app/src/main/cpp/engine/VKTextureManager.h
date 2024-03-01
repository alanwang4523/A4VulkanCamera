
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:05.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKTEXTUREMANAGER_H
#define A4VULKANCAMERA_VKTEXTUREMANAGER_H


#include <cassert>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "common/vulkan_wrapper/vulkan_wrapper.h"

class VKDeviceManager;
class VKRender;
class VKBufferManager;

class VKTextureManager {
public:
    enum TextureType {
        tTexY, tTexU, tTexV
    };
    VKTextureManager() : texType{tTexY, tTexU, tTexV} {

    }
    static const VkFormat kTexFmt = VK_FORMAT_R8G8B8A8_UNORM;
    static const VkFormat kTextureFormat = VK_FORMAT_R8_UNORM;

    struct VulkanTexture {
        VkSampler sampler;
        VkImage image;
        VkImageLayout imageLayout;
        VkSubresourceLayout layout;
        VkDeviceMemory mem;
        VkImageView view;
        size_t width;
        size_t height;
        void *mapped;
    };

    typedef struct texture_object {
        VkSampler sampler;
        VkImage image;
        VkImageLayout imageLayout;
        VkDeviceMemory mem;
        VkImageView view;
        int32_t tex_width;
        int32_t tex_height;
    } texture_object;
public:
    void createTexture(VKDeviceManager *deviceInfo, uint8_t *m_pBuffer, size_t m_width, size_t m_height);
    VkResult loadTexture(VKDeviceManager *deviceInfo, uint8_t *buffer, TextureType type, size_t width,
                         size_t height,
                         VulkanTexture *texture, VkImageUsageFlags usage, VkFlags required_props);
    void setImageLayout(VkCommandBuffer cmdBuffer,
                        VkImage image,
                        VkImageLayout oldImageLayout,
                        VkImageLayout newImageLayout,
                        VkPipelineStageFlags srcStages,
                        VkPipelineStageFlags destStages);
    size_t getBufferOffset(VulkanTexture *texture, TextureType type, size_t width, size_t height);
    void copyTextureData(VulkanTexture *texture, uint8_t *data);
    VkResult allocateMemoryTypeFromProperties(VKDeviceManager *deviceInfo, uint32_t typeBits,
                                              VkFlags requirements_mask,
                                              uint32_t *typeIndex);
    void deleteTextures(VKDeviceManager *deviceInfo);
    void updateTextures(VKDeviceManager *deviceInfo, uint8_t *buffer, size_t width, size_t height);

public:
    struct texture_object testTextures[1];
    static const uint32_t kTextureCount = 3;
    struct VulkanTexture textures[kTextureCount];
    const TextureType texType[kTextureCount];
};


#endif //A4VULKANCAMERA_VKTEXTUREMANAGER_H
