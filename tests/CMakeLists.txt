# Add test executables
add_executable(test_colliders test_colliders.cpp)
add_executable(test_collisions test_collisions.cpp)
add_executable(test_lines test_lines.cpp)

# Link Libraries
target_link_libraries(test_colliders Physics Geometry gtest pthread)
target_link_libraries(test_collisions Physics Geometry gtest pthread)
target_link_libraries(test_lines Geometry gtest pthread)