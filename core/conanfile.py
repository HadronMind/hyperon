import os
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import load

required_conan_version = ">=2.0.4"


class hyperkdb_coreRecipe(ConanFile):
    name = "hyperkdb_core"
    version = "1.0"

    # Optional metadata
    license = "Apache 2.0"
    author = "xiaming.chen"
    url = "https://github.com/HyperKB/hyperkb"
    description = "Knowledge base"
    topics = ("Knowledge Base", "Hypergraph", "AGI")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("fmt/9.1.0")
        self.requires("glog/0.6.0")

    def build_requirements(self):
        self.test_requires("gtest/1.13.0")

    def layout(self):
        cmake_layout(self)
        self.folders.root = "."
        self.folders.source = "."
        self.folders.build = "build"
        self.folders.generators = "build"

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        path = os.path.join(self.source_folder, "CMakeLists.txt")
        cmake_file = load(self, path)
        cmake = CMake(self)
        #cmake.definitions['CMAKE_EXPORT_COMPILE_COMMANDS'] = "ON"
        cmake.configure(cli_args=["-GNinja"])
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["hyperkdb_core"]





