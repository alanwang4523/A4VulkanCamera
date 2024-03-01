
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:14.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_RGBFILTER_H
#define A4VULKANCAMERA_RGBFILTER_H


#include "VulkanFilter.h"

static const char rgbFragShader[] = "#version 400\n"
                                    "#extension GL_ARB_separate_shader_objects : enable\n"
                                    "#extension GL_ARB_shading_language_420pack : enable\n"
                                    "layout (binding = 0) uniform sampler2D tex;\n"
                                    "layout (binding = 1) uniform rgb{ \n"
                                    " float red;  \n"
                                    " float green;  \n"
                                    " float blue;  \n"
                                    "} rgbVals;\n"
                                    "layout (push_constant) uniform pushBlock {\n"
                                    " float push_red;\n"
                                    " float push_green;\n"
                                    " float push_blue;\n"
                                    "} pushVals;\n"
                                    "layout (location = 0) in vec2 texcoord;\n"
                                    "layout (location = 0) out vec4 uFragColor;\n"
                                    "void main() {\n"
                                    "    vec4 textureColor = texture(tex,  texcoord); \n"
                                    "   uFragColor = vec4(textureColor.r * pushVals.push_red, textureColor.g * pushVals.push_green , textureColor.b * pushVals.push_blue,1.0);\n"
                                    "}";


class RGBFilter : public VulkanFilter {
public:
    RGBFilter() : VulkanFilter() {
        pVertexShader = showVertexShader;
        pFragShader = rgbFragShader;
    };

    virtual int updateDescriptorSet(std::vector<VkDescriptorBufferInfo>& bufferInfo,std::vector<VkDescriptorImageInfo>& imageInfo);
    virtual int createPipeline(VkRenderPass renderPass);
    virtual int buildRenderPass(VkCommandBuffer commandBuffer,VkRenderPass renderPass,VkFramebuffer framebuffer);
    virtual void setProcess(uint32_t process) override ;
protected:
    virtual int createDescriptorLayout();
    virtual int createDescriptorSet();

    float red = 1.0;
    float green = 1.0;
    float blue = 1.0;
};


#endif //A4VULKANCAMERA_RGBFILTER_H
