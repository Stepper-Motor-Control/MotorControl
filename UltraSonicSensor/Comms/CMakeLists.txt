# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (PositionMotor LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (Communication 
             STATIC
             Task.cpp
             Comms.cpp
             Client.cpp
             )


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (Communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

