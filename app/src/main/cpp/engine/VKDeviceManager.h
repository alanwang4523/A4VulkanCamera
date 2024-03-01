
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:41.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKDEVICEMANAGER_H
#define A4VULKANCAMERA_VKDEVICEMANAGER_H

#include <vector>
#include <string>
#include <android/native_window.h>
#include "common/vulkan_wrapper/vulkan_wrapper.h"

class VKDeviceManager {
public:
    VKDeviceManager();
    ~VKDeviceManager();
    int createDevice(ANativeWindow* platformWindow, VkApplicationInfo* appInfo);

    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceMemoryProperties memoryProperties;
    VkDevice device;

    uint32_t queueFamilyIndex;


    VkSurfaceKHR surface;
    VkQueue queue;

    bool initialized = false;
};


#endif //A4VULKANCAMERA_VKDEVICEMANAGER_H
