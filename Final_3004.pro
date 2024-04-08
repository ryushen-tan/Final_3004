QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Device.cpp \
    EEGHeadset.cpp \
    EEGSignal.cpp \
    EEGSite.cpp \
    Session.cpp \
    SessionInfo.cpp \
    SignalGenerator.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Device.h \
    EEGHeadset.h \
    EEGSignal.h \
    EEGSite.h \
    Session.h \
    SessionInfo.h \
    SignalGenerator.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
