QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    main_window_admin.cpp \
    main_window_stu.cpp \
    main_window_tch.cpp \
    widget.cpp

HEADERS += \
    main_window_admin.h \
    main_window_stu.h \
    main_window_tch.h \
    widget.h

FORMS += \
    main_window_admin.ui \
    main_window_stu.ui \
    main_window_tch.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
