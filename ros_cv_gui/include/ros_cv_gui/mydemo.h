#ifndef MYDEMO_H
#define MYDEMO_H

#include <QWidget>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

namespace Ui {
class mydemo;
}

class mydemo : public QWidget
{
    Q_OBJECT

public:
    explicit mydemo(QWidget *parent = 0);
    ~mydemo();

enum FilterType{
    Box,
    Mean,
    Gaussian,
    Original
};

private slots:
    void slot_open();
    void slot_imgPro(int value);
    void slot_save();
    void slot_quit();
    void slot_toggle1(bool checked);
    void slot_toggle2(bool checked);
    void slot_toggle3(bool checked);

private:
    void imageShow(cv::Mat matImg);
    void onBoxFilter(int value);
    void onMeanBlur(int value);
    void onGaussian(int value);

private:
    Ui::mydemo *ui;
    image_transport::Publisher m_pub;
    QImage m_qImg;
    cv::Mat m_image;
    FilterType m_type;
};

#endif // MYDEMO_H
