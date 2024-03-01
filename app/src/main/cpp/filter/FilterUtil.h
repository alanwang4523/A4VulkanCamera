
/**
 * Author: AlanWang4523.
 * Date: 2024/3/1 16:16.
 * Mail: alanwang4523@gmail.com
 */
#ifndef A4VULKANCAMERA_FILTERUTIL_H
#define A4VULKANCAMERA_FILTERUTIL_H

class VulkanFilter;

class FilterUtil {
public:
    static VulkanFilter* getFilterByType(int type);
    static float getProcess(int progress, float start, float end);
};


#endif //A4VULKANCAMERA_FILTERUTIL_H
