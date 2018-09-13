/**
 * @file /include/editor_string.h
 *
 * @brief Qt based gui for EditorString.
 *
 * @date July 2018
 **/
#ifndef EDITORSTRING_H
#define EDITORSTRING_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtWidgets/QWidget>
#include <QObject>
#include "dyn_cfg_gui/ui_editor_string.h"

/*****************************************************************************
** Interface [EditorString]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class EditorString : public QWidget
{
    Q_OBJECT

public:
    struct ParamDesc
    {
        std::string name;
        std::string text;
        std::string describe;

        ParamDesc()
        {
            name = "";
            text = "";
            describe = "";
        }
    };

    EditorString(ParamDesc desc, QWidget *parent = 0)
        : QWidget(parent), m_desc(desc)
    {
        ui.setupUi(this);

        ui._paramname_label->setText(QString::fromStdString(m_desc.name));
        ui._paramval_lineedit->setText(QString::fromStdString(m_desc.text));

        this->setToolTip(QString::fromStdString(m_desc.describe));
    }

    ~EditorString(){}

private slots:


private:
    Ui::EditorString ui;
    ParamDesc m_desc;
};

#endif // EDITORSTRING_H
