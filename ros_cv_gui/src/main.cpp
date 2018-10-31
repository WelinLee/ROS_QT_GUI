#include "../include/ros_cv_gui/mydemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mydemo w;
    w.show();

    return a.exec();
}
