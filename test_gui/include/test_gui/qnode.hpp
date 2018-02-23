/**
 * @file /include/test_gui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2018
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/
#ifndef test_gui_QNODE_HPP_
#define test_gui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <string>
#include <QThread>
#include <QStringListModel>

/*****************************************************************************
** Namespaces
*****************************************************************************/
namespace test_gui
{

/*****************************************************************************
** Class
*****************************************************************************/
class QNode : public QThread
{
    Q_OBJECT
public:
    QNode(int argc, char** argv);
    virtual ~QNode();
    bool init();
    bool init(const std::string &master_url, const std::string &host_url);
    void run();

    /*********************
    ** Logging
    **********************/
    enum LogLevel
    {
        Debug,
        Info,
        Warn,
        Error,
        Fatal
    };

    QStringListModel* loggingModel()
        {return &logging_model;}
    void log( const LogLevel &level, const std::string &msg);

    void RecvTopicCallback(const std_msgs::StringConstPtr &msg);
    QStringListModel* loggingModelLis()
        {return &logging_listen;}
    void log_listen(const LogLevel &level, const std::string &msg);

Q_SIGNALS:
    void loggingUpdated();
    void loggingListen();
    void rosShutdown();

private:
    int init_argc;
    char** init_argv;
    ros::Publisher chatter_publisher;
    ros::Subscriber chatter_subscriber;
    QStringListModel logging_model;
    QStringListModel logging_listen;
};

}  // namespace test_gui

#endif /* test_gui_QNODE_HPP_ */
