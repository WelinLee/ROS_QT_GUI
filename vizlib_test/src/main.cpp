#include "vizlib_test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VizlibTest w(argc, argv);
    w.show();

    return a.exec();
}
