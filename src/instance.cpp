// MIT License
//
// Copyright (c) 2022 Daemyung Jang.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "lava/instance.h"
#include "lava/physical_device.h"

namespace lava {

template<typename T>
uint32_t make_version(T ver) {
    return VK_MAKE_VERSION(ver.major, ver.minor, ver.patch);
}

instance::instance(const descriptor& desc) {
    const VkApplicationInfo vk_application_info {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = desc.app.name,
        .applicationVersion = make_version(desc.app.version),
        .pEngineName = desc.engine.name,
        .engineVersion = make_version(desc.engine.version),
        .apiVersion = VK_API_VERSION_1_3
    };

    const VkInstanceCreateInfo vk_create_info {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &vk_application_info,
        .enabledLayerCount = static_cast<uint32_t>(desc.layers.size()),
        .ppEnabledLayerNames = desc.layers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(desc.extensions.size()),
        .ppEnabledExtensionNames = desc.extensions.data()
    };

    switch (vkCreateInstance(&vk_create_info, nullptr, &vk_instance_)) {
    case VK_ERROR_OUT_OF_HOST_MEMORY:
        throw std::runtime_error("error: out of host memory.");
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        throw std::runtime_error("error: out of device memory.");
    case VK_ERROR_INITIALIZATION_FAILED:
        throw std::runtime_error("error: initialization failed");
    case VK_ERROR_LAYER_NOT_PRESENT:
        throw std::runtime_error("error: layer not present.");
    case VK_ERROR_EXTENSION_NOT_PRESENT:
        throw std::runtime_error("error: extension not present.");
    case VK_ERROR_INCOMPATIBLE_DRIVER:
        throw std::runtime_error("error: incompatible driver.");
    default:
        break;
    }
}

instance::instance(instance&& other) noexcept {
    if (vk_instance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(vk_instance_, nullptr);
    }
    vk_instance_ = other.vk_instance_;
    other.vk_instance_ = VK_NULL_HANDLE;
}

instance::~instance() {
    if (vk_instance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(vk_instance_, nullptr);
    }
}

instance& instance::operator=(instance&& other) noexcept {
    if (vk_instance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(vk_instance_, nullptr);
    }
    vk_instance_ = other.vk_instance_;
    other.vk_instance_ = VK_NULL_HANDLE;
    return *this;
}

instance::operator bool() const {
    return vk_instance_ != VK_NULL_HANDLE;
}

instance::operator VkInstance() const {
    return vk_instance_;
}

std::vector<physical_device> instance::physical_devices() const {
    return physical_device::enumerate(*this);
}

} //namespace lava
