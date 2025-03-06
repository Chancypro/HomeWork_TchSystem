#include "tch_info.h"
#include "qgraphicseffect.h"
#include "ui_tch_info.h"
#include "frm_changepwd.h"
#include "SqlOperation.h"

tch_info::tch_info(int netID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tch_info),
    netID(netID)
{
    ui->setupUi(this);
    beautify(ui);

    QSqlQuery query = SqlOperation::SearchTypTchInfo(this->netID);
    query.next();

    ui->lbl_netid->setText(query.value("tchID").toString());
    ui->lbl_age->setText(query.value("age").toString());
    ui->lbl_gender->setText(UserEnum::GenderTypeStr[query.value("gender").toInt()]);
    ui->lbl_name->setText(query.value("name").toString());
    ui->lbl_academy->setText(query.value("department").toString());
    ui->lbl_posts->setText(UserEnum::TchPositionStr[query.value("position").toInt()-1]);
}
void tch_info::beautify(Ui::tch_info* ui)
{
    this->setWindowTitle("教师个人信息");
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
    //登录框
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 0);
    ui->widget_1->setGraphicsEffect(shadow);

}
tch_info::~tch_info()
{
    delete ui;
}

void tch_info::on_btn_changepwd_clicked()
{
    frm_changepwd* cp = new frm_changepwd(this->netID);
    cp->setAttribute(Qt::WA_DeleteOnClose);
    cp->show();
}

