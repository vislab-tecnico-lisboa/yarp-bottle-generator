cmake_minimum_required(VERSION 2.8.7)

# find YARP
find_package(YARP REQUIRED)

# add YARP include directories
include_directories(${YARP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# set up our program
add_executable(generatedCode generatedCode.cpp)

# link with YARP libraries
target_link_libraries(generatedCode ${YARP_LIBRARIES})