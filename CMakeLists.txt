cmake_minimum_required(VERSION 2.8.7)

# Project name
PROJECT(YarpBottleGenerator)

# Check if package is installed
#find_package(Boost REQUIRED serialization system)

# Path to the includes
include_directories(include)
#include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# Setting both the cpp's and hpp's for the new library
set(YarpBottleGeneratorSource  src/yarpcodegenerator.cpp
                               src/commonbeginninggenerator.cpp
                               src/portmuxgenerator.cpp
                               src/commonendgenerator.cpp)

set(YarpBottleGeneratorHeaders include/yarpcodegenerator.hpp
                               include/commonbeginninggenerator.hpp
                               include/portmuxgenerator.hpp
                               include/commonendgenerator.hpp)

# Create the 'libYarpBottleGenerator' shared library with the source and header files
add_library(YarpBottleGenerator SHARED ${YarpBottleGeneratorSource} ${YarpBottleGeneratorHeaders})
#target_link_libraries(YarpBottleGenerator ${Boost_LIBRARIES})

# Create the 'yarpBottleGenerator' executable
add_executable(yarpBottleGenerator src/main.cpp)

# Link executable and libraries
target_link_libraries(yarpBottleGenerator YarpBottleGenerator)

# Option to run sudo make install
install(TARGETS yarpBottleGenerator DESTINATION bin)