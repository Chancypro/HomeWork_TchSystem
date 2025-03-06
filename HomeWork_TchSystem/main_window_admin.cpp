#include "main_window_admin.h"
#include "ui_main_window_admin.h"
#include "frm_stu_info_manage.h"
#include "frm_tch_info_manage.h"
#include "SqlOperation.h"
#include "admin_info.h"
#include "frm_login.h"
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>

AdminMainwindow::AdminMainwindow(int admID, const QString& admName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMainwindow),
    admID(admID), admName(admName)
{
    ui->setupUi(this);

    ui->lbl_AdmID->setText(QString::number(this->admID));
    ui->lbl_AdmName->setText(this->admName);

    initAdmMain();
}



void AdminMainwindow::initAdmMain(){
    QIcon a(":/new/main_window_stu/logo.jpg");
    this->setWindowIcon(a);
    this->setWindowTitle("管理员端主页");

    ui->newslabel1->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073791.htm\">高松校长率团访问香港理工大学</a>");
    ui->newslabel2->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073771.htm\">COP28大会专家热议气候适应与恢复力</a>");
    ui->newslabel3->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073671.htm\">中山大学分子工程交叉与前沿论坛暨活性中间体分析检测前沿研讨会顺利召开</a>");
    ui->newslabel4->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073701.htm\">中山大学11种科技期刊入选《科技期刊世界影响力指数（WJCI）报告（2023）》</a>");
    ui->newslabel5->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073521.htm\">我校举办“2023年中山大学辅导员年度人物”评选活动</a>");



//    :/new/main_window_stu/timepass.png
    QPixmap x1(":/new/main_window_stu/timepass.png");
    ui->btn_TimePlus->setIcon(QIcon(x1));
    ui->btn_TimePlus->setIconSize(x1.size());
    ui->btn_TimeMinus->setIcon(QIcon(x1));
    ui->btn_TimeMinus->setIconSize(x1.size());

//    QPixmap x2(":/new/main_window_stu/clear.png");
//    ui->btn_Clear->setIcon(QIcon(x2));
//    ui->btn_Clear->setIconSize(x2.size());

    QPixmap x3(":/new/main_window_stu/stuinfo.png");
    ui->btn_StuInfoMange->setIcon(QIcon(x3));
    ui->btn_StuInfoMange->setIconSize(x3.size());

    QPixmap x7(":/new/main_window_stu/tchinfo.png");
    ui->btn_TchInfoManage->setIcon(QIcon(x7));
    ui->btn_TchInfoManage->setIconSize(x7.size());




    ui->widget_4->setStyleSheet("background-color:#138dff;");
    //label
    QPixmap x4(":/new/main_window_stu/bkjw.jpg");
    ui->jwTitle_2->setPixmap(x4);
    ui->jwTitle_2->setScaledContents(true);
    QPixmap x5(":/new/main_window_stu/user48.png");
    ui->btn_HeadPortrait->setIcon(x5);
    ui->btn_HeadPortrait->setIconSize(x5.size());
    //ui->btn_HeadPortrait->setPixmap(x5);
    //ui->btn_HeadPortrait->setScaledContents(false);
    //按钮
    QPixmap x6(":/new/main_window_stu/exit48.png");
    ui->btn_Exit->setIcon(QIcon(x6));
    ui->btn_Exit->setIconSize(x6.size());
}

AdminMainwindow::~AdminMainwindow()
{
    delete ui;
}


void AdminMainwindow::on_newslabel1_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}



void AdminMainwindow::on_newslabel2_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void AdminMainwindow::on_newslabel3_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void AdminMainwindow::on_newslabel4_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void AdminMainwindow::on_newslabel5_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void AdminMainwindow::on_btn_Exit_clicked()
{
//    Frm_Login* login = new Frm_Login;
//    login->setAttribute(Qt::WA_DeleteOnClose);
//    login->show();
    this->close();
}


void AdminMainwindow::on_btn_StuInfoMange_clicked()
{
    Frm_StuInfoManage* FSIM = new Frm_StuInfoManage(this->admID, this->admName);
    FSIM->setAttribute(Qt::WA_DeleteOnClose);
    FSIM->show();
}


void AdminMainwindow::on_btn_TchInfoManage_clicked()
{
    Frm_TchInfoManage* FTIM = new Frm_TchInfoManage(this->admID, this->admName);
    FTIM->setAttribute(Qt::WA_DeleteOnClose);
    FTIM->show();
}


void AdminMainwindow::on_btn_TimePlus_clicked()
{
    QT_TRY{
        SqlOperation::ProgressUp();

        QSqlQuery query = SqlOperation::ProgressQuery();
        query.next();
        int progress = query.value("progress").toInt();
        int year = query.value("year").toInt();
        int term = query.value("term").toInt();

        QString msg = QString("当前时间：%1年 第%2学期, %3").arg(year).arg(term).arg(ProgressInfoStr[progress]);
        QMessageBox::information(this, "提示", msg);
    }QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }
}

void AdminMainwindow::on_btn_TimeMinus_clicked()
{
    QT_TRY{
        SqlOperation::ProgressDown();

        QSqlQuery query = SqlOperation::ProgressQuery();
        query.next();
        int progress = query.value("progress").toInt();
        int year = query.value("year").toInt();
        int term = query.value("term").toInt();

        QString msg = QString("当前时间：%1年 第%2学期, %3").arg(year).arg(term).arg(ProgressInfoStr[progress]);
        QMessageBox::information(this, "提示", msg);

    }QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }
}

void AdminMainwindow::on_btn_HeadPortrait_clicked()
{
    admin_info* ai = new admin_info(this->admID);
    ai->setAttribute(Qt::WA_DeleteOnClose);
    ai->show();
}







