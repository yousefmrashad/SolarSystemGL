cmake_minimum_required(VERSION 3.24)
project(SolarSystemGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(SolarSystemGL main.cpp)

# Set the CMake toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Find the FreeGLUT package
find_package(freeglut REQUIRED)

# Link the executable with FreeGLUT
target_link_libraries(SolarSystemGL
        $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>
        OpenGL32
        GlU32
        )
