/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 15:29.
 * Mail: alanwang4523@gmail.com
 */
#include "VKVideoRenderer.h"
#include "common/vulkan_wrapper/vulkan_wrapper.h"
#include "utils/Log.h"
#include "filter/FilterUtil.h"

VKVideoRenderer::VKVideoRenderer()
        : mVideoWidth(0)
        , mVideoHeight(0)
        , mWindowWidth(0)
        , mWindowHeight(0)
        , mNewFilterType(0)
        , mRotation(0)
{
    vkRenderInfo = new VKRender();
    vkBufferInfo = new VKBufferManager();
    vkSwapChainInfo = new VKSwapChainManager();
    vkDeviceInfo = new VKDeviceManager();
    vkTextureInfo = new VKTextureManager();
    vkOffScreenInfo = new VKOffScreen();

    vkDeviceInfo->initialized = false;

    mDataBuffer = nullptr;
    vulkanFilter = new VulkanFilter();
    offscreenFilter = new OffScreenFilter();
    effectFilter = new EffectFilter();
}

VKVideoRenderer::~VKVideoRenderer() {
    vkDeviceInfo->initialized = false;
    deleteCommandPool();
}

void VKVideoRenderer::init(ANativeWindow *window, size_t width, size_t height,AAssetManager* manager) {
    mWindowWidth = width;
    mWindowHeight = height;
    mAssetManager = manager;

    if (!InitVulkan()) {
        LOGE("Vulkan is unavailable, install vulkan and re-start");
        return;
    }

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .apiVersion = VK_MAKE_VERSION(1, 0, 0),
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .pApplicationName = "A4VulkanCameraPreview",
        .pEngineName = "A4VulkanCamera",
    };

    createDevice(window, &appInfo);
    createSwapChain();
}

void VKVideoRenderer::renderFrame() {
    uint32_t nextIndex;
    CALL_VK(vkAcquireNextImageKHR(vkDeviceInfo->device, vkSwapChainInfo->swapchain, UINT64_MAX, vkRenderInfo->semaphore, VK_NULL_HANDLE, &nextIndex));
    CALL_VK(vkResetFences(vkDeviceInfo->device,1,&vkRenderInfo->fence));

    VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submitInfo = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &vkRenderInfo->semaphore,
        .pWaitDstStageMask = &waitStageMask,
        .commandBufferCount = 1,
        .pCommandBuffers = &vkRenderInfo->cmdBuffer[nextIndex],
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr,
    };

    if (vkDeviceInfo->queue == nullptr){
        LOGE("vkDeviceInfo->queue == nullptr");
        return ;
    }

    CALL_VK(vkQueueSubmit(vkDeviceInfo->queue,1,&submitInfo,vkRenderInfo->fence));
    CALL_VK(vkWaitForFences(vkDeviceInfo->device,1,&vkRenderInfo->fence,VK_TRUE,100000000));

    VkResult result;
    VkPresentInfoKHR presentInfo{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext = nullptr,
        .swapchainCount = 1,
        .pSwapchains = &vkSwapChainInfo->swapchain,
        .pImageIndices = &nextIndex,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = nullptr,
        .pResults = &result
    };

    vkQueuePresentKHR(vkDeviceInfo->queue,&presentInfo);
}

void VKVideoRenderer::draw(uint8_t *buffer, size_t length, size_t width, size_t height, int rotation) {
    mDataBuffer = buffer;
    mRotation = rotation;

    mVideoWidth = width;
    mVideoHeight = height;

    if (!vkDeviceInfo->initialized) {
        initializeRenderEnv();
    }
    if (!vkDeviceInfo->initialized) {
        return;
    }

    if (mNewFilterType != mCurFilterType){
        mCurFilterType = mNewFilterType;

        delete effectFilter;
        effectFilter = nullptr;
        effectFilter = FilterUtil::getFilterByType(mCurFilterType);
        effectFilter->init(vkDeviceInfo->device, vkOffScreenInfo->offscreenPass.renderPass);

        std::vector<VkDescriptorBufferInfo> vecBufferInfo;
        vecBufferInfo.resize(1);

        VkDescriptorBufferInfo bufferInfo {
                bufferInfo.buffer = vkBufferInfo->rgbBuffer,
                bufferInfo.offset = 0,
                bufferInfo.range = sizeof(RGBBufferObject),
        };

        vecBufferInfo[0] = bufferInfo;


        std::vector<VkDescriptorImageInfo> imageInfoList;
        VkDescriptorImageInfo imageInfo{
                .sampler = vkOffScreenInfo->offscreenPass.descriptor[0].sampler,
                .imageView = vkOffScreenInfo->offscreenPass.descriptor[0].imageView,
                .imageLayout = vkOffScreenInfo->offscreenPass.descriptor[0].imageLayout
        };

        imageInfoList.push_back(imageInfo);

        effectFilter->updateDescriptorSet(vecBufferInfo, imageInfoList);
        createCommandPool();
    }

    if (mCurProcess != mLastProcess){
        mLastProcess = mCurProcess;
        createCommandPool();
        LOGE("mCurProcess != mLastProcess create command pool");
    }

    updateTextures();
    renderFrame();
}

void VKVideoRenderer::setFilterType(int filterType) {
    mNewFilterType = filterType;
}

void VKVideoRenderer::setProcess(int process) {
    mCurProcess = process;
    if (effectFilter != nullptr){
        effectFilter->setProcess(mCurProcess);
    }
}

bool VKVideoRenderer::createTextures() {
    vkTextureInfo->createTexture(vkDeviceInfo, mDataBuffer, mVideoWidth, mVideoHeight);
    return true;
}

bool VKVideoRenderer::updateTextures() {
    vkTextureInfo->updateTextures(vkDeviceInfo, mDataBuffer, mVideoWidth, mVideoHeight);
    return false;
}

void VKVideoRenderer::deleteTextures() {
    vkTextureInfo->deleteTextures(vkDeviceInfo);
}

void VKVideoRenderer::initializeRenderEnv() {
    createRenderPass();
    createFrameBuffers();

    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffers();
    createTextures();

    createOffscreenReaderPassAndFramebuffer();

    offscreenFilter->init(vkDeviceInfo->device,vkOffScreenInfo->offscreenPass.renderPass);

    std::vector<VkDescriptorBufferInfo> vecBufferInfo;
    vecBufferInfo.resize(1);

    VkDescriptorBufferInfo bufferInfo {
            bufferInfo.buffer = vkBufferInfo->uboBuffer,
            bufferInfo.offset = 0,
            bufferInfo.range = sizeof(UniformBufferObject)
    };

    vecBufferInfo[0] = bufferInfo;

    std::vector<VkDescriptorImageInfo> vecImageInfo;
    vecImageInfo.resize(3);

    VkDescriptorImageInfo texDsts[3];
    memset(texDsts, 0, sizeof(texDsts));
    for (int i = 0; i < 3; ++i) {
        texDsts[i].sampler = vkTextureInfo->textures[i].sampler;
        texDsts[i].imageView = vkTextureInfo->textures[i].view;
        texDsts[i].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
        vecImageInfo[i] = texDsts[i];
    }

    offscreenFilter->updateDescriptorSet(vecBufferInfo,vecImageInfo);
    effectFilter->init(vkDeviceInfo->device,vkOffScreenInfo->offscreenPass.renderPass);
    effectFilter->updateDescriptorSet(vkOffScreenInfo->offscreenPass.descriptor[0].sampler,
                                      vkOffScreenInfo->offscreenPass.descriptor[0].imageView,
                                      VK_IMAGE_LAYOUT_GENERAL);

    vulkanFilter->init(vkDeviceInfo->device,vkRenderInfo->renderPass);
    vulkanFilter->updateDescriptorSet(
            vkOffScreenInfo->offscreenPass.descriptor[1].sampler,
            vkOffScreenInfo->offscreenPass.descriptor[1].imageView,
            VK_IMAGE_LAYOUT_GENERAL
    );

    createCommandPool();
    vkDeviceInfo->initialized = true;
}

void VKVideoRenderer::createDevice(ANativeWindow *platformWindow, VkApplicationInfo *appInfo) {
    vkDeviceInfo->createDevice(platformWindow, appInfo);
}

void VKVideoRenderer::createSwapChain() {
    vkSwapChainInfo->createSwapChain(vkDeviceInfo);
}

void VKVideoRenderer::createRenderPass() {
    vkRenderInfo->createRenderPass(vkDeviceInfo, vkSwapChainInfo);
}

void VKVideoRenderer::createFrameBuffers(VkImageView depthView) {
    vkSwapChainInfo->createFrameBuffer(vkDeviceInfo, vkRenderInfo, depthView);
}

void VKVideoRenderer::createUniformBuffers() {
    vkBufferInfo->updateUniformBuffers(mVideoWidth, mVideoHeight, mRotation, mWindowWidth, mWindowHeight);
    vkBufferInfo->createUniformBuffers(vkDeviceInfo);
    vkBufferInfo->createRGBUniformBuffer(vkDeviceInfo);
}

void VKVideoRenderer::createVertexBuffer() {
    vkBufferInfo->createVertexBuffer(vkDeviceInfo);
    vkBufferInfo->createShowVertexBuffer(vkDeviceInfo);
}

void VKVideoRenderer::createIndexBuffer() {
    vkBufferInfo->createIndexBuffer(vkDeviceInfo);
}

void VKVideoRenderer::createCommandPool() {
    vkRenderInfo->createCommandPool(vkDeviceInfo, vkSwapChainInfo, vkBufferInfo, vkOffScreenInfo,
                                    vulkanFilter, offscreenFilter, effectFilter);
}

void VKVideoRenderer::deleteUniformBuffers() {
    vkDestroyBuffer(vkDeviceInfo->device, vkBufferInfo->uboBuffer, nullptr);
    vkFreeMemory(vkDeviceInfo->device, vkBufferInfo->uboBufferMemory, nullptr);
}

void VKVideoRenderer::deleteCommandPool() {
    vkRenderInfo->deleteCommandPool(vkDeviceInfo);
}

void VKVideoRenderer::createOffscreenReaderPassAndFramebuffer() {
    vkOffScreenInfo->createOffscreen(vkDeviceInfo,vkSwapChainInfo);
}
