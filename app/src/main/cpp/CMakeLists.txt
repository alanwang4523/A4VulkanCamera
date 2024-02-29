# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.6.0)

# Declares and names the project.

project("a4vulkancamera")

# Integrate GameActivity, refer to
#     https://d.android.com/games/agdk/integrate-game-activity
# for the detailed instructions.
find_package(game-activity REQUIRED CONFIG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall \
                     -DVK_USE_PLATFORM_ANDROID_KHR")

set(PATH_TO_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(PATH_TO_TRIANGLE ${CMAKE_CURRENT_SOURCE_DIR}/triangle)


include_directories(${PATH_TO_COMMON}/vulkan_wrapper)

file(GLOB_RECURSE CPP_FILES_COMMON "${PATH_TO_COMMON}/*.cpp")
file(GLOB_RECURSE CPP_FILES_TRIANGLE "${PATH_TO_TRIANGLE}/*.cpp")

add_library( # Sets the name of the library.
        a4vulkancamera
        SHARED
        ${CPP_FILES_COMMON}
        ${CPP_FILES_TRIANGLE}
        native-lib.cpp
        )

find_library( # Sets the name of the path variable.
        log-lib
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        a4vulkancamera
        ${log-lib}
        game-activity::game-activity
        android
        )