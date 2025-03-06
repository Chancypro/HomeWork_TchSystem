#ifndef MAIN_WINDOW_ADMIN_H
#define MAIN_WINDOW_ADMIN_H

#include <QWidget>

namespace Ui {
class AdminMainwindow;
}

class AdminMainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainwindow(int admID, const QString& admName, QWidget *parent = nullptr);
    ~AdminMainwindow();

private slots:
    void on_newslabel1_linkActivated(const QString &link);

    void on_newslabel2_linkActivated(const QString &link);

    void on_newslabel3_linkActivated(const QString &link);

    void on_newslabel4_linkActivated(const QString &link);

    void on_newslabel5_linkActivated(const QString &link);

    void on_btn_Exit_clicked();

    void on_btn_StuInfoMange_clicked();

    void on_btn_TchInfoManage_clicked();

    void on_btn_TimePlus_clicked();

    void on_btn_TimeMinus_clicked();

    void on_btn_HeadPortrait_clicked();

private:
    void initAdmMain();

    Ui::AdminMainwindow *ui;
    int admID;
    QString admName;
};

#endif // MAIN_WINDOW_ADMIN_H
