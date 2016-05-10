include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
add_executable(BrainfuckTests tests.cpp)
target_link_libraries(BrainfuckTests brainfuck)
