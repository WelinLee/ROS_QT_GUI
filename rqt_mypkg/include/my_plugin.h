/*
  Copyright 2018
*/
#ifndef RQT_MYPKG_CPP_MY_PLUGIN_H
#define RQT_MYPKG_CPP_MY_PLUGIN_H

#include <ros/ros.h>
#include <rqt_gui_cpp/plugin.h>
#include <QWidget>
#include "rqt_mypkg/ui_my_plugin.h"

namespace rqt_mypkg_cpp
{

class MyPlugin : public rqt_gui_cpp::Plugin
{    
    Q_OBJECT
public:
    MyPlugin();
    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
    virtual void shutdownPlugin();

private slots:
    void on_slot_pub_topic();
    void on_slider_value_change(int value);

private:
    Ui::MyPluginWidget ui_;
    QWidget* widget_;
    ros::Publisher m_chatter;
};

}  // namespace rqt_mypkg_cpp

#endif  // RQT_MYPKG_CPP_MY_PLUGIN_H
