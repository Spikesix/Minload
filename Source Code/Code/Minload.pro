QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minload

SOURCES += main.cpp mainwindow.cpp \
    convertwindow.cpp
HEADERS += mainwindow.h \
    convertwindow.h



RESOURCES += \
    resources.qrc


RC_ICONS = icon.ico


