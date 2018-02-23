/*
  Copyright 2018
*/

#include "my_plugin.h"
#include <std_msgs/String.h>
#include <pluginlib/class_list_macros.h>
#include <QStringList>

namespace rqt_mypkg_cpp
{

MyPlugin::MyPlugin()
    : rqt_gui_cpp::Plugin()
    , widget_(0)
{
    setObjectName("C++PluginT");
}

void MyPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
    // access standalone command line arguments
    QStringList argv = context.argv();
    // create QWidget
    widget_ = new QWidget();
    // extend the widget with all attributes and children from UI file
    ui_.setupUi(widget_);
    // add widget to the user interface
    context.addWidget(widget_);

    ui_.lineEdit->setText(QString::number(ui_.verticalSlider->value()));

    QObject::connect(ui_.verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_slider_value_change(int)));
    QObject::connect(ui_.pushButton, SIGNAL(clicked()), this, SLOT(on_slot_pub_topic()));

    m_chatter = getNodeHandle().advertise<std_msgs::String>("temp_chatter", 1000);
}

void MyPlugin::shutdownPlugin()
{
    // unregister all publishers here
    m_chatter.shutdown();
}

void MyPlugin::on_slot_pub_topic()
{
    std_msgs::String msg;
    std::stringstream ss;
    ss << "data: " << ui_.verticalSlider->value();
    msg.data = ss.str();
    m_chatter.publish(msg);
}

void MyPlugin::on_slider_value_change(int value)
{
    ui_.lineEdit->setText(QString::number(value));
}

}  // namespace rqt_mypkg_cpp

// #define PLUGINLIB_DECLARE_CLASS(pkg, class_name, class_type, base_class_type)
PLUGINLIB_DECLARE_CLASS(rqt_mypkg_cpp, MyPlugin, rqt_mypkg_cpp::MyPlugin, rqt_gui_cpp::Plugin)
