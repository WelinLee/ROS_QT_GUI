#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QTimer>
#include <ros/ros.h>
#include "ui_widget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(int argc, char **argv, QWidget *parent = 0);
    ~Widget();

    void init_ros(int argc, char **argv);

private slots:
    void slot_btn_start();
    void slot_btn_quit();
    void slot_timer();

private:
    ros::Publisher test_pub_;
    QTimer *m_timer = nullptr;
    Ui::Widget *ui;

protected:
    virtual void closeEvent(QCloseEvent *ev);
};

#endif // WIDGET_H
