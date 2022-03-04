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

#ifndef LAVA_INSTANCE_H
#define LAVA_INSTANCE_H

#include <vector>
#include <vulkan/vulkan.h>

namespace lava {

class instance {
public:
    struct descriptor {
          struct {
              const char* name;
              struct {
                  uint8_t major;
                  uint8_t minor;
                  uint8_t patch;
              } version;
          } app;
          struct {
              const char* name;
              struct {
                  uint8_t major;
                  uint8_t minor;
                  uint8_t patch;
              } version;
          } engine;
          std::vector<const char*> layers;
          std::vector<const char*> extensions;
    };

    instance() = default;

    explicit instance(const descriptor& desc);

    explicit instance(const instance& other) = delete;

    instance(instance&& other) noexcept;

    ~instance();

    instance& operator=(const instance& other) = delete;

    instance& operator=(instance&& other) noexcept;

    explicit operator bool() const;

private:
    VkInstance instance_ = VK_NULL_HANDLE;
};

} // namespace lava

#endif //LAVA_INSTANCE_H
