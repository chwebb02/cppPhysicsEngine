# Add test executables
add_executable(test_colliders test_colliders.cpp)

# Link Libraries
target_link_libraries(test_colliders Physics Geometry gtest pthread)