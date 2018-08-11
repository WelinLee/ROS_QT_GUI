#ifndef VIZLIB_TEST_H
#define VIZLIB_TEST_H

#include <QWidget>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool_manager.h>
#include "vizlib_test/ui_vizlib_test.h"

namespace Ui {
class VizlibTest;
}

class VizlibTest : public QWidget
{
    Q_OBJECT

public:
    explicit VizlibTest(int argc, char **argv, QWidget *parent = 0);
    ~VizlibTest();

    void init_ros(int argc, char **argv);

private slots:
    void slot_btn_display();
    void slot_btn_quit();

private:
    rviz::VisualizationManager *manager_;
    rviz::RenderPanel * render_panel_;
    Ui::VizlibTest *ui;
};

#endif // VIZLIB_TEST_H
