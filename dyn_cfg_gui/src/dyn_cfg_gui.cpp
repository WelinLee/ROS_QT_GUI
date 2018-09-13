/**
 * @file /src/dyn_cfg_gui.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date July 2018
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include <XmlRpcClient.h>
#include <QDebug>
#include "../include/dyn_cfg_gui.h"

/*****************************************************************************
** Implementation [DynRecfgWidget]
*****************************************************************************/
DynRecfgWidget::DynRecfgWidget(int argc, char **argv, QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_model = new QStandardItemModel(ui.treeView);
    m_model->setHorizontalHeaderLabels(QStringList() << QString("Dynamic Services"));
    m_proxyModel = new QSortFilterProxyModel;
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setFilterKeyColumn(0);
    ui.treeView->setModel(m_proxyModel);
    ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.treeView->header()->setDefaultAlignment(Qt::AlignHCenter);

    QObject::connect(ui.pushButton_refresh, SIGNAL(clicked()), this, SLOT(slot_btn_refresh()));
    QObject::connect(ui.pushButton_collapse, SIGNAL(clicked()), this, SLOT(slot_btn_collapse()));
    QObject::connect(ui.pushButton_expand, SIGNAL(clicked()), this, SLOT(slot_btn_expand()));
    QObject::connect(ui.treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_selected_node(QModelIndex)));
    QObject::connect(ui.lineEdit_filter, SIGNAL(textChanged(QString)), this, SLOT(slot_txt_filter(QString)));

    ros_init(argc, argv);
}

DynRecfgWidget::~DynRecfgWidget()
{
    delete m_rosthread;
}

void DynRecfgWidget::ros_init(int argc, char **argv)
{
    ros::init(argc, argv, "DynRecfgGui");
    selected_node__ = ""; nodelist__.clear(); isSelectedNode__ = false;
    m_rosthread = new RosThread;
    connect(m_rosthread, SIGNAL(signal_recfg_msg(QString, RecfgMsgVal)),
            this, SLOT(slot_addparamui(QString, RecfgMsgVal)));

    if(ros::ok())
        slot_btn_refresh();
}

bool DynRecfgWidget::find_dynmaic_services( std::vector<std::string> &srvls)
{
    srvls.clear();

    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();

    if (!ros::master::execute("getSystemState", args, result, payload, true))
    {
        ROS_ERROR("Execute ros system wrong!");
        return false;
    }

    //std::cout << "payload[2] (services) size: " << payload[2].size() << " \n";
    for (int i = 0; i < payload[2].size(); ++i)
    {
        XmlRpc::XmlRpcValue val = payload[2][i];
        std::string service_name = val[0];
        int index = service_name.find("/set_parameters");
        if(index > 0)    //not found index =  -1
        {
            std::string dynsrv_name = service_name.assign(service_name.c_str(), index);
            srvls.push_back(dynsrv_name);
            qDebug() << "dynamic service name: " << QString::fromStdString(dynsrv_name);
        }
    }
    return true;
}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/
void DynRecfgWidget::slot_btn_refresh()
{
    m_model->clear();
    m_model->setHorizontalHeaderLabels(QStringList() << QString("Dynamic Services"));

    std::vector<std::string> srvLists;
    if(!find_dynmaic_services(srvLists))
        return;

    if(srvLists.size() < 1)
        return;

    qDebug() << "Number of dynamic services: " << srvLists.size();
    for(unsigned int i = 0; i < srvLists.size(); i++)
    {
        QStandardItem *srvItem = new QStandardItem(QString::fromStdString(srvLists.at(i)));
        m_model->appendRow(srvItem);
    }
}

void DynRecfgWidget::slot_selected_node(const QModelIndex &index)
{
    QString node = index.data().toString();
    QString updatetopic = node + "/parameter_updates";
    m_rosthread->setServicesName(updatetopic.toStdString());

    if(selected_node__ == node)
        return;
    if(nodelist__.contains(node))
        return;

    selected_node__ = node;
    nodelist__.append(node);
}

void DynRecfgWidget::slot_txt_filter(const QString &text)
{
    QRegExp regExp(ui.lineEdit_filter->text(), Qt::CaseInsensitive, QRegExp::RegExp);   //CaseInsensitive has no capital letter
    m_proxyModel->setFilterRegExp(regExp);
}

void DynRecfgWidget::slot_btn_collapse()
{
    ui.treeView->collapseAll();
}

void DynRecfgWidget::slot_btn_expand()
{
    ui.treeView->expandAll();
}

void DynRecfgWidget::slot_removenode(QString name)
{
    m_rosthread->shutServicesUpdate(name.toStdString());
    m_paramMap.remove(name);

    nodelist__.removeOne(name);
    if(selected_node__ == name)
        selected_node__ = "";
}

void DynRecfgWidget::slot_addparamui(const QString &topicname, const RecfgMsgVal &msg)
{
    QString srvname = topicname;
    if(!m_paramMap.contains(srvname))
    {
        m_paramMap[srvname] = new ParamWidget(srvname);
        QObject::connect(m_paramMap[srvname] , SIGNAL(signal_removenode(QString)), this, SLOT(slot_removenode(QString)));
        ui.verticalLayout->addWidget(m_paramMap[srvname]);
    }
    else
    {
        m_paramMap[srvname]->rmCustomLayout();
    }

    for(unsigned int i = 0; i < msg->bools.size(); i++)
    {
        EditorBool::ParamDesc desc;
        desc.name = msg->bools[i].name;
        desc.isChecked = msg->bools[i].value;
        EditorBool *editbool = new EditorBool(desc);
        m_paramMap[srvname]->addCustomLayout(editbool);
    }
    for(unsigned int i = 0; i < msg->ints.size(); i++)
    {
        EditorNumber::ParamDesc desc;
        desc.name = msg->ints[i].name;
        desc.value = msg->ints[i].value;
        EditorNumber *editint = new EditorNumber(desc);
        m_paramMap[srvname]->addCustomLayout(editint);
    }
    for(unsigned int i = 0; i < msg->doubles.size(); i++)
    {
        EditorDecimal::ParamDesc desc;
        desc.name = msg->doubles[i].name;
        desc.value = msg->doubles[i].value;
        EditorDecimal *editdbl = new EditorDecimal(desc);
        m_paramMap[srvname]->addCustomLayout(editdbl);
    }
    for(unsigned int i = 0; i < msg->strs.size(); i++)
    {
        EditorString::ParamDesc desc;
        desc.name = msg->strs[i].name;
        desc.text = msg->strs[i].value;
        EditorString *editstr = new EditorString(desc);
        m_paramMap[srvname]->addCustomLayout(editstr);
    }
}
