cmake_minimum_required(VERSION 2.8.11)
project(rqt_mypkg)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rqt_gui
  rqt_gui_cpp
  std_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
  find_package(Qt5Widgets REQUIRED)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
catkin_python_setup()


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
# INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp std_msgs
#  DEPENDS system_lib
)

set (rqt_mypkg_cpp_SRCS
  src/my_plugin.cpp
)
set(rqt_mypkg_cpp_HDRS
  include/my_plugin.h
)
set(rqt_mypkg_cpp_UIS
  ui/my_plugin.ui
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION}" STREQUAL "5")
  qt5_wrap_cpp(rqt_mypkg_cpp_MOCS ${rqt_mypkg_cpp_HDRS})
  qt5_wrap_ui(rqt_mypkg_cpp_UIS_H ${rqt_mypkg_cpp_UIS})
else()
  qt4_wrap_cpp(rqt_mypkg_cpp_MOCS ${rqt_mypkg_cpp_HDRS})
  qt4_wrap_ui(rqt_mypkg_cpp_UIS_H ${rqt_mypkg_cpp_UIS})
endif()

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
    ${rqt_mypkg_cpp_SRCS}
    ${rqt_mypkg_cpp_MOCS}
    ${rqt_mypkg_cpp_UIS_H}
)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
if("${qt_gui_cpp_USE_QT_MAJOR_VERSION}" STREQUAL "5")
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
else()
  target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()

#############
## Install ##
#############

## Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES
   plugin.xml
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_install_python(PROGRAMS scripts/rqt_mypkg
    DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

