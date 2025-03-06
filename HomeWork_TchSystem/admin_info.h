#ifndef ADMIN_INFO_H
#define ADMIN_INFO_H

#include <QWidget>

namespace Ui {
class admin_info;
}

class admin_info : public QWidget
{
    Q_OBJECT

public:
    explicit admin_info(int netID, QWidget *parent = nullptr);
    void beautify(Ui::admin_info* ui);
    ~admin_info();

private slots:
    void on_btn_changepwd_clicked();

private:
    Ui::admin_info *ui;
    int netID;
};

#endif // ADMIN_INFO_H
