/**
 * @file /src/param_widget.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date July 2018
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include <iostream>
#include <QIcon>
#include <QFont>
#include <QtWidgets/QFileDialog>
#include "../include/param_widget.h"

/*****************************************************************************
** Implementation [ParamWidget]
*****************************************************************************/
ParamWidget::ParamWidget(QString title, QWidget *parent)
    : QWidget(parent), m_nodename(title)
{
    m_vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    m_savebtn = new QPushButton(QIcon(QString(":/images/save.png")), "");
    m_loadbtn = new QPushButton(QIcon(QString(":/images/open.png")), "");
    m_closebtn = new QToolButton();
    m_closebtn->setIcon(QIcon(QString(":/images/close.png")));

    QLabel *label = new QLabel();
    QFont font("Trebuchet MS, Bold");
    font.setUnderline(true);
    font.setBold(true);
    label->setFont(font);
    label->setText(title.remove("/parameter_updates"));

    hLayout->addWidget(m_savebtn);
    hLayout->addWidget(m_loadbtn);
    hLayout->addStretch();
    hLayout->addWidget(label);
    hLayout->addStretch();
    hLayout->addWidget(m_closebtn);

    m_vLayout->addLayout(hLayout);
    this->setLayout(m_vLayout);

    QObject::connect(m_savebtn, SIGNAL(clicked()), this, SLOT(slot_btn_save()));
    QObject::connect(m_loadbtn, SIGNAL(clicked()), this, SLOT(slot_btn_load()));
    QObject::connect(m_closebtn, SIGNAL(clicked()), this, SLOT(slot_btn_close()));

    m_widgetLS.clear();
}

ParamWidget::~ParamWidget()
{

}

void ParamWidget::addCustomLayout(QWidget *widget)
{
    m_vLayout->addWidget(widget);
    m_widgetLS.append(widget);
}

void ParamWidget::rmCustomLayout()
{
    foreach (QWidget *widget, m_widgetLS)
    {
        m_vLayout->removeWidget(widget);
        delete widget;
        widget = NULL;
    }
    m_widgetLS.clear();
}

void ParamWidget::slot_btn_save()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save parmeters to file..."), ".",
                                                    tr("YAML files {.yaml} (*.yaml)"));
    if(!filename.isEmpty())
    {}
}

void ParamWidget::slot_btn_load()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Load from File"), ".",
                                                    tr("YAML files {.yaml} (*.yaml)"));
    if(!filename.isEmpty())
    {}
}

void ParamWidget::slot_btn_close()
{
    emit signal_removenode(m_nodename);
    this->close();
}
