#include "include/qt4test.h"
#include "qt4rosgui/ui_qt4test.h"
#include <QtCore/QDebug>
#include <std_msgs/Int8.h>


Qt4Test::Qt4Test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Qt4Test)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_btn()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slot_btn2()));

    int argc = 0; char **argv = nullptr;
    ros::init(argc, argv, "qt4test");
    ros::NodeHandle n;
    chatter_pub_ = n.advertise<std_msgs::Int8>("qt4pub", 1000);
}

Qt4Test::~Qt4Test()
{
    delete ui;
}

void Qt4Test::slot_btn()
{
    static int i = 0;
    std_msgs::Int8 msg;
    msg.data = i;
    chatter_pub_.publish(msg);
    i++;
    ui->lineEdit->setText(QString::number(i));
}

void Qt4Test::slot_btn2()
{
    qDebug() << "closed";
    this->close();
}
