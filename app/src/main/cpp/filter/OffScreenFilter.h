
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:17.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_OFFSCREENFILTER_H
#define A4VULKANCAMERA_OFFSCREENFILTER_H

#include "VulkanFilter.h"

class OffScreenFilter : public VulkanFilter {
public:
    OffScreenFilter():VulkanFilter(){
        pVertexShader = kVertexShader;
        pFragShader = kFragmentShader;
    }
    virtual int init(VkDevice device,VkRenderPass renderPass) override ;
    int updateDescriptorSet(VkSampler ,VkImageView,VkImageLayout) override;
    virtual int updateDescriptorSet(std::vector<VkDescriptorBufferInfo>& bufferInfo,std::vector<VkDescriptorImageInfo>& imageInfo) override;
protected:
    virtual int createDescriptorLayout() override;
    virtual int createDescriptorSet() override;
};



#endif //A4VULKANCAMERA_OFFSCREENFILTER_H
