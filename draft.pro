system(./makeversion.sh) QMAKE_EXTRA_TARGETS += version.h
PRE_TARGETDEPS += version.h
QT += quick
QT -= GLES
CONFIG += c++11
CONFIG += optimize_full

linux-oe-g++ {
    message("rm")
    LIBS += -lqsgepaper
    DEFINES += RM
}

TARGET = draft
DESTDIR = bin
OBJECTS_DIR = obj
DEPLOYMENT_PATH=/home/root
INSTALLS += target
target.path = /home/root
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    option_item.h \
    options.h \
    version.h

SOURCES += main.cpp \
    option_item.cpp \
    options.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


RESOURCES += \
    qml.qrc

