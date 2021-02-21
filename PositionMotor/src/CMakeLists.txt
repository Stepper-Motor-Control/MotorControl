# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (PositionMotor LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (CommsLib  
             STATIC
             Task.cpp
             Comms.cpp
             )

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (CommsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

      
# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (ReceiveData ReceiveDataServer.cpp PositionServoMotor.cpp)  
       
target_link_libraries (ReceiveData pthread CommsLib wiringPi)       


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (ReceiveData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

