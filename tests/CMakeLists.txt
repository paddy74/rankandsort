message(STATUS "Preparing tests")

# Enable construction of test target
enable_testing()

# Create a test target separate from registering the test
add_executable(rankandsort.test_main src/test_main.cpp)

target_link_libraries(rankandsort.test_main rankandsort)

# Add the test target
add_test(test_main rankandsort.test_main)

message(STATUS "Preparing tests - done")
