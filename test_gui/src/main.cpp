/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date February 2018
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtGui>
#include <QApplication>
#include "../include/test_gui/main_window.hpp"

/*****************************************************************************
** Main
*****************************************************************************/
int main(int argc, char **argv)
{
    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    test_gui::MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

    return result;
}
