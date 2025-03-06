#include "frm_changepwd.h"
#include "qgraphicseffect.h"
#include "ui_frm_changepwd.h"
#include "SqlOperation.h"
#include <QMessageBox>

using namespace UserEnum;

frm_changepwd::frm_changepwd(int netID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm_changepwd),
    netID(netID)
{
    ui->setupUi(this);
    beautify(ui);

    ui->txt_NetID->setText(QString::number(this->netID));
}
void frm_changepwd::beautify(Ui::frm_changepwd* ui)
{
    this->setWindowTitle("修改密码");
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
    //登录框
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 0);
    ui->widget_1->setGraphicsEffect(shadow);
}
frm_changepwd::~frm_changepwd()
{
    delete ui;
}

void frm_changepwd::on_btn_changepwd_2_clicked()
{
    this->close();
}


void frm_changepwd::on_btn_changepwd_clicked()
{
    QString curPwd = ui->le_CurPwd->text();
    QString newPwd = ui->le_NewPwd->text();

    if(newPwd == ""){
        QMessageBox::information(this, "提示", "新密码不能为空！");
        return;
    }
    QT_TRY{
        QSqlQuery query = SqlOperation::SearchTypUserInfo(this->netID);
        if(query.next()){
            if(curPwd != query.value("pwd").toString()){
                QMessageBox::information(this, "提示", "原密码错误！");
                return;
            }
            int res = SqlOperation::UpdateUserInfo(netID, newPwd, UserType(query.value("user_type").toInt()), Status(query.value("status").toInt()));
            if(res > 0){
                QMessageBox::information(this, "提示", "修改成功！");
                ui->le_CurPwd->setText("");
                ui->le_NewPwd->setText("");
            }else{
                QMessageBox::information(this, "提示", "修改失败！");
            }
        }
    }QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }

}

