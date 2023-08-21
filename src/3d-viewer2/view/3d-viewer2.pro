QT       += core gui opengl openglwidgets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../libs/QtGifImage/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    glmodule.cc \
    ../main.cc \
    ../model/DataContainer.cc \
    ../model/ImgParser.cc \
    ../model/Model.cc \
    view.cc

HEADERS += \
    ../controller/controller.h \
    glmodule.h \
    ../model/DataContainer.h \
    ../model/ImgParser.h \
    ../model/Model.h \
    ../model/StringUtils.h \
    view.h

FORMS += \
    view.ui

ICON = image/preview.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
