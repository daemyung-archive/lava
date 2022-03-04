cmake_minimum_required(VERSION 3.18)
project(lava)

add_library(lava
    STATIC
        include/lava/instance.h
        src/instance.cpp)

target_include_directories(lava
    PUBLIC
        include)

target_compile_features(lava
    PUBLIC
        cxx_std_20)

find_package(Vulkan REQUIRED)
target_link_libraries(lava
    PUBLIC
        Vulkan::Vulkan)

add_executable(test
        test/instance_test.cpp)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(test
        lava
        Catch2::Catch2WithMain)
