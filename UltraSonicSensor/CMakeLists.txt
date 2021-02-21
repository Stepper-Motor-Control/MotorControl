# CMakeLists files in this project can
cmake_minimum_required (VERSION 2.8.11)
project (UltraSonicSensor)

# Setup Debug flag
set(CMAKE_BUILD_TYPE Debug)

# Add directories 
add_subdirectory (Sensor)
add_subdirectory (Comms)

add_executable (SensorServer SensorServer.cpp   UltraSonicSensorMain.cpp SensorCommsServer.cpp)  

target_include_directories (Communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (Communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sensor)

target_link_libraries (SensorServer Sensor pthread wiringPi wiringPiDev ADCDevice Communication rt)    