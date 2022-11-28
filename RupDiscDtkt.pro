QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    functionkno.cpp \
    loadwidget.cpp \
    loadwidgetv.cpp \
    main.cpp \
    rupdiscdtct.cpp \
    showwidget.cpp

HEADERS += \
    functionkno.h \
    loadwidget.h \
    loadwidgetv.h \
    rupdiscdtct.h \
    showwidget.h

FORMS += \
    loadwidget.ui \
    loadwidgetv.ui \
    rupdiscdtct.ui \
    showwidget.ui

QMAKE_LFLAGS += -no-pie

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH += /home/emjay/opencv/OpenCV454_gcc_x64/include \
               /home/emjay/opencv/OpenCV454_gcc_x64/include/opencv4 \
               /home/emjay/opencv/OpenCV454_gcc_x64/include/opencv4/opencv2

LIBS += /home/emjay/opencv/OpenCV454_gcc_x64/lib/libopencv_world.so
