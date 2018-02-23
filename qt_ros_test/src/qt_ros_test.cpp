#include "qt_ros_test.h"
#include "qt_ros_test/ui_qt_ros_test.h"
#include <QString>
#include <std_msgs/String.h>

Qt_Ros_Test::Qt_Ros_Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Qt_Ros_Test)
{
    ui->setupUi(this);

    ui->lineEdit->setText(QString::number(ui->verticalSlider->value()));
    QObject::connect(ui->verticalSlider, SIGNAL(valueChanged(int)),
                     this, SLOT(on_slider_value_change(int)));

    int argc = 0; char **argv = NULL;
    ros::init(argc, argv, "client_plug");
    if (!ros::master::check())
    {
        ROS_INFO("No master started!");
        this->close();
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    chatter_publisher = n.advertise<std_msgs::String>("qtrostest_chat", 1000);
    //ros::spin();
}

Qt_Ros_Test::~Qt_Ros_Test()
{
    delete ui;
}

void Qt_Ros_Test::on_slider_value_change(int value)
{
    ui->lineEdit->setText(QString::number(value));

    std_msgs::String msg;
    std::stringstream ss;
    ss << "data: " << ui->verticalSlider->value();
    msg.data = ss.str();
    chatter_publisher.publish(msg);
}

