#include "main_window_stu.h"
#include "ui_main_window_stu.h"
#include "frm_stu_pick_class.h"
#include "frm_stu_my_class.h"
#include "frm_stu_my_score.h"
#include "stu_info.h"
#include "frm_login.h"
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>

StudentMainWindow::StudentMainWindow(int stuID, const QString& stuName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentMainWindow),
    stuID(stuID), stuName(stuName)
{
    ui->setupUi(this);

    ui->lbl_StuID->setText(QString::number(this->stuID));
    ui->lbl_StuName->setText(this->stuName);

    initStuMain();

}


void StudentMainWindow::initStuMain(){
    QIcon a(":/new/main_window_stu/logo.jpg");
    this->setWindowIcon(a);
    this->setWindowTitle("学生端主页");

    ui->newslabel1->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073791.htm\">高松校长率团访问香港理工大学</a>");
    ui->newslabel2->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073771.htm\">COP28大会专家热议气候适应与恢复力</a>");
    ui->newslabel3->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073671.htm\">中山大学分子工程交叉与前沿论坛暨活性中间体分析检测前沿研讨会顺利召开</a>");
    ui->newslabel4->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073701.htm\">中山大学11种科技期刊入选《科技期刊世界影响力指数（WJCI）报告（2023）》</a>");
    ui->newslabel5->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073521.htm\">我校举办“2023年中山大学辅导员年度人物”评选活动</a>");



    //    //label
    //    QPixmap p(":/new/stu1/bkjw.jpg");
    //    ui->jwTitle_2->setPixmap(p);
    //    ui->jwTitle_2->setScaledContents(true);
    //    QPixmap i(":/new/stu1/user48.png");
    //    ui->label_3->setPixmap(i);
    //    ui->label_3->setScaledContents(false);
    QPixmap x1(":/new/main_window_stu/choose.png");
    ui->btn_PickClass->setIcon(QIcon(x1));
    ui->btn_PickClass->setIconSize(x1.size());

    QPixmap x2(":/new/main_window_stu/schedule.png");
    ui->btn_MyClass->setIcon(QIcon(x2));
    ui->btn_MyClass->setIconSize(x2.size());

    QPixmap x3(":/new/main_window_stu/myscore.png");
    ui->btn_MyScore->setIcon(QIcon(x3));
    ui->btn_MyScore->setIconSize(x3.size());

    ui->widget_4->setStyleSheet("background-color:#138dff;");
    //label
    QPixmap x4(":/new/main_window_stu/bkjw.jpg");
    ui->jwTitle_2->setPixmap(x4);
    ui->jwTitle_2->setScaledContents(true);

    //按钮
    QPixmap x5(":/new/main_window_stu/user48.png");
    ui->btn_HeadPortrait->setIcon(x5);
    ui->btn_HeadPortrait->setIconSize(x5.size());
    QPixmap x6(":/new/main_window_stu/exit48.png");
    ui->btn_Exit->setIcon(QIcon(x6));
    ui->btn_Exit->setIconSize(x6.size());

}

StudentMainWindow::~StudentMainWindow()
{
    delete ui;
}

void StudentMainWindow::on_newslabel1_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void StudentMainWindow::on_newslabel2_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void StudentMainWindow::on_newslabel3_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void StudentMainWindow::on_newslabel4_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

void StudentMainWindow::on_newslabel5_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void StudentMainWindow::on_btn_Exit_clicked()
{
//    Frm_Login* login = new Frm_Login;
//    login->setAttribute(Qt::WA_DeleteOnClose);
//    login->show();
    this->close();
}


void StudentMainWindow::on_btn_PickClass_clicked()
{
    Frm_StuPickClass* frmPickClass = new Frm_StuPickClass(this->stuID, this->stuName);
    frmPickClass->setAttribute(Qt::WA_DeleteOnClose);
    frmPickClass->show();
}


void StudentMainWindow::on_btn_MyClass_clicked()
{
    Frm_StuMyClass* frmMyClass = new Frm_StuMyClass(this->stuID, this->stuName);
    frmMyClass->setAttribute(Qt::WA_DeleteOnClose);
    frmMyClass->show();
}


void StudentMainWindow::on_btn_MyScore_clicked()
{
    Frm_StuMyScore* frmMyScore = new Frm_StuMyScore(this->stuID, this->stuName);
    frmMyScore->setAttribute(Qt::WA_DeleteOnClose);
    frmMyScore->show();
}


void StudentMainWindow::on_btn_HeadPortrait_clicked()
{
    stu_info* si = new stu_info(this->stuID);
    si->setAttribute(Qt::WA_DeleteOnClose);
    si->show();
}

