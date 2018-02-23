## Author
- **Welin**  2018.02.23

## Description
* In this project, three approaches are provided to implement ROS&Qt GUI.
* In the test_gui folder, it just modified the example in catkin_create_qt_pkg depending on qt_build.
* In the rqt_mypkg folder, it is the C++ rqt_plugin test depending on rqt_gui_cpp.
* In the qt_ros_test, it combines ROS with Qt library.

## TODO
```sh
    $ mkdir -p catkin_ws/src
    $ cd catkin_es/src
```

git clone the project from the corrent URL

```sh
    $ cd ..
    $ catkin_make
    $ source devel/setup.bash
```

Then, rosrun test_gui test_gui *or* rosrun qt_ros_test qt_ros_test_node.

To run the rqt_mypkg, just open rqt, and the "rqt first C++ plugin" could be found in the Plugins menu.


	