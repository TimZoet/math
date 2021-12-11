import re

from conans import ConanFile
from conans.tools import load
from conan.tools.cmake import CMakeToolchain, CMake
from conan.tools.layout import cmake_layout

def get_version():
    try:
        content = load("modules/math/mathVersionString.cmake")
        version = re.search("set\(MATH_VERSION (\d+\.\d+\.\d+)\)", content).group(1)
        return version.strip()
    except Exception as e:
        return None

class MathConan(ConanFile):
    name = "math"
    version = get_version()

    # Optional metadata
    license = "GNU AFFERO GENERAL PUBLIC LICENSE Version 3"
    author = "Tim Zoet"
    url = "https://github.com/TimZoet/math"
    description = "C++ math library."

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"fPIC": [True, False]}
    default_options = {"fPIC": True}

    exports_sources = "CMakeLists.txt", "readme.md", "cmake/*", "modules/CMakeLists.txt", "modules/math/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["math"]
