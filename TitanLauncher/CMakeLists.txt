# CMakeList.txt : CMake project for TitanLauncher, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (TitanLauncher "TitanLauncher.cpp" "TitanLauncher.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TitanLauncher PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(TitanLauncher glfw nlohmann_json)

# TODO: Add tests and install targets if needed.
