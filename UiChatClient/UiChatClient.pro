QT       += core gui
QT       += sql
QTPLUGIN += QSQLMYSQL
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chat.cpp \
    Chat.cpp \
    database.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    registrationform.cpp \
    seemes.cpp \
    seeus.cpp \
    startscreen.cpp \
    writemes.cpp

HEADERS += \
    Chat.h \
    Chat.h \
    Message.h \
    Message.h \
    User.h \
    User.h \
    database.h \
    loginform.h \
    mainwindow.h \
    mysql.h \
    registrationform.h \
    seemes.h \
    seeus.h \
    startscreen.h \
    writemes.h


FORMS += \
    loginform.ui \
    mainwindow.ui \
    registrationform.ui \
    seemes.ui \
    seeus.ui \
    startscreen.ui \
    writemes.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32: LIBS += -L'C:/Program Files/MySQL/MySQL Server 8.0/lib/' -llibmysql

INCLUDEPATH += 'C:/Program Files/MySQL/MySQL Server 8.0/include'
DEPENDPATH += 'C:/Program Files/MySQL/MySQL Server 8.0/include'
