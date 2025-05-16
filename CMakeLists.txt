cmake_minimum_required(VERSION 3.10)
project(cgmathdemo)

set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(include)

# Source files
add_executable(cgmathdemo
    src/main.cpp
    src/vector-math/vec2.cpp
    src/vector-math/vec3.cpp
    src/rendering/render.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link GLEW and GLFW
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Link all libraries
target_link_libraries(cgmathdemo
    PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glfw
)
