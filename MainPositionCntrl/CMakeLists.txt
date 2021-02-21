# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (MainPositionMotor LANGUAGES CXX)

# Setup Debug flag
set(CMAKE_BUILD_TYPE Debug)

# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (MainPositionMotor MainCode.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (MainPositionMotor LINK_PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../PositionMotor/src/libPositionMotorLib.a -lwiringPi)
# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (MainPositionMotor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../PositionMotor/include)
target_include_directories (MainPositionMotor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../PositionMotor/src)

