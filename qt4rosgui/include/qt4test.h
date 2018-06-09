#ifndef QT4_TEST_H
#define QT4_TEST_H

#include <QtGui/QWidget>
#include <QtCore/QString>
#include <ros/ros.h>

namespace Ui {
class Qt4Test;
}

class Qt4Test : public QWidget
{
    Q_OBJECT

public:
    explicit Qt4Test(QWidget *parent = 0);
    ~Qt4Test();

private slots:
    void slot_btn();
    void slot_btn2();

private:
    Ui::Qt4Test *ui;
    ros::Publisher chatter_pub_;

};

#endif // QT4_TEST_H
