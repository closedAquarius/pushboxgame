QT       += core gui multimedia

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
    allfinished.cpp \
    boxgame.cpp \
    custom.cpp \
    gamelevel.cpp \
    help.cpp \
    level1.cpp \
    level1finished.cpp \
    main.cpp \
    music.cpp \
    notice.cpp \
    start.cpp

HEADERS += \
    allfinished.h \
    boxgame.h \
    custom.h \
    gamelevel.h \
    help.h \
    level1.h \
    level1finished.h \
    music.h \
    notice.h \
    start.h

FORMS += \
    allfinished.ui \
    custom.ui \
    gamelevel.ui \
    help.ui \
    level1.ui \
    level1finished.ui \
    music.ui \
    notice.ui \
    start.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
