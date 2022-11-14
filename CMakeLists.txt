# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("TitanLauncher")

# Include sub-projects.
add_subdirectory ("TitanLauncher")
add_subdirectory ("3rdparty/json")
add_subdirectory ("3rdparty/glfw")
add_subdirectory ("3rdparty/wxwidgets")