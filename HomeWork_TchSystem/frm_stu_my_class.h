#ifndef FRM_STU_MY_CLASS_H
#define FRM_STU_MY_CLASS_H

#include <QWidget>
#include <QTableWidget>
#include <QString>

#include "frm_course_detial_info.h"
#include "SqlOperation.h"

const int WeekOffset = 2;
const int ClassOffset = 0;

namespace Ui {
class frm_stu_my_class;
}

class Frm_StuMyClass : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_StuMyClass(int stuID, QString stuName, QWidget *parent = nullptr);

    ~Frm_StuMyClass();

private slots:
    void on_btn_Exit_clicked();

    void on_spb_Year_textChanged(const QString &arg1);

    void on_cbb_HalfTerm_currentIndexChanged(int index);

    void on_cbb_Term_currentIndexChanged(int index);

    void on_tbw_ScoreInfo_itemDoubleClicked(QTableWidgetItem *item);

    void on_btn_HeadPortriat_clicked();

private:
    void InitCourseTimeInfo();

    void DataBind_CourseTimeInfo(int year, int term, int halfTerm);

    void InsertTableItems(void);

    void beautify();
    
    Ui::frm_stu_my_class *ui;
    int stuID;
    QString stuName;

    int CourseID[11][7] = {0};
};

#endif // FRM_STU_MY_CLASS_H
