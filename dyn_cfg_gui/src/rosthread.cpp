#include "../include/rosthread.h"
#include <iostream>

RosThread::RosThread(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<RecfgMsgVal>("RecfgMsgVal");

    m_isExt = false; m_ros_thread = NULL; m_subMap.clear();
    n_ = new ros::NodeHandle;
    m_ros_thread = new boost::thread(boost::bind(&RosThread::rosrunThread, this));
}

RosThread::~RosThread()
{
    m_isExt = true;
    if(m_ros_thread)
    {
        m_ros_thread->interrupt();
        m_ros_thread->join();
        delete m_ros_thread;
    }
    ROS_INFO("Ros shutdown, proceeding to close the gui.");
}

void RosThread::rosrunThread()
{
    ros::Duration initDur(0.2);
    while (ros::ok() && !m_isExt)
    {
        ros::spinOnce();
        initDur.sleep();
    }
    ROS_INFO("ros thread closing...");
}

void RosThread::setServicesName(std::string srvname)
{
    if(!m_subMap.contains(srvname))
    {
        ROS_INFO("sub service name: %s", srvname.c_str());
        ros::Subscriber sub = n_->subscribe<dynamic_reconfigure::Config>(srvname, 1000, boost::bind(&RosThread::subRecfgCallBack, this, _1, srvname));
        m_subMap.insert(srvname, sub);
    }
    else
        return;
}

void RosThread::shutServicesUpdate(std::string srvname)
{
    if(m_subMap.contains(srvname))
    {
        m_subMap[srvname].shutdown();
        m_subMap.remove(srvname);
        ROS_INFO("%s topic shut down.", srvname.c_str());
    }
    else
        return;
}

void RosThread::subRecfgCallBack(const dynamic_reconfigure::Config::ConstPtr &msg, std::string srvname)
{
//    const std::string &pub_name = event.getPublisherName();
//    const dynamic_reconfigure::ConfigConstPtr &msg = event.getMessage();
    emit signal_recfg_msg(QString::fromStdString(srvname), msg);
}
