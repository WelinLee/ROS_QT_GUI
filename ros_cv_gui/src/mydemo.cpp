#include "../include/ros_cv_gui/mydemo.h"
#include "ros_cv_gui/ui_mydemo.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <yaml-cpp/yaml.h>

#define BOXFILTER       std::string("BoxFilter")
#define MEANBLUR        std::string("MeanBlur")
#define GAUSSIANBLUR    std::string("GaussianBlur")
#define ORIGIANIMG      std::string("Original")

mydemo::mydemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mydemo)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("ROS_CV GUI"));

    connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(slot_open()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(slot_quit()));
    connect(ui->pushButton_save, SIGNAL(clicked()), this, SLOT(slot_save()));
    connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(slot_toggle1(bool)));
    connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(slot_toggle2(bool)));
    connect(ui->radioButton_3, SIGNAL(toggled(bool)), this, SLOT(slot_toggle3(bool)));
    connect(ui->verticalSlider, &QSlider::valueChanged, this, &mydemo::slot_imgPro);

    ui->label_txt->setText(QString::fromStdString(ORIGIANIMG));

    int argc = 0; char **argv = NULL;
    ros::init(argc, argv, "ros_cv_gui");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    m_pub = it.advertise("img_proc/image", 1);

}

mydemo::~mydemo()
{
    delete ui;
}

void mydemo::slot_open()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("OpenImage"), ".", QString("Image Files (*.jpg *.png *.bmp)"));
    if(filename.right(4)==".jpg"||filename.right(4)==".png"||filename.right(4)==".bmp")
    {
        m_image = cv::imread(filename.toStdString());
        qDebug() << "image channels:" << m_image.channels();
        imageShow(m_image);
    }
    
    std::string yamlfile = "/home/user/param.yaml";
    YAML::Node yamlConfig = YAML::LoadFile(yamlfile);
    std::string str_param = yamlConfig["filter_type"].as<std::string>();
    int int_param = yamlConfig["value"].as<int>();
    if(BOXFILTER == str_param)
    {
        m_type = Box;
        ui->radioButton->setChecked(true);
        ui->label_txt->setText(QString::fromStdString(BOXFILTER));
    }
    else if(MEANBLUR == str_param)
    {
        m_type = Mean;
        ui->radioButton_2->setChecked(true);
        ui->label_txt->setText(QString::fromStdString(MEANBLUR));
    }
    else if(GAUSSIANBLUR == str_param)
    {
        m_type = Gaussian;
        ui->radioButton_3->setChecked(true);
        ui->label_txt->setText(QString::fromStdString(GAUSSIANBLUR));
    }
    else
    {
        m_type = Original;
        int_param = 0;
        ui->label_txt->setText(QString::fromStdString(ORIGIANIMG));
    }
    ui->verticalSlider->setValue(int_param);
    ui->lineEdit->setText(QString::number(int_param));

}

void mydemo::slot_toggle1(bool checked)
{
    if(checked)
    {
        m_type = Box;
        onBoxFilter(0);
        ui->verticalSlider->setValue(0);
        ui->lineEdit->setText(QString::number(0));
        ui->label_txt->setText(QString::fromStdString(BOXFILTER));
    }
}

void mydemo::slot_toggle2(bool checked)
{
    if(checked)
    {
        m_type = Mean;
        onMeanBlur(0);
        ui->verticalSlider->setValue(0);
        ui->lineEdit->setText(QString::number(0));
        ui->label_txt->setText(QString::fromStdString(MEANBLUR));
    }
}

void mydemo::slot_toggle3(bool checked)
{
    if(checked)
    {
        m_type = Gaussian;
        onGaussian(0);
        ui->verticalSlider->setValue(0);
        ui->lineEdit->setText(QString::number(0));
        ui->label_txt->setText(QString::fromStdString(GAUSSIANBLUR));
    }
}

void mydemo::slot_imgPro(int value)
{
    ui->lineEdit->setText(QString("%1").arg(ui->verticalSlider->value()));

    if(!m_image.data)
        return;

    switch(m_type)
    {
    case Box:
        onBoxFilter(value);
    case Mean:
        onMeanBlur(value);
    case Gaussian:
        onGaussian(value);
    default:
        break;
    }

}

void mydemo::onBoxFilter(int value)
{
    cv::Mat dstImage;
    cv::boxFilter(m_image, dstImage, -1, cv::Size(value+1,value+1));
    imageShow(dstImage);
}

void mydemo::onMeanBlur(int value)
{
    cv::Mat dstImage;
    cv::blur(m_image, dstImage, cv::Size(value+1,value+1), cv::Point(-1,-1));
    imageShow(dstImage);
}

void mydemo::onGaussian(int value)
{
    cv::Mat dstImage;
    cv::GaussianBlur(m_image, dstImage, cv::Size(value*2+1,value*2+1), 0, 0);
    imageShow(dstImage);
}

void mydemo::imageShow(cv::Mat matImg)
{
    sensor_msgs::ImagePtr msg;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", matImg).toImageMsg();
    m_pub.publish(msg);

    cv::Mat showImg;
    cv::cvtColor(matImg, showImg, CV_BGR2RGB);
    m_qImg = QImage((const unsigned char*)(showImg.data), showImg.cols, showImg.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(m_qImg));
}

void mydemo::slot_save()
{
    std::string yamlfile = "/home/user/param.yaml";
    YAML::Node yamlConfig = YAML::LoadFile(yamlfile);
    yamlConfig["value"] = ui->verticalSlider->value();
    yamlConfig["filter_type"] = (ui->label_txt->text()).toStdString();

    std::ofstream file;
    file.open(yamlfile.c_str());
    file.flush();
    file << yamlConfig;
    file.close();
}

void mydemo::slot_quit()
{
    this->close();
}
