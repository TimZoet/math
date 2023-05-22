from conan import ConanFile
from conan.tools.files import copy

class MathConan(ConanFile):
    ############################################################################
    ## Package info.                                                          ##
    ############################################################################
    
    name = "math"
    
    description = "C++ math library."
    
    url = "https://github.com/TimZoet/math"
    
    @property
    def user(self):
        return getattr(self, "_user", "timzoet")
    
    @user.setter
    def user(self, value):
        self._user = value
    
    @property
    def channel(self):
        return getattr(self, "_channel", f"v{self.version}")
    
    @channel.setter
    def channel(self, value):
        self._channel = value

    ############################################################################
    ## Settings.                                                              ##
    ############################################################################

    python_requires = "pyreq/1.0.1@timzoet/v1.0.1"
    
    python_requires_extend = "pyreq.BaseConan"
    
    ############################################################################
    ## Base methods.                                                          ##
    ############################################################################
    
    def set_version(self):
        base = self.python_requires["pyreq"].module.BaseConan
        base.set_version(self, "mathVersionString.cmake", "MATH_VERSION")
    
    def init(self):
        base = self.python_requires["pyreq"].module.BaseConan
        self.settings = base.settings
        self.options.update(base.options, base.default_options)
    
    ############################################################################
    ## Building.                                                              ##
    ############################################################################
    
    def export_sources(self):
        copy(self, "CMakeLists.txt", self.recipe_folder, self.export_sources_folder)
        copy(self, "license", self.recipe_folder, self.export_sources_folder)
        copy(self, "mathVersionString.cmake", self.recipe_folder, self.export_sources_folder)
        copy(self, "readme.md", self.recipe_folder, self.export_sources_folder)
        copy(self, "modules/*", self.recipe_folder, self.export_sources_folder)
    
    def config_options(self):
        base = self.python_requires["pyreq"].module.BaseConan
        if self.settings.os == "Windows":
            del self.options.fPIC
    
    def requirements(self):
        base = self.python_requires["pyreq"].module.BaseConan
        base.requirements(self)
        
        if self.options.build_tests:
            self.requires("bettertest/1.0.0@timzoet/stable")
    
    def package_info(self):
        self.cpp_info.libs = ["math"]
    
    def generate(self):
        base = self.python_requires["pyreq"].module.BaseConan
        
        tc = base.generate_toolchain(self)
        tc.generate()
        
        deps = base.generate_deps(self)
        deps.generate()
    
    def configure_cmake(self):
        base = self.python_requires["pyreq"].module.BaseConan
        cmake = base.configure_cmake(self)
        return cmake

    def build(self):
        base = self.python_requires["pyreq"].module.BaseConan
        cmake = base.configure_cmake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        base = self.python_requires["pyreq"].module.BaseConan
        cmake = base.configure_cmake(self)
        cmake.install()
