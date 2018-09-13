cmake_minimum_required(VERSION 2.8.3)
project(dyn_cfg_gui)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)
add_definitions(-Wall)
add_definitions(-O0)
add_definitions(-g)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  dynamic_reconfigure
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)   # Qt Environment


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()


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
#  LIBRARIES dyn_cfg_gui
#  CATKIN_DEPENDS other_catkin_pkg
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
  ${catkin_LIBRARY_DIRS}
)

##############################################################################
# Sections
##############################################################################
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/*.h)
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)

QT5_WRAP_CPP(QT_MOC_H ${QT_MOC})
QT5_WRAP_UI(QT_FORMS_H ${QT_FORMS})
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})

##############################################################################
# Sources
##############################################################################
file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

## Declare a C++ library
# add_library(dyn_cfg_gui
#   src/${PROJECT_NAME}/dyn_cfg_gui.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(dyn_cfg_gui ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## Specify libraries to link a library or executable target against
add_executable(${PROJECT_NAME}  ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_H} ${QT_MOC_H})
target_link_libraries(${PROJECT_NAME}  ${catkin_LIBRARIES} Qt5::Core Qt5::Gui Qt5::Widgets)

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(dyn_cfg_gui_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

