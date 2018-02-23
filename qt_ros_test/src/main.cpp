#include "qt_ros_test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_Ros_Test w;
    w.show();

    return a.exec();
}
