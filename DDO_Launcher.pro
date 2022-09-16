QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DDO_Launcher
TEMPLATE = app

CONFIG += c++11
CONFIG+= static

#LIBS += -lopengl32
#INCLUDEPATH += S:/Qt/Tools/OpenSSL/Win_x86/include
#LIBS += -LS:/Qt/Tools/OpenSSL/Win_x86/bin -llibcrypto-1_1 -llibssl-1_1
#windows icon
RC_FILE = icon.rc
#mac icon
#ICON = icon.icns


SOURCES += main.cpp\
    ddolauncher.cpp

HEADERS  += \
    ddolauncher.h

qtHaveModule(opengl): QT += opengl

RESOURCES += ddons.qrc

FORMS +=

DISTFILES +=
