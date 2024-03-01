
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:12.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_VULKANFILTER_H
#define A4VULKANCAMERA_VULKANFILTER_H

#include <array>
#include "common/VKShaders.h"
#include "common/VKUtils.h"
#include "common/VulkanInitializers.h"
#include "FilterDefine.h"
#include "utils/Log.h"

class VulkanFilter {
public:
    VulkanFilter() : pVertexShader(showVertexShader), pFragShader(showFragShader) {
        pushConstant.resize(0);
    }
    virtual int init(VkDevice device,VkRenderPass renderPass);
    virtual int buildRenderPass(VkCommandBuffer commandBuffer,VkRenderPass renderPass,VkFramebuffer framebuffer);
    virtual int buildRenderPass(VkCommandBuffer commandBuffer);
    virtual int bindFilterBuffer(FilterBuffer& buffer);
    virtual int bindFilterFramebuffer(FilterFramebuffer& framebuffer);
    virtual int updateDescriptorSet(VkSampler sampler,VkImageView imageView,VkImageLayout imageLayout);
    virtual int updateDescriptorSet(std::vector<VkDescriptorBufferInfo>& bufferInfo,std::vector<VkDescriptorImageInfo>& imageInfo);
    virtual int updateBufferDescriptorSet(std::vector<VkDescriptorBufferInfo>& bufferInfo,int binding = 0);
    virtual int updateImageDescriptorSet(std::vector<VkDescriptorImageInfo>& imageInfo,int binding = 0 );
    virtual void setProcess(uint32_t process);
protected:

    const char* pVertexShader = showVertexShader;
    const char* pFragShader = showFragShader;


    virtual int createDescriptorLayout();
    virtual int createDescriptorSet();
    virtual int createPipelineCache();
    virtual int createPipeline(VkRenderPass renderPass);
    virtual int createPipeline();

    struct FilterPipeline pipeline;
    struct FilterContext context;

    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;
    std::vector<float> pushConstant;

    int indexCount;
    int width;
    int height;
    bool isInit = false;
    uint32_t mProcess ;
};


#endif //A4VULKANCAMERA_VULKANFILTER_H
