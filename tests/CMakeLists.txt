add_executable(rankandsort.test_main src/test_main.cpp)

target_link_libraries(rankandsort.test_main rankandsort)
target_link_libraries(rankandsort.test_main lowletorfeats)
target_link_libraries(rankandsort.test_main textalyzer)

enable_testing()
add_test(test_main rankandsort.test_main)
