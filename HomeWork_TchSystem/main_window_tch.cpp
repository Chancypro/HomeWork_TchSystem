#include "main_window_tch.h"
#include "ui_main_window_tch.h"
#include "frm_tchclass_manage.h"
#include "frm_tch_course_manage.h"
#include "tch_info.h"
#include "frm_login.h"
#include <QDesktopServices>
#include <QUrl>

TeacherMainWindow::TeacherMainWindow(int tchID, const QString& tchName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherMainWindow),
    tchID(tchID), tchName(tchName)
{
    ui->setupUi(this);

    ui->lbl_TchID->setText(QString::number(this->tchID));
    ui->lbl_TchName->setText(this->tchName);

    initTeaMain();

}

void TeacherMainWindow::initTeaMain(){
    QIcon a(":/new/main_window_stu/logo.jpg");
    this->setWindowIcon(a);
    this->setWindowTitle("教师端主页");

    ui->newslabel1->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073791.htm\">高松校长率团访问香港理工大学</a>");
    ui->newslabel2->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073771.htm\">COP28大会专家热议气候适应与恢复力</a>");
    ui->newslabel3->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073671.htm\">中山大学分子工程交叉与前沿论坛暨活性中间体分析检测前沿研讨会顺利召开</a>");
    ui->newslabel4->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073701.htm\">中山大学11种科技期刊入选《科技期刊世界影响力指数（WJCI）报告（2023）》</a>");
    ui->newslabel5->setText("<a style='color: rgb(24,144,255);'href=\"https://www.sysu.edu.cn/news/info/2161/1073521.htm\">我校举办“2023年中山大学辅导员年度人物”评选活动</a>");



//    btn_TchClassManage
    QPixmap x1(":/new/main_window_stu/classmanage.png");
    ui->btn_TchClassManage->setIcon(QIcon(x1));
    ui->btn_TchClassManage->setIconSize(x1.size());

    QPixmap x2(":/new/main_window_stu/schedule.png");
    ui->btn_CourseManage->setIcon(QIcon(x2));
    ui->btn_CourseManage->setIconSize(x2.size());





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

TeacherMainWindow::~TeacherMainWindow()
{
    delete ui;
}

void TeacherMainWindow::on_newslabel1_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void TeacherMainWindow::on_newslabel2_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void TeacherMainWindow::on_newslabel3_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void TeacherMainWindow::on_newslabel4_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void TeacherMainWindow::on_newslabel5_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}


void TeacherMainWindow::on_btn_Exit_clicked()
{
//    Frm_Login* login = new Frm_Login;
//    login->setAttribute(Qt::WA_DeleteOnClose);
//    login->show();
    this->close();
}


void TeacherMainWindow::on_btn_CourseManage_clicked()
{
    Frm_TchCourseManage* frm_TCM = new Frm_TchCourseManage(this->tchID, this->tchName);
    frm_TCM->setAttribute(Qt::WA_DeleteOnClose);
    frm_TCM->show();
}


void TeacherMainWindow::on_btn_TchClassManage_clicked()
{
    Frm_TchClassManage* frm_TCM = new Frm_TchClassManage(this->tchID, this->tchName);
    frm_TCM->setAttribute(Qt::WA_DeleteOnClose);
    frm_TCM->show();
}


void TeacherMainWindow::on_btn_HeadPortrait_clicked()
{
    tch_info* ti = new tch_info(this->tchID);
    ti->setAttribute(Qt::WA_DeleteOnClose);
    ti->show();
}

