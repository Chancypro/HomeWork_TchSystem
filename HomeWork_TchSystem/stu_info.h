#ifndef STU_INFO_H
#define STU_INFO_H

#include <QWidget>

namespace Ui {
class stu_info;
}

class stu_info : public QWidget
{
    Q_OBJECT

public:
    explicit stu_info(int netID, QWidget *parent = nullptr);
    void beautify(Ui::stu_info* ui);
    ~stu_info();

private slots:
    void on_btn_changepwd_clicked();

private:
    Ui::stu_info *ui;

    int netID;
};

#endif // STU_INFO_H
