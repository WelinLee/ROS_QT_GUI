#include "widget.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <std_msgs/Int8.h>

Widget::Widget(int argc, char **argv, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init_ros(argc, argv);

    QObject::connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(slot_btn_start()));
    QObject::connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(slot_btn_quit()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_ros(int argc, char **argv)
{
    ros::init(argc, argv, "ros_cmake");
    ros::NodeHandle private_nh("~");
    test_pub_ = private_nh.advertise<std_msgs::Int8>("test", 1000);
}

void Widget::slot_btn_start()
{
    static int i = 0;
    std_msgs::Int8 msg;
    msg.data = i;
    test_pub_.publish(msg);
    i++;
    ui->lineEdit->setText(QString::number(i));
}

void Widget::slot_btn_quit()
{
    this->close();
}

void Widget::closeEvent(QCloseEvent *ev)
{
    int result = QMessageBox::question(this, QString("Tips"), QString("Dialog is closing..."));
    if(QMessageBox::Yes == result)
        ev->accept();
    else
        ev->ignore();
}
