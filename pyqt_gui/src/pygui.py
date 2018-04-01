#!/usr/bin/env python

import os, sys
import rospy
from std_msgs.msg import String
from python_qt_binding import loadUi
from PyQt4 import QtGui

class pyGui(QtGui.QWidget):
    def __init__(self):
        super(pyGui, self).__init__()
        self_dir = os.path.dirname(os.path.realpath(__file__))
        print self_dir
        self.ui_dir = os.path.join(self_dir, '../ui')
        ui_file = os.path.join(self.ui_dir, 'pygui.ui')
        loadUi(ui_file, self)
        self.pub = rospy.Publisher("pygui_topic", String, queue_size=10)
        rospy.init_node('py_gui')
        self.is_pub = False
        self.current_value = self.horizontalSlider.value()
        print self.current_value
        self.label.setText("num: " + str(self.current_value))
        self.pushButton.pressed.connect(self.publish_topic)
        self.pushButton_2.pressed.connect(self.gui_close)
        self.horizontalSlider.valueChanged.connect(self.change_value)

    def publish_topic(self):
        self.pub.publish(str(self.current_value))
        self.pushButton.setEnabled(False)
        self.is_pub = True

    def change_value(self, value):
        self.current_value = value
        if True == self.is_pub:
            self.label.setText("num: " + str(value))
            self.pub.publish(str(self.current_value))

    def gui_close(self):
        self.close()


def main():
    app=QtGui.QApplication(sys.argv)
    pyShow = pyGui()
    pyShow.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()