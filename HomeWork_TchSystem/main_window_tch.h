#ifndef MAIN_WINDOW_TCH_H
#define MAIN_WINDOW_TCH_H

#include <QWidget>

namespace Ui {
class TeacherMainWindow;
}

class TeacherMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherMainWindow(int tchID, const QString& tchName, QWidget *parent = nullptr);
    ~TeacherMainWindow();

private slots:
    void on_newslabel1_linkActivated(const QString &link);

    void on_newslabel2_linkActivated(const QString &link);

    void on_newslabel3_linkActivated(const QString &link);

    void on_newslabel4_linkActivated(const QString &link);

    void on_newslabel5_linkActivated(const QString &link);

    void on_btn_Exit_clicked();

    void on_btn_CourseManage_clicked();

    void on_btn_TchClassManage_clicked();

    void on_btn_HeadPortrait_clicked();

private:
    void initTeaMain();

    Ui::TeacherMainWindow *ui;
    int tchID;
    QString tchName;
};

#endif // MAIN_WINDOW_TCH_H
