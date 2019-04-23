add_executable(fullccrank.test_main src/main.cpp)

target_link_libraries(fullccrank.test_main fullccrank)

enable_testing()
add_test(test_main fullccrank.test_main)
