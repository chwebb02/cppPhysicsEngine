# Version Requirement
cmake_minimum_required(VERSION 3.10)

# Project
project(PhysicsEngine VERSION 1.0)

add_executable(PhysicsEngine src/main.cpp)

# Include Directories
include_directories(include/)

# Libraries
add_library(Geometry src/vector.cpp)
add_library(Physics src/collider.cpp src/physObj.cpp src/vector.cpp)

# Linking
target_link_libraries(PhysicsEngine Geometry Physics)

# Executables
