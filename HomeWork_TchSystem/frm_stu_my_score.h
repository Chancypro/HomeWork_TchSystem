#ifndef FRM_STU_MY_SCORE_H
#define FRM_STU_MY_SCORE_H

#include <QWidget>
#include <QString>
#include <QTableWidget>
#include <QTreeWidget>
#include "SqlOperation.h"

namespace Ui {
class frm_stu_my_score;
}

class Frm_StuMyScore : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_StuMyScore(int stuID, QString stuName, QWidget *parent = nullptr);
    void InsertTableItems();
    ~Frm_StuMyScore();

private slots:
    void on_btn_Exit_clicked();

    void on_trw_YearTerm_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_btn_HeadPortrait_clicked();

private:
    void InitScoreTableInfo();
    void InitYearTermInfo();

    void DataBind_ScoreInfo(int year, int term);

    void InitCreditGPA();

    void beautify();

    enum ScoreInfoList: int{
        SerialNum,
        CourseType,
        CourseName,
        TchName,
        Credit,
        Score,
        GPA,
        Rank,
        IsPass,
        ScoreInfoListCount
    };
    const QString ScoreInfoListStr[ScoreInfoListCount] = {
        "序号",
        "课程类别",
        "课程名称",
        "授课教师",
        "学分",
        "成绩",
        "绩点",
        "教学班排名",
        "是否通过"
    };

    Ui::frm_stu_my_score *ui;
    int stuID;
    QString stuName;
};

#endif // FRM_STU_MY_SCORE_H
