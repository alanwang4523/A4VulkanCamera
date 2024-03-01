
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:16.
 * Mail: alanwang4523@gmail.com
 */
#include "FilterUtil.h"

#include "VulkanFilter.h"
#include "RGBFilter.h"
#include "FilterType.h"

VulkanFilter* FilterUtil::getFilterByType(int type) {
    switch (type){
        case SHOW_TYPE:
            return new VulkanFilter();
        case RBG_FILTER_TYPE:
            return new RGBFilter();
        default:
            break;
    }
    return new VulkanFilter();
}

float FilterUtil::getProcess(int progress, float start, float end) {
    return (end - start) * progress / 100.0f + start;
}
