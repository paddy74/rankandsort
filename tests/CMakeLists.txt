message(STATUS "Preparing tests")

# Enable construction of test target
enable_testing()

# Create and link the test executables
add_executable(rankandsort.test_main src/test_main.cpp)
target_link_libraries(rankandsort.test_main rankandsort)

# Test definitions
macro(create_test target)
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro(create_test)

create_test(rankandsort.test_main)

message(STATUS "Preparing tests - done")
