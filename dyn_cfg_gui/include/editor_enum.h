/**
 * @file /include/editor_enum.h
 *
 * @brief Qt based gui for EditorEnum.
 *
 * @date July 2018
 **/
#ifndef EDITORENUM_H
#define EDITORENUM_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtWidgets/QWidget>
#include <QObject>
#include "dyn_cfg_gui/ui_editor_enum.h"

/*****************************************************************************
** Interface [EditorString]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class EditorEnum : public QWidget
{
    Q_OBJECT

public:
    EditorEnum(QWidget *parent = 0):QWidget(parent)
    {
        ui.setupUi(this);
    }

    ~EditorEnum(){}

private slots:


private:
    Ui::EditorEnum ui;
};

#endif // EDITORENUM_H
