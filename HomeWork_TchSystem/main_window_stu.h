#ifndef MAIN_WINDOW_STU_H
#define MAIN_WINDOW_STU_H

#include <QWidget>

namespace Ui {
class StudentMainWindow;
}

class StudentMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentMainWindow(int stuID, const QString& stuName, QWidget *parent = nullptr);
    ~StudentMainWindow();

private slots:

    void on_newslabel1_linkActivated(const QString &link);

    void on_newslabel2_linkActivated(const QString &link);

    void on_newslabel3_linkActivated(const QString &link);

    void on_newslabel4_linkActivated(const QString &link);

    void on_newslabel5_linkActivated(const QString &link);

    void on_btn_Exit_clicked();

    void on_btn_PickClass_clicked();

    void on_btn_MyClass_clicked();

    void on_btn_MyScore_clicked();

    void on_btn_HeadPortrait_clicked();

private:
    void initStuMain();

    Ui::StudentMainWindow *ui;
    int stuID;
    QString stuName;


};

#endif // MAIN_WINDOW_STU_H
