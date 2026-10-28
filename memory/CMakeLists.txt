cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wdeprecated -fsanitize=undefined")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# Add executable
add_executable(main main.cpp world.cpp)

# Add test executable
add_executable(test test_world.cpp world.cpp)
target_link_libraries(test gtest)

# Set test flags
set_property(TARGET test PROPERTY CXX_FLAGS "-fsanitize=undefined")

# Add custom target for formatting
add_custom_target(format
    COMMAND clang-format --style=file -i *.cpp *.h
)

# Add custom target for valgrind
add_custom_target(valgrind
    COMMAND valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-origins=yes --track-fds=yes -s ./main
    DEPENDS main
)
