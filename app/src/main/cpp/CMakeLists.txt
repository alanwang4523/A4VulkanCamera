# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.6.0)

project("a4vulkancamera")

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -DVK_USE_PLATFORM_ANDROID_KHR -DVK_NO_PROTOTYPES")

set(PATH_TO_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(PATH_TO_TRIANGLE ${CMAKE_CURRENT_SOURCE_DIR}/triangle)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PATH_TO_COMMON}/vulkan_wrapper)

file(GLOB_RECURSE CPP_FILES_COMMON "${PATH_TO_COMMON}/*.cpp")
file(GLOB_RECURSE CPP_FILES_IN_JNI "${CMAKE_CURRENT_SOURCE_DIR}/jni/*.cpp")
file(GLOB_RECURSE CPP_FILES_IN_ENGINE "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")
file(GLOB_RECURSE CPP_FILES_IN_FILTER "${CMAKE_CURRENT_SOURCE_DIR}/filter/*.cpp")
file(GLOB_RECURSE CPP_FILES_IN_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp")
#file(GLOB_RECURSE CPP_FILES_TRIANGLE "${PATH_TO_TRIANGLE}/*.cpp")

add_library( # Sets the name of the library.
        a4vulkancamera
        SHARED
        ${CPP_FILES_COMMON}
        ${CPP_FILES_IN_JNI}
        ${CPP_FILES_IN_ENGINE}
        ${CPP_FILES_IN_FILTER}
        ${CPP_FILES_IN_UTILS}
#        ${CPP_FILES_TRIANGLE}
        native-lib.cpp
        )

# SHADERC_SRC 变量指定为路径的绝对值
get_filename_component(SHADERC_SRC
        ${ANDROID_NDK}/sources/third_party/shaderc
        ABSOLUTE)

add_library(shaderc_lib STATIC IMPORTED)
set_target_properties(shaderc_lib PROPERTIES IMPORTED_LOCATION
        ${SHADERC_SRC}/libs/c++_static/${ANDROID_ABI}/libshaderc.a)

target_include_directories(a4vulkancamera PRIVATE
        ${SHADERC_SRC}/include
        ${SHADERC_SRC}/third_party/spirv-tools/include
        ${SHADERC_SRC}/third_party/spirv-tools/include/spirv-tools
        )

find_library( # Sets the name of the path variable.
        log-lib
        log)

find_library( # Sets the name of the path variable.
        GLESv2-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        GLESv2 )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        a4vulkancamera
        ${log-lib}
        android
        shaderc_lib
        ${GLESv2-lib}
        )