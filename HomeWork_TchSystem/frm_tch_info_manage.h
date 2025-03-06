#ifndef FRM_TCH_INFO_MANAGE_H
#define FRM_TCH_INFO_MANAGE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Frm_TchInfoManage;
}

class Frm_TchInfoManage : public QWidget
{
    Q_OBJECT

public:
    explicit Frm_TchInfoManage(int admID, const QString& admName, QWidget *parent = nullptr);
    void beautify();
    ~Frm_TchInfoManage();

signals:
    void SaveStateChanged();

private slots:
    void on_SaveStateChanged();

    void on_btn_Exit_clicked();

    void on_btn_Clear_clicked();

    void on_btn_Delete_clicked();

    void on_btn_SaveInfo_clicked();

    void on_tbW_TchInfo_itemClicked(QTableWidgetItem *item);

    void on_btn_HeadPortrait_clicked();

private:
    void InitWindow();

    void InitTchTableWidget();

    void DataBind_TchInfo();

    void ClearInfo();

    enum TchInfoList: int{
        TchNetID,
        TchName,
        TchGender,
        TchAge,
        TchDepartment,
        TchPosition,
        TchListCount
    };

    enum SaveState: int{
        Add,
        Save
    };

    Ui::Frm_TchInfoManage *ui;
    int admID;
    QString admName;

    SaveState saveState;
};

#endif // FRM_TCH_INFO_MANAGE_H
