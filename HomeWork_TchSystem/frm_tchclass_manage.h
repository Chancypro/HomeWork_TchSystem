#ifndef FRM_TCHCLASS_MANAGE_H
#define FRM_TCHCLASS_MANAGE_H

#include <QWidget>
#include <QTreeWidget>

#include "SqlOperation.h"

namespace Ui {
class Frm_TchClassManage;
}

class Frm_TchClassManage : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_TchClassManage(int tchID, const QString& tchName, QWidget *parent = nullptr);
    ~Frm_TchClassManage();

private slots:
    void on_trW_CourseList_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btn_SaveScore_clicked();

    void on_btn_Exit_clicked();

    void on_btn_HeadPortrait_clicked();

private:
    void InitCourseList();

    void DataBind_CourseList();
    void DataBind_TchClassInfo(int courseID, CourseEnum::CourseStatus courseStatus);

    void beautify();

    Ui::Frm_TchClassManage *ui;

    int tchID;
    QString tchName;

    int trW_currentSelectedCourse;
    CourseEnum::CourseStatus trW_currentSelectedCourseStatus;
};

#endif // FRM_TCHCLASS_MANAGE_H
