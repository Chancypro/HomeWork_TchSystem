QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

RC_ICONS = logo.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SqlOperation.cpp \
    admin_info.cpp \
    co_Sqloperation.cpp \
    frm_changepwd.cpp \
    frm_course_detial_info.cpp \
    frm_login.cpp \
    frm_stu_info_manage.cpp \
    frm_stu_my_class.cpp \
    frm_stu_my_score.cpp \
    frm_stu_pick_class.cpp \
    frm_tch_course_manage.cpp \
    frm_tch_info_manage.cpp \
    frm_tchclass_manage.cpp \
    main.cpp \
    main_window_admin.cpp \
    main_window_stu.cpp \
    main_window_tch.cpp \
    stu_info.cpp \
    tch_info.cpp

HEADERS += \
    SqlOperation.h \
    TotalNameDesign.h \
    admin_info.h \
    frm_changepwd.h \
    frm_course_detial_info.h \
    frm_login.h \
    frm_stu_info_manage.h \
    frm_stu_my_class.h \
    frm_stu_my_score.h \
    frm_stu_pick_class.h \
    frm_tch_course_manage.h \
    frm_tch_info_manage.h \
    frm_tchclass_manage.h \
    main_window_admin.h \
    main_window_stu.h \
    main_window_tch.h \
    stu_info.h \
    tch_info.h

FORMS += \
    admin_info.ui \
    frm_changepwd.ui \
    frm_course_detial_info.ui \
    frm_login.ui \
    frm_stu_info_manage.ui \
    frm_stu_my_class.ui \
    frm_stu_my_score.ui \
    frm_stu_pick_class.ui \
    frm_tch_course_manage.ui \
    frm_tch_info_manage.ui \
    frm_tchclass_manage.ui \
    main_window_admin.ui \
    main_window_stu.ui \
    main_window_tch.ui \
    stu_info.ui \
    tch_info.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc \
    pics.qrc
