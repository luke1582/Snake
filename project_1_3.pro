QT       += core gui
QT+=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    endgame.cpp \
    endgame1.cpp \
    game_1.cpp \
    game_2.cpp \
    game_3.cpp \
    game_begin.cpp \
    game_select.cpp \
    gamewidget.cpp \
    gamewidget_2.cpp \
    gamewidget_3.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    rank.cpp \
    setting.cpp \
    two_sankes.cpp

HEADERS += \
    database.h \
    endgame.h \
    endgame1.h \
    game_1.h \
    game_2.h \
    game_3.h \
    game_begin.h \
    game_select.h \
    gamewidget.h \
    gamewidget_2.h \
    gamewidget_3.h \
    login.h \
    mainwindow.h \
    rank.h \
    setting.h \
    two_sankes.h

FORMS += \
    game_1.ui \
    game_2.ui \
    game_3.ui \
    game_begin.ui \
    game_select.ui \
    gamewidget.ui \
    gamewidget2.ui \
    gamewidget_2.ui \
    gamewidget_3.ui \
    login.ui \
    mainwindow.ui \
    rank.ui \
    setting.ui \
    two_sankes.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
CONFIG+=c++11

QT += multimedia

RESOURCES += \
    image.qrc
