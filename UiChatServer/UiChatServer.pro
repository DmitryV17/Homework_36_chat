QT       += core gui
QT       += sql
QTPLUGIN += QSQLMYSQL
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Admin.cpp \
    banlist.cpp \
    database.cpp \
    dellist.cpp \
    main.cpp \
    Admin.cpp \
    mainwindow.cpp \
    meslist.cpp \
    uslist.cpp

HEADERS += \
    Admin.h \
    banlist.h \
    database.h \
    dellist.h \
    mainwindow.h \
    Admin.h \
    meslist.h \
    mysql.h \
    uslist.h

FORMS += \
    banlist.ui \
    dellist.ui \
    mainwindow.ui \
    meslist.ui \
    uslist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32: LIBS += -L'C:/Program Files/MySQL/MySQL Server 8.0/lib/' -llibmysql

INCLUDEPATH += 'C:/Program Files/MySQL/MySQL Server 8.0/include'
DEPENDPATH += 'C:/Program Files/MySQL/MySQL Server 8.0/include'
