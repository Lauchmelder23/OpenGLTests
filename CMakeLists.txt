# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenGLTests")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include sub-projects.
add_subdirectory ("src")
