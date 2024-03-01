
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:21.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_EFFECTFILTER_H
#define A4VULKANCAMERA_EFFECTFILTER_H

#include "VulkanFilter.h"

class EffectFilter : public VulkanFilter {

public:
    EffectFilter():VulkanFilter(){
        pVertexShader = showVertexShader;
        pFragShader = showFragShader;
    }

};


#endif //A4VULKANCAMERA_EFFECTFILTER_H
