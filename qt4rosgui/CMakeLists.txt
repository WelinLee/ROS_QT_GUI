cmake_minimum_required(VERSION 2.8.3)
project(qt4rosgui)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -rdynamic -Wall -O0 -std=c++11") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -rdynamic -Wall -O0") 
add_definitions(-std=c++11)
add_definitions(-Wall)
add_definitions(-O0)
add_definitions(-g)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

## System dependencies are found with CMake's conventions
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
include(${QT_USE_FILE})
qt4_wrap_ui(UIC ui/qt4test.ui)
qt4_wrap_cpp(MOC include/qt4test.h)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
   INCLUDE_DIRS include
#  LIBRARIES qt4rosgui
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    include
    ${CMAKE_CURRENT_BINARY_DIR}/..
    /usr/included/qt4
)


## Declare a C++ executable
add_executable(qt4rosgui_node src/main.cpp src/qt4test.cpp ${MOC} ${UIC})
target_link_libraries(qt4rosgui_node ${catkin_LIBRARIES} ${QT_LIBRARIES})

