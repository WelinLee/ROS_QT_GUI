/**
 * @file /include/editor_decimal.h
 *
 * @brief Qt based gui for EditorDecimal.
 *
 * @date July 2018
 **/
#ifndef EDITORDECIMAL_H
#define EDITORDECIMAL_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtWidgets/QWidget>
#include <QObject>
#include "dyn_cfg_gui/ui_editor_decimal.h"

/*****************************************************************************
** Interface [EditorDecimal]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class EditorDecimal : public QWidget
{
    Q_OBJECT

public:
    struct ParamDesc
    {
        std::string name;
        double value;
        double minvalue;
        double maxvalue;
        std::string describe;

        ParamDesc()
        {
            name = "";
            value = 0; minvalue = -99.99; maxvalue = 99.99;
            describe = "";
        }
    };

    EditorDecimal(ParamDesc desc, QWidget *parent = 0)
        : QWidget(parent), m_desc(desc)
    {
        ui.setupUi(this);

        ui._paramname_label->setText(QString::fromStdString(m_desc.name));
        ui._min_val_label->setText(QString::number(m_desc.minvalue));
        ui._max_val_label->setText(QString::number(m_desc.maxvalue));
        ui.doubleSpinBox->setValue(m_desc.value);

        this->setToolTip(QString::fromStdString(m_desc.describe));
    }

    ~EditorDecimal(){}

private slots:


private:
    Ui::EditorDecimal ui;
    ParamDesc m_desc;
};

#endif // EDITORDECIMAL_H
