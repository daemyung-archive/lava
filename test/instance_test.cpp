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

using namespace lava;

TEST_CASE("constructor instance", "[instance]") {
    SECTION("default") {
        instance::descriptor desc {};
        CHECK_NOTHROW(instance(desc));
    }

    SECTION("app") {
        instance::descriptor desc {
            .app {
                .name = "lava_cts",
                .version = {0, 1, 0}
            }
        };
        CHECK_NOTHROW(instance(desc));
    }

    SECTION("engine") {
        instance::descriptor desc {
            .engine {
                .name = "lava_cts",
                .version = {0, 1, 0}
            }
        };
        CHECK_NOTHROW(instance(desc));
    }

    SECTION("valid layers") {
        instance::descriptor desc {
            .layers {
                "VK_LAYER_KHRONOS_validation"
            }
        };
        CHECK_NOTHROW(instance(desc));
    }

    SECTION("invalid layers") {
        instance::descriptor desc {
            .layers {
                "VK_LAYER_invalid"
            }
        };
        CHECK_THROWS(instance(desc));
    }

    SECTION("valid extensions") {
        instance::descriptor desc {
            .extensions {
                "VK_EXT_debug_report",
                "VK_KHR_surface"
            }
        };
        CHECK_NOTHROW(instance(desc));
    }

    SECTION("invalid extensions") {
        instance::descriptor desc {
            .extensions {
                "VK_EXT_invalid"
            }
        };
        CHECK_THROWS(instance(desc));
    }

    SECTION("all") {
        instance::descriptor desc {
            .app {
                .name = "lava_cts",
                .version = {0, 1, 0}
            },
            .engine {
                .name = "lava_cts",
                .version = {0, 1, 0}
            },
            .layers {
                "VK_LAYER_KHRONOS_validation"
            },
            .extensions {
                "VK_EXT_debug_report",
                "VK_KHR_surface"
            }
        };
        CHECK_NOTHROW(instance(desc));
    }
}

TEST_CASE("move instance", "[instance]") {
    instance inst0;
    CHECK_FALSE(inst0);

    instance::descriptor desc {};
    instance inst1(desc);
    CHECK(inst1);

    inst0 = std::move(inst1);
    CHECK(inst0);
    CHECK_FALSE(inst1);
}

TEST_CASE("cast instance", "[instance]") {
    instance inst0;
    CHECK(static_cast<VkInstance>(inst0) == VK_NULL_HANDLE);

    instance::descriptor desc {};
    instance inst1(desc);
    CHECK(static_cast<VkInstance>(inst1) != VK_NULL_HANDLE);
}
