#include "stu_info.h"
#include "qgraphicseffect.h"
#include "ui_stu_info.h"
#include "frm_changepwd.h"
#include "SqlOperation.h"

stu_info::stu_info(int netID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_info),
    netID(netID)
{
    ui->setupUi(this);
    beautify(ui);

    QSqlQuery query = SqlOperation::SearchTypStuInfo(this->netID);
    query.next();

    ui->lbl_netid->setText(query.value("stuID").toString());
    ui->lbl_age->setText(query.value("age").toString());
    ui->lbl_gender->setText(UserEnum::GenderTypeStr[query.value("gender").toInt()]);
    ui->lbl_name->setText(query.value("name").toString());
    ui->lbl_grade->setText(query.value("grade").toString());
    ui->lbl_major->setText(query.value("major").toString());
    ui->lbl_academy->setText(query.value("department").toString());
}
void stu_info::beautify(Ui::stu_info* ui)
{
    this->setWindowTitle("学生个人信息");
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
    //登录框
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 0);
    ui->widget_1->setGraphicsEffect(shadow);

}
stu_info::~stu_info()
{
    delete ui;
}

void stu_info::on_btn_changepwd_clicked()
{
    frm_changepwd* cp = new frm_changepwd(this->netID);
    cp->setAttribute(Qt::WA_DeleteOnClose);
    cp->show();
}

