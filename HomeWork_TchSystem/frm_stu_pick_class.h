#ifndef FRM_STU_PICK_CLASS_H
#define FRM_STU_PICK_CLASS_H

#include <QWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QListWidget>
#include <map>
#include"frm_course_detial_info.h"
#include"SqlOperation.h"

using std::unordered_map;

namespace Ui {
class frm_stu_pick_class;
}

class Frm_StuPickClass : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_StuPickClass(int stuID, QString stuName, QWidget *parent = nullptr);
    ~Frm_StuPickClass();

private slots:
    void on_trw_YearTerm_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btn_Exit_clicked();

    void on_tbw_CourseInfo_itemDoubleClicked(QTableWidgetItem *item);

    void on_lw_SelectedCourseInfo_itemDoubleClicked(QListWidgetItem *item);

    void on_btn_Cancel_clicked();

    void on_btn_Select_clicked();

    void on_le_CourseName_textChanged(const QString &arg1);

    void on_btn_HeadPortrait_clicked();

private:
    //header<<"课程名称"<<"任课教师"<<"上课地点时间"<<"学分"<<"考核方式"<<"开设学院"<<"选课人数/剩余空位"<<"选课状态";
    enum CourseInfoList: int{
        CourseID,
        CourseName,
        TchName,
        CourseCredit,
        CourseType,
        CourseAddress,
        CourseAssessmentMethod,
        StuNum,
        SelectionState,
        CourseInfoListCount
    };
    const QString CourseInfoListStr[CourseInfoListCount] = {
        "课程编号",
        "课程名称",
        "授课教师",
        "学分",
        "类型",
        "授课地点",
        "考核方式",
        "选课人数/剩余空位",
        "状态"
    };

    void InitCourseInfo();
    void InitSelectedCourseInfo();
    void InitYearTerm();

    void DataBind_CourseInfo(int year, int term, const QString& courseName);
    void DataBind_SelectedCourseInfo(int year, int term);

    void beautify();

    Ui::frm_stu_pick_class *ui;

    int stuID;
    QString stuName;

    int curSelectedYear;
    int curSelectedTerm;

    //已选课程中的下标所对应的课程编号
    QList<int> tbwIdxToSelectedCourseID;
};

#endif // FRM_STU_PICK_CLASS_H
