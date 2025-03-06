#include "admin_info.h"
#include "qgraphicseffect.h"
#include "ui_admin_info.h"
#include "frm_changepwd.h"
#include "SqlOperation.h"

admin_info::admin_info(int netID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_info),
    netID(netID)
{
    ui->setupUi(this);
    beautify(ui);

    QSqlQuery query = SqlOperation::SearchTypAdmInfo(this->netID);
    query.next();

    ui->lbl_netid->setText(query.value("admID").toString());
    ui->lbl_age->setText(query.value("age").toString());
    ui->lbl_gender->setText(UserEnum::GenderTypeStr[query.value("gender").toInt()]);
    ui->lbl_name->setText(query.value("name").toString());
}
void admin_info::beautify(Ui::admin_info* ui)
{
    this->setWindowTitle("管理员个人信息");
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
    //登录框
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 0);
    ui->widget_1->setGraphicsEffect(shadow);

}
admin_info::~admin_info()
{
    delete ui;
}

void admin_info::on_btn_changepwd_clicked()
{
    frm_changepwd* cp = new frm_changepwd(this->netID);
    cp->setAttribute(Qt::WA_DeleteOnClose);
    cp->show();
}

