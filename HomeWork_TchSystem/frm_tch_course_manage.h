#ifndef FRM_TCH_COURSE_MANAGE_H
#define FRM_TCH_COURSE_MANAGE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Frm_TchCourseManage;
}

class Frm_TchCourseManage : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_TchCourseManage(int tchID, const QString& tchName, QWidget *parent = nullptr);
    ~Frm_TchCourseManage();

private slots:
    void on_spb_Year_valueChanged(int arg1);

    void on_cbb_Term_currentIndexChanged(int index);

    void on_tbW_CourseInfo_itemDoubleClicked(QTableWidgetItem *item);

    void on_btn_AddCourse_clicked();

    void on_btn_RemoveCourse_clicked();

    void on_frm_cdi_data_changed();

    void on_btn_Search_clicked();

    void on_btn_Exit_clicked();

    void on_le_CourseName_textChanged(const QString &arg1);

    void on_le_CourseTchName_textChanged(const QString &arg1);

    void on_btn_HeadPortrait_clicked();

private:
    void InitCourseTableWidget();

    void DataBind_CourseInfo(int year, int term, const QString& courseName, const QString& courseTchName);

    void Refresh();

    void beautify();

    enum CourseInfoList: int{
        CourseID,
        CourseName,
        CourseTch,
        CourseType,
        CourseCredit,
        CoursePeriod,
        CourseAddress,
        CourseStatus,
        CourseInfoListCount
    };

    QString courseInfoListHeader[CourseInfoListCount];

    Ui::Frm_TchCourseManage *ui;

    int tchID;
    QString tchName;

    int trW_currentSelectedCourse;
};

#endif // FRM_TCH_COURSE_MANAGE_H
