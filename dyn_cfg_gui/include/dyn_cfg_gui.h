/**
 * @file /include/dyn_cfg_gui.h
 *
 * @brief Qt based gui for DynRecfgWidget.
 *
 * @date July 2018
 **/
#ifndef DYNRECFGWIDGET_H
#define DYNRECFGWIDGET_H

/*****************************************************************************
** Includes
*****************************************************************************/
#include <QtWidgets/QWidget>
#include <QObject>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "dyn_cfg_gui/ui_dyn_cfg_gui.h"
#include <iostream>
#include <vector>
#include <dynamic_reconfigure/Config.h>
#include "editor_bool.h"
#include "editor_number.h"
#include "editor_decimal.h"
#include "editor_string.h"
#include "rosthread.h"
#include "param_widget.h"

/*****************************************************************************
** Interface [DynRecfgWidget]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class DynRecfgWidget : public QWidget
{
    Q_OBJECT

public:
    DynRecfgWidget(int argc, char **argv, QWidget *parent = 0);
    ~DynRecfgWidget();

    void ros_init(int argc, char **argv);

private slots:
    void slot_btn_refresh();
    void slot_btn_collapse();
    void slot_btn_expand();
    void slot_selected_node(const QModelIndex &index);
    void slot_txt_filter(const QString &text);
    void slot_addparamui(const QString &topicname, const RecfgMsgVal &msg);
    void slot_removenode(QString name);

private:
    bool find_dynmaic_services(std::vector<std::string> &srvls);
    void rosrunthread();

private:
    Ui::DynRecfgWidget ui;
    QStandardItemModel *m_model;
    QSortFilterProxyModel *m_proxyModel;
    QString selected_node__;
    QStringList nodelist__;
    bool isSelectedNode__;
    RosThread *m_rosthread;
    QMap<QString, ParamWidget*> m_paramMap;
};

#endif // DYNRECFGWIDGET_H
