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

#include <catch.hpp>
#include <lava/instance.h>
#include <lava/physical_device.h>

using namespace lava;

TEST_CASE("get physical device count", "[physical device]") {
    SECTION("with invalid instance") {
        instance inst;
        CHECK_THROWS(physical_device::count(inst));
    }

    SECTION("with valid instance") {
        instance inst(instance::descriptor {});
        CHECK_NOTHROW(physical_device::count(inst));
    }
}

TEST_CASE("enumerate physical devices", "[physical device]") {
    instance inst(instance::descriptor {});
    auto physical_devices = physical_device::enumerate(inst);
    CHECK_FALSE(physical_devices.empty());
}

TEST_CASE("constructor physical device", "[physical device]") {
    SECTION("invalid instance") {
        physical_device::descriptor desc {};
        CHECK_THROWS(physical_device(desc));
    }

    instance inst(instance::descriptor {});

    SECTION("invalid index") {
        physical_device::descriptor desc {
                .master = &inst,
                .index = SIZE_MAX
        };
        CHECK_THROWS(physical_device(desc));
    }

    SECTION("default") {
        physical_device::descriptor desc {
            .master = &inst,
            .index = 0
        };
        CHECK_NOTHROW(physical_device(desc));
    }
}

TEST_CASE("cast physical device", "[physical device]") {
    physical_device phy_devs0;
    CHECK(static_cast<VkPhysicalDevice>(phy_devs0) == VK_NULL_HANDLE);

    instance::descriptor desc {};
    instance inst1(desc);
    auto phy_devs1 = inst1.physical_devices();
    std::for_each(phy_devs1.begin(), phy_devs1.end(),
            [](const physical_device& phy_dev) {
        CHECK(static_cast<VkPhysicalDevice>(phy_dev) != VK_NULL_HANDLE);
    });
}

TEST_CASE("get master of physical device", "[physical device]") {
    instance::descriptor desc {};
    instance inst(desc);
    auto phy_devs = inst.physical_devices();
    std::for_each(phy_devs.begin(), phy_devs.end(),
            [](const physical_device& phy_dev) {
        CHECK(phy_dev.master());
    });
}

TEST_CASE("get index of physical device", "[physical device]") {
    instance::descriptor desc {};
    instance inst(desc);
    auto phy_devs = inst.physical_devices();
    for (auto i = 0; i != phy_devs.size(); ++i) {
        CHECK(phy_devs[i].index() == i);
    }
}
