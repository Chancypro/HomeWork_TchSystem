#ifndef TCH_INFO_H
#define TCH_INFO_H

#include <QWidget>

namespace Ui {
class tch_info;
}

class tch_info : public QWidget
{
    Q_OBJECT

public:
    explicit tch_info(int netID, QWidget *parent = nullptr);
    void beautify(Ui::tch_info* ui);
    ~tch_info();

private slots:
    void on_btn_changepwd_clicked();

private:
    Ui::tch_info *ui;
    int netID;
};

#endif // TCH_INFO_H
