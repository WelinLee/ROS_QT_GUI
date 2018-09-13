/**
 * @file /include/editor_number.h
 *
 * @brief Qt based gui for EditorNumber.
 *
 * @date July 2018
 **/
#ifndef EDITORNUMBER_H
#define EDITORNUMBER_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtWidgets/QWidget>
#include <QObject>
#include <QSlider>
#include "dyn_cfg_gui/ui_editor_number.h"

/*****************************************************************************
** Interface [EditorNumber]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class EditorNumber : public QWidget
{
    Q_OBJECT

public:
    struct ParamDesc
    {
        std::string name;
        int value;
        int minvalue;
        int maxvalue;
        std::string describe;

        ParamDesc()
        {
            name = "";
            value = 0; minvalue = -99; maxvalue = 99;
            describe = "";
        }
    };

    EditorNumber(ParamDesc desc, QWidget *parent = 0)
        : QWidget(parent), m_desc(desc)
    {
        ui.setupUi(this);

        ui._paramname_label->setText(QString::fromStdString(m_desc.name));
        ui._min_val_label->setText(QString::number(m_desc.minvalue));
        ui._max_val_label->setText(QString::number(m_desc.maxvalue));
        ui._slider_horizontal->setValue(m_desc.value);

        int sliderVal = ui._slider_horizontal->value();
        ui._paramval_lineEdit->setText(QString::number(sliderVal));

        this->setToolTip(QString::fromStdString(m_desc.describe));

        QObject::connect(ui._slider_horizontal, SIGNAL(valueChanged(int)), this, SLOT(slot_slider_changed(int)));
    }

    ~EditorNumber(){}

private slots:
    void slot_slider_changed(int value)
    {
        ui._paramval_lineEdit->setText(QString::number(value));
    }

private:
    Ui::EditorNumber ui;
    ParamDesc m_desc;
};

#endif // EDITORNUMBER_H
