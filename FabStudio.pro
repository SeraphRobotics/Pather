# -------------------------------------------------
# Project created by QtCreator 2010-02-16T16:57:33
# -------------------------------------------------
DEFINES += CONFIRM_ENABLED
QT += xml
QT -= gui # for console


TARGET = Pather
#TEMPLATE = app  # for UI
CONFIG   += console   #for console
CONFIG   -= app_bundle # for console
SOURCES += main.cpp
#LIBS += CoreFoundation
LIBS += -framework CoreFoundation  # for OSX

#HEADERS +=
#FORMS += mainwindow.ui\

#INCLUDEPATH += ../../../
#RESOURCES += resources.qrc
include("common.pro")
#include("shared-amf.pro")
include("shared.pro")
include("shared-math.pro")
#include("shared-pather.pro")
include("shared-slice.pro")
#include("shared-stl.pro")
#include("shared-toolscript.pro")
include("shared-utils.pro")
#OTHER_FILES += fabstudio.rc
#RC_FILE = fabstudio.rc
