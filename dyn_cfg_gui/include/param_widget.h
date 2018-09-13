/**
 * @file /include/param_widget.h
 *
 * @brief Qt based gui for ParamWidget.
 *
 * @date July 2018
 **/
#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtWidgets/QWidget>
#include <QObject>
#include <QBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include "editor_bool.h"
#include "editor_number.h"
#include "editor_decimal.h"
#include "editor_string.h"

/*****************************************************************************
** Interface [ParamWidget]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class ParamWidget : public QWidget
{
    Q_OBJECT

public:
    ParamWidget(QString title, QWidget *parent = 0);
    ~ParamWidget();

    void addCustomLayout(QWidget *widget);
    void rmCustomLayout();

signals:
    void signal_removenode(QString nodename);

private slots:
    void slot_btn_load();
    void slot_btn_save();
    void slot_btn_close();

private:
    QVBoxLayout *m_vLayout;
    QPushButton *m_loadbtn;
    QPushButton *m_savebtn;
    QToolButton *m_closebtn;
    QString m_nodename;
    QList<QWidget*> m_widgetLS;
};

#endif // PARAMWIDGET_H
