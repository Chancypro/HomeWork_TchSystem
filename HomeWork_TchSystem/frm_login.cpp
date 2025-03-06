#include "frm_login.h"
#include "ui_frm_login.h"
#include "main_window_admin.h"
#include "main_window_stu.h"
#include "main_window_tch.h"
#include <QPalette>
#include <QGraphicsDropShadowEffect>

Frm_Login::Frm_Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frm_login)
{
    ui->setupUi(this);
    this->beautify();

    ui->le_Pwd->setEchoMode(QLineEdit::EchoMode::Password);
}

void Frm_Login::beautify()
{
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
    this->setWindowTitle("中山大学教务管理系统欢迎您");
    //美化
    //顶部栏
    ui->widget_5->setStyleSheet("background-color:#138dff;");
    //label
    QPixmap p(":/new/stu1/bkjw.jpg");
    ui->jwTitle_2->setPixmap(p);
    ui->jwTitle_2->setScaledContents(true);

    //登录框
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 0);
    ui->widget->setGraphicsEffect(shadow);

    QPixmap x(":/new/stu1/loginf.jpg");
    ui->LoginTitle->setPixmap(x);
    ui->LoginTitle->setScaledContents(false);

}

void Frm_Login::on_btn_Login_clicked(){
    bool flag = true;
    int netID = ui->le_NetID->text().toInt(&flag);
    QString pwd = ui->le_Pwd->text();

    if(!flag){
        QMessageBox::information(this, "提示", "请输入正确形式的NetID!");
    }else if(pwd == ""){
        QMessageBox::information(this, "提示", "请输入密码！");
    }else{
        QT_TRY{
            QSqlQuery query = SqlOperation::new_Login(netID, pwd);
            if(query.next()){
                UserEnum::UserType userType = UserEnum::UserType(query.value("user_type").toInt());
                switch(userType){
                case UserEnum::UserType::Student:{
                    query = SqlOperation::SearchTypStuInfo(netID);
                    if(query.next()){
                        StudentMainWindow* stuMW = new StudentMainWindow(netID, query.value("name").toString());
                        stuMW->setAttribute(Qt::WA_DeleteOnClose);
                        stuMW->show();
                        this->close();
                    }else{
                        QMessageBox::information(this, "提示", "该用户不存在！");
                    }
                    break;
                }

                case UserEnum::UserType::Teacher:{
                    query = SqlOperation::SearchTypTchInfo(netID);
                    if(query.next()){
                        TeacherMainWindow* tchMW = new TeacherMainWindow(netID, query.value("name").toString());
                        tchMW->setAttribute(Qt::WA_DeleteOnClose);
                        tchMW->show();
                        this->close();
                    }else{
                        QMessageBox::information(this, "提示", "该用户不存在！");
                    }
                    break;
                }

                case UserEnum::UserType::Admin:{
                    query = SqlOperation::SearchTypAdmInfo(netID);
                    if(query.next()){
                        AdminMainwindow* admMW = new AdminMainwindow(netID, query.value("name").toString());
                        admMW->setAttribute(Qt::WA_DeleteOnClose);
                        admMW->show();
                        this->close();
                    }else{
                        QMessageBox::information(this, "提示", "该用户不存在！");
                    }
                    break;
                }
                default:
                    QMessageBox::information(this, "提示", "NetID或密码错误！");
                    break;
                }
            }else{
                QMessageBox::information(this, "提示", "NetID或密码错误！");
            }
        }QT_CATCH(QString msg){
            QMessageBox::critical(this, ERR_NOTE, msg);
        }

    }
}

Frm_Login::~Frm_Login()
{
    delete ui;
}

