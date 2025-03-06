#ifndef FRM_CHANGEPWD_H
#define FRM_CHANGEPWD_H

#include <QWidget>

namespace Ui {
class frm_changepwd;
}

class frm_changepwd : public QWidget
{
    Q_OBJECT

public:
    explicit frm_changepwd(int netID, QWidget *parent = nullptr);
    void beautify(Ui::frm_changepwd* ui);
    ~frm_changepwd();

private slots:
    void on_btn_changepwd_2_clicked();

    void on_btn_changepwd_clicked();

private:
    Ui::frm_changepwd *ui;
    int netID;
};

#endif // FRM_CHANGEPWD_H
