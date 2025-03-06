#ifndef FRM_COURSE_DETIAL_INFO_H
#define FRM_COURSE_DETIAL_INFO_H

#include <QWidget>
#include<QCheckBox>
#include<QMessageBox>
#include"SqlOperation.h"

using namespace CourseEnum;

const double BaseHalfTermPeriod[2] = { 9 * 0.75, 10*0.75 };

namespace Ui {
class frm_course_detial_info;
}

class Frm_CourseDetialInfo : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_CourseDetialInfo(int courseID, int netID, QString name, IDType type, int year = 0, int term = 0, QWidget *parent = nullptr);
    ~Frm_CourseDetialInfo();

signals:
    void DataChanged();
private slots:
    void on_cbb_HalfTerm_currentIndexChanged(int index);

    void on_btn_Save_clicked();

    void on_btn_Exit_clicked();

    void on_btn_HeadPortrait_clicked();

private:
    void DataBind();
    void InitCheckBox_TimeSelect();
    void beautify();

    Ui::frm_course_detial_info *ui;

    int courseID;
    int netID;
    IDType idType;
    int tchID;
    QString name;
    CourseStatus courseStatus;

    QCheckBox* cb_TimeSelect[6][6];
    bool cbTimeSelectValue[6][6][2]{{{0}}};
    int course_period[2];
};

#endif // FRM_COURSE_DETIAL_INFO_H
