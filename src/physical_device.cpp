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

#include "lava/physical_device.h"
#include "lava/instance.h"

namespace lava {

size_t physical_device::count(instance const& instance) {
    if (!instance) {
        throw std::runtime_error("instance is invalid.");
    }
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(static_cast<VkInstance>(instance),
            &count, nullptr);
    return count;
}

std::vector<physical_device> physical_device::enumerate(instance const& instance) {
    if (!instance) {
        throw std::runtime_error("instance is invalid.");
    }
    std::vector<physical_device> physical_devices(physical_device::count(instance));
    for (uint32_t i = 0; i != physical_devices.size(); ++i) {
        physical_devices[i] = physical_device({&instance, i});
    }
    return physical_devices;
}

physical_device::physical_device(descriptor const& desc)
    : master_(desc.master), index_(desc.index) {
    if (!master_ || !(*master_)) {
        throw std::runtime_error("instance is invalid.");
    }
    uint32_t count = physical_device::count(*master_);
    if (!count || count <= index_) {
        throw std::runtime_error("index is invalid.");
    }
    std::vector<VkPhysicalDevice> vk_physical_devices(count);
    vkEnumeratePhysicalDevices(static_cast<VkInstance>(*master_),
            &count, vk_physical_devices.data());
    vk_physical_device_ = vk_physical_devices.at(index_);
}

physical_device::operator bool() const {
    return vk_physical_device_ != VK_NULL_HANDLE;
}

physical_device::operator VkPhysicalDevice() const {
    return vk_physical_device_;
}

instance const* physical_device::master() const noexcept {
    return master_;
}

size_t physical_device::index() const noexcept {
    return index_;
}

} //namespace lava

