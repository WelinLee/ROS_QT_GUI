## Author
- **Welin**  2018.02.23
- modified in 2018.03.31

## Description
* In this project, three approaches are provided to implement ROS&Qt GUI and another two projects for PyQt GUI.
* In the test_gui folder, it just modified the example in catkin_create_qt_pkg depending on qt_build.
* In the rqt_mypkg folder, it is the C++ rqt_plugin test depending on rqt_gui_cpp.
* In the qt_ros_test folder, it combines ROS with Qt library.

The above three are written in C++ programmer.
The following two below are written in Python.

* In the ros_pyqt folder, it use PyQt to implement the GUI.
* In the pyqt_gui folder, it use PyQt and python_qt_binding to implement the GUI.


In the qt4rosgui folder, it use Qt4 libraries to implement the ROS-GUI not depends on qt-ros package.

## TODO
```sh
    $ mkdir -p catkin_ws/src
    $ cd catkin_ws/src
```

git clone the project from the corrent URL

```sh
    $ cd ..
    $ catkin_make
    $ source devel/setup.bash
```

Then, rosrun test_gui test_gui *or* rosrun qt_ros_test qt_ros_test_node *or* rosrun qt4rosgui qt4rosgui_node.

To run the rqt_mypkg, just open rqt, and the "rqt first C++ plugin" could be found in the Plugins menu.

To run ros_pyqt *or* pyqt_gui, just using the command *python ros_pyqt* or *python pyqt_gui*.

