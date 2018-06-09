#include "include/qt4test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt4Test w;
    w.show();

    return a.exec();
}
