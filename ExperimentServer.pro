QT -= gui

CONFIG += c++11 release
CONFIG += console
CONFIG -= app_bundle

LIBS += -lpthread libwsock32 libws2_32
LIBS += $$PWD/_libs/visa64.lib
INCLUDEPATH += $$PWD/_include


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += NOCONSOLE=0
DEFINES += SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
    src/server/servermanager.cpp \
    src/controller/democontroller.cpp \
    src/controller/admincontroller.cpp \
    src/utils/util.cpp \
    src/utils/jsoncpp.cpp \
    src/device/b2900.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/server/servermanager.hpp \
    src/controller/democontroller.hpp \
    src/controller/controller.hpp \
    src/controller/admincontroller.hpp \
    src/utils/util.hpp \
    src/device/device.hpp \
    src/device/b2900.hpp
