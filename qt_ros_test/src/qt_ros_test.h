#ifndef QT_ROS_TEST_H
#define QT_ROS_TEST_H

#include <QWidget>
#include <ros/ros.h>

namespace Ui {
class Qt_Ros_Test;
}

class Qt_Ros_Test : public QWidget
{
    Q_OBJECT

public:
    explicit Qt_Ros_Test(QWidget *parent = 0);
    ~Qt_Ros_Test();

private slots:
    void on_slider_value_change(int value);

private:
    Ui::Qt_Ros_Test *ui;
    ros::Publisher chatter_publisher;
};

#endif // QT_ROS_TEST_H
