#ifndef FRM_STU_INFO_MANAGE_H
#define FRM_STU_INFO_MANAGE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Frm_StuInfoManage;
}

class Frm_StuInfoManage : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_StuInfoManage(int admID, const QString& admName, QWidget *parent = nullptr);
    void beautify();
    ~Frm_StuInfoManage();
signals:
    void SaveStateChanged();

private slots:
    void on_btn_Exit_clicked();

    void on_btn_Clear_clicked();

    void on_btn_Delete_clicked();

    void on_btn_SaveInfo_clicked();

    void on_SaveStateChanged();

    void on_tbW_StuInfo_itemClicked(QTableWidgetItem *item);

    void on_btn_HeadPortrait_clicked();

private:
    void InitWindow();
    void InitStuTableWidget();

    void DataBind_StuInfo();

    void ClearInfo();

    //NetID, Name, Gender, Age, Department, Major, Grade
    enum StuInfoList: int{
        StuNetID,
        StuName,
        StuGender,
        StuAge,
        StuDepartment,
        StuMajor,
        StuGrade,
        StuListCount
    };

    enum SaveState: int{
        Add,
        Save
    };

    Ui::Frm_StuInfoManage *ui;

    SaveState saveState;

    int admID;
    QString admName;
};

#endif // FRM_STU_INFO_MANAGE_H
