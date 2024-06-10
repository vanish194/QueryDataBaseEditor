QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adding.cpp \
    additionalmnemonicaddwindow.cpp \
    customquerymodel.cpp \
    customtableview.cpp \
    databaseaction.cpp \
    main.cpp \
    mainmnemonicaddwindow.cpp \
    mainwindow.cpp \
    sensoraddwindow.cpp \
    tooladdwindow.cpp

HEADERS += \
    adding.h \
    additionalmnemonicaddwindow.h \
    blobimagedelegate.h \
    customquerymodel.h \
    customtableview.h \
    databaseaction.h \
    mainmnemonicaddwindow.h \
    mainwindow.h \
    sensoraddwindow.h \
    tooladdwindow.h

FORMS += \
    adding.ui \
    additionalmnemonicaddwindow.ui \
    mainmnemonicaddwindow.ui \
    mainwindow.ui \
    sensoraddwindow.ui \
    tooladdwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
