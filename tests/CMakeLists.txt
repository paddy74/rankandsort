message(STATUS "Preparing tests")

add_executable(rankandsort.test_main src/test_main.cpp)
add_executable(rankandsort.test_treelite src/test_treelite.cpp)

target_link_libraries(rankandsort.test_main lowletorfeats)
target_link_libraries(rankandsort.test_main textalyzer)
target_link_libraries(rankandsort.test_main rankandsort)

#target_link_libraries(rankandsort.test_treelite)

enable_testing()
add_test(test_main rankandsort.test_main)
add_test(test_treelite rankandsort.test_treelite)

message(STATUS "Preparing tests - done")
