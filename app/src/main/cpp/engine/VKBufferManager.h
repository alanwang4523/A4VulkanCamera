
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:49.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKBUFFERMANAGER_H
#define A4VULKANCAMERA_VKBUFFERMANAGER_H

#include <vector>
#include <string>
#include "VKDeviceManager.h"
#include "common/vulkan_wrapper/vulkan_wrapper.h"
#include "common/VKDefines.h"

class VKBufferManager {

public:
    int createRGBUniformBuffer(VKDeviceManager* deviceInfo);
    int createVertexBuffer(VKDeviceManager* deviceInfo);
    int createShowVertexBuffer(VKDeviceManager* deviceInfo);
    int createIndexBuffer(VKDeviceManager* deviceInfo);
    int createUniformBuffers(VKDeviceManager* deviceInfo);
    int updateUniformBuffers(size_t m_width,size_t m_height,int m_rotation,size_t m_backingWidth,size_t m_backingHeight);

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    VkBuffer uboBuffer;
    VkDeviceMemory uboBufferMemory;

    VkBuffer rgbBuffer;
    VkDeviceMemory rgbBufferMemory;
    uint32_t m_indexCount;
    VkBuffer showVertexBuffer;
    VkDeviceMemory showBufferMemory;
    UniformBufferObject m_ubo;
    RGBBufferObject m_rgb;
private:
    bool mapMemoryTypeToIndex(VKDeviceManager* deviceInfo, uint32_t typeBits,
                              VkFlags requirements_mask, uint32_t* typeIndex);
    void createBuffer(VKDeviceManager * deviceInfo, VkDeviceSize size, VkBufferUsageFlags usage,
                      VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VKDeviceManager * deviceInfo, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
};


#endif //A4VULKANCAMERA_VKBUFFERMANAGER_H
