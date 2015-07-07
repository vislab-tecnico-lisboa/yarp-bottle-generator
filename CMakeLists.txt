cmake_minimum_required(VERSION 2.8.7)

# Project name
PROJECT(YarpBottleGenerator)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

# Check if package is installed
find_package(Boost REQUIRED system filesystem)

# Path to the includes
include_directories(include)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# Setting both the cpp's and hpp's for the new library
set(YarpBottleGeneratorSource  src/yarpcodegenerator.cpp
                               src/commonbeginninggenerator.cpp
                               src/portmuxgenerator.cpp
                               src/dataconvertergenerator.cpp
                               src/commonendgenerator.cpp
                               src/bottlecreatorgenerator.cpp
                               src/childgenerator.cpp)

set(YarpBottleGeneratorHeaders include/yarpcodegenerator.hpp
                               include/commonbeginninggenerator.hpp
                               include/portmuxgenerator.hpp
                               include/dataconvertergenerator.hpp
                               include/commonendgenerator.hpp
                               include/bottlecreatorgenerator.hpp
                               include/childgenerator.hpp)

# Create the 'libYarpBottleGenerator' shared library with the source and header files
add_library(YarpBottleGenerator SHARED ${YarpBottleGeneratorSource} ${YarpBottleGeneratorHeaders})
#target_link_libraries(YarpBottleGenerator ${Boost_LIBRARIES})

# Create the 'yarpBottleGenerator' executable
add_executable(yarpBottleGenerator src/main.cpp)

# Link executable and libraries
target_link_libraries(yarpBottleGenerator YarpBottleGenerator ${Boost_LIBRARIES})

# Option to run sudo make install
install(TARGETS YarpBottleGenerator DESTINATION lib)
install(TARGETS yarpBottleGenerator DESTINATION bin)
