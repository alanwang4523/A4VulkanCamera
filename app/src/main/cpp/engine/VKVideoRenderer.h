
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:29.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VKVIDEORENDERER_H
#define A4VULKANCAMERA_VKVIDEORENDERER_H


#include <stdint.h>
#include <memory>
#include <android/native_window.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <vulkan/vulkan.h>
#include "engine/VKDeviceManager.h"
#include "engine/VKBufferManager.h"
#include "engine/VKSwapChainManager.h"
#include "engine/VKRender.h"
#include "engine/VKTextureManager.h"
#include "engine/VKOffScreen.h"
#include "filter/VulkanFilter.h"
#include "filter/OffScreenFilter.h"
#include "filter/EffectFilter.h"

class VKVideoRenderer {
public:
    VKVideoRenderer();
    virtual ~VKVideoRenderer();
    virtual void init(ANativeWindow* window, size_t width, size_t height, AAssetManager* manager);
    virtual void draw(uint8_t *buffer, size_t length, size_t width, size_t height, int rotation);
    virtual void setFilterType(int filterType);
    virtual void setProcess(int process);
    virtual bool createTextures();
    virtual bool updateTextures();
    virtual void deleteTextures();

private:
    void initializeRenderEnv();
    void renderFrame();
    void createDevice(ANativeWindow* platformWindow, VkApplicationInfo* appInfo);
    void createSwapChain();
    void createRenderPass();
    void createFrameBuffers(VkImageView depthView = VK_NULL_HANDLE);

    void createUniformBuffers();
    void createVertexBuffer();
    void createIndexBuffer();
    void createCommandPool();
    void deleteUniformBuffers();
    void deleteCommandPool();
    void createOffscreenReaderPassAndFramebuffer();

private:
    size_t mVideoWidth;
    size_t mVideoHeight;
    size_t mWindowWidth;
    size_t mWindowHeight;
    int mRotation;

    AAssetManager* mAssetManager;

    VKDeviceManager* vkDeviceInfo;
    VKSwapChainManager* vkSwapChainInfo;
    VKRender* vkRenderInfo;
    VKBufferManager* vkBufferInfo;
    VKTextureManager* vkTextureInfo;
    VKOffScreen* vkOffScreenInfo;

    uint8_t *mDataBuffer;

    VulkanFilter *vulkanFilter;
    OffScreenFilter *offscreenFilter;
    VulkanFilter* effectFilter;

    int mNewFilterType;
    int mCurFilterType = 0;
    int mCurProcess = 0;
    int mLastProcess = 0;
};


#endif //A4VULKANCAMERA_VKVIDEORENDERER_H
