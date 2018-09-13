#ifndef ROSTHREAD_H
#define ROSTHREAD_H

#include <QObject>
#include <QMap>
#include <QMetaType>
#include <boost/thread.hpp>
#include <iostream>
#include <ros/ros.h>
#include <dynamic_reconfigure/Config.h>

typedef dynamic_reconfigure::Config::ConstPtr RecfgMsgVal;

class RosThread : public QObject
{
    Q_OBJECT

public:
    RosThread(QObject *parent = 0);
    ~RosThread();

    void setServicesName(std::string srvname);
    void shutServicesUpdate(std::string srvname);

signals:
    void signal_recfg_msg(const QString &topicname, const RecfgMsgVal &msg);

private:
    void rosrunThread();
    //void subRecfgCallBack(const ros::MessageEvent<const dynamic_reconfigure::Config> &event);
    void subRecfgCallBack(const dynamic_reconfigure::Config::ConstPtr &msg, std::string srvname);

private:
    ros::NodeHandle *n_;
    bool m_isExt;
    boost::thread *m_ros_thread;
    ros::Subscriber m_subrecfg;
    QMap<std::string, ros::Subscriber> m_subMap;

};

#endif
