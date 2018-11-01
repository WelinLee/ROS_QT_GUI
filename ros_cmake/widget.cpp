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

    m_timer = new QTimer( this );
    QObject::connect( m_timer, SIGNAL(timeout()), this, SLOT(slot_timer()));
}

Widget::~Widget()
{
    delete m_timer;
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
    static bool flag = true;
    if(true == flag)
    {
        m_timer->start(1000);
        ui->pushButton_start->setText(QString("Stop"));
        flag = false;
    }
    else
    {
        m_timer->stop();
        ui->pushButton_start->setText(QString("Start"));
        flag = true;
    }
}

void Widget::slot_timer()
{
    static int i = 0;
    std_msgs::Int8 msg;
    msg.data = i;
    test_pub_.publish(msg);
    ui->lineEdit->setText(QString::number(i));
    i++;
}

void Widget::slot_btn_quit()
{
    if(m_timer->isActive())
        m_timer->stop();
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
