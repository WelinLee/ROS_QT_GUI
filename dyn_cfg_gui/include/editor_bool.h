/**
 * @file /include/editor_bool.h
 *
 * @brief Qt based gui for EditorBool.
 *
 * @date July 2018
 **/
#ifndef EDITORBOOL_H
#define EDITORBOOL_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtWidgets/QWidget>
#include <QObject>
#include "dyn_cfg_gui/ui_editor_bool.h"

/*****************************************************************************
** Interface [EditorBool]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class EditorBool : public QWidget
{
    Q_OBJECT

public:
    struct ParamDesc
    {
        std::string name;
        bool isChecked;
        std::string describe;

        ParamDesc()
        {
            name = "";
            isChecked = false;
            describe = "";
        }
    };

    EditorBool(ParamDesc desc, QWidget *parent = 0)
        : QWidget(parent), m_desc(desc)
    {
        ui.setupUi(this);

        ui._paramname_label->setText(QString::fromStdString(m_desc.name));
        ui._checkbox->setChecked(m_desc.isChecked);

        this->setToolTip(QString::fromStdString(m_desc.describe));
    }

    ~EditorBool(){}

private slots:


private:
    Ui::EditorBool ui;
    ParamDesc m_desc;
};

#endif // EDITORBOOL_H
