message(STATUS "Generating samples")

add_executable(rankandsort.example src/example.cpp)
target_link_libraries(rankandsort.example rankandsort)

message(STATUS "Generating samples - done")
