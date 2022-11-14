# CMakeList.txt : CMake project for TitanLauncher, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# Add source to this project's executable.
add_executable (TitanLauncher WIN32 "TitanLauncher.cpp")

target_link_libraries(TitanLauncher glfw nlohmann_json wx::net wx::core wx::base)

# TODO: Add tests and install targets if needed.
