#-------------------------------------------------
#
# Project created by QtCreator 2022-08-19T16:42:17
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewCAN
TEMPLATE = app

#QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
#QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
#QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


#在QT5中解决中文乱码问题
#1.菜单->工具->选项->文本编辑器->行为->文件编码 设置为UTF8则添加
#2.在pro文件中加 QMAKE_CXXFLAGS += /utf-8
#不必再在cpp中指定 #pragma execution_character_set("utf-8")
#QMAKE_CXXFLAGS += /utf-8

SOURCES += \
    SLT/canframemodel.cpp \
    addcommanddialog.cpp \
    commandfilterform.cpp \
    commontool.cpp \
    datachosseform.cpp \
        main.cpp \
        mainwindow.cpp \
    canthread.cpp \
    onecommandform.cpp \
    qtlog/logger.cpp \
    qtlog/logwriter.cpp \
    qtlog/qtlog.cpp \
    sendthread.cpp


HEADERS += \
    SLT/canframemodel.h \
    SLT/macro.h \
    addcommanddialog.h \
    circular_buffer.h \
    commandfilterform.h \
    commontool.h \
    datachosseform.h \
    dequeadapter.h \
        mainwindow.h \
    canthread.h \
    onecommandform.h \
    qtlog/logger.h \
    qtlog/logwriter.h \
    qtlog/qtlog.h \
ControlCAN.h \
SLT/plf_queue.h \
    sendthread.h

FORMS += \
        addcommanddialog.ui \
        commandfilterform.ui \
        datachosseform.ui \
        mainwindow.ui \
        onecommandform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

LIBS += -L$$PWD/lib

LIBS += -lControlCAN

#LIBS += -lControlCAN -llibxl32


#生成路径
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../bin
}
CONFIG(release, debug|release){
#    DESTDIR = $$PWD/../bin
}
