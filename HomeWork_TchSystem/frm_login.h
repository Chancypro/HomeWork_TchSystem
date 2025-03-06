#ifndef FRM_LOGIN_H
#define FRM_LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include "SqlOperation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class frm_login; }
QT_END_NAMESPACE

class Frm_Login : public QWidget
{
    Q_OBJECT

public:
    Frm_Login(QWidget *parent = nullptr);
    ~Frm_Login();
private slots:
    void on_btn_Login_clicked();

    void beautify();

private:
    Ui::frm_login *ui;
};
#endif // FRM_LOGIN_H
