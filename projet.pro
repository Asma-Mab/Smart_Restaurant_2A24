QT       += core gui

QT       += sql
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = projet
TEMPLATE = app

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clients.cpp \
    commande.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    clients.h \
    commande.h \
    connection.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
