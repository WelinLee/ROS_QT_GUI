/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date July 2018
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include <ros/ros.h>
#include "../include/dyn_cfg_gui.h"

/*****************************************************************************
** Main
*****************************************************************************/
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    DynRecfgWidget w(argc, argv);
    w.show();
    return app.exec();
}
