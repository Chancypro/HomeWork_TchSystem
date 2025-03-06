#include "frm_stu_info_manage.h"
#include "qgraphicseffect.h"
#include "ui_frm_stu_info_manage.h"
#include "admin_info.h"
#include "SqlOperation.h"
#include <QMessageBox>

using namespace UserEnum;

Frm_StuInfoManage::Frm_StuInfoManage(int admID, const QString& admName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frm_StuInfoManage),
    admID(admID), admName(admName)
{
    ui->setupUi(this);
    beautify();

    this->saveState = SaveState::Add;

    ui->lbl_AdmID->setText(QString::number(this->admID));
    ui->lbl_AdmName->setText(this->admName);
    ui->sp_Grade->setEnabled(false);
    connect(this, &Frm_StuInfoManage::SaveStateChanged, &Frm_StuInfoManage::on_SaveStateChanged);
    this->InitWindow();
}

void Frm_StuInfoManage::beautify()
{
    this->setWindowTitle("学生信息");
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
    //美化
    //顶部栏
    ui->widget_4->setStyleSheet("background-color:#138dff;");
    //label
    QPixmap p(":/new/stu1/bkjw.jpg");
    ui->jwTitle_2->setPixmap(p);
    ui->jwTitle_2->setScaledContents(true);

    //按钮
    QPixmap i(":/new/stu1/user48.png");
    ui->btn_HeadPortrait->setIcon(i);
    ui->btn_HeadPortrait->setIconSize(i.size());
    QPixmap x(":/new/stu1/exit48.png");
    ui->btn_Exit->setIcon(QIcon(x));
    ui->btn_Exit->setIconSize(x.size());
    //表格
    ui->tbW_StuInfo->setAlternatingRowColors(true);
    QHeaderView *head = ui->tbW_StuInfo->horizontalHeader();
    head->setFixedHeight(30);
    // 设置表头背景颜色和边框
    head->setStyleSheet("QHeaderView::section {"
                        "    background-color: #5b9bd5;"  // 设置表头背景颜色
                        "    border:solid rgb(210, 211, 255);"  // 设置表头边框宽度和颜色
                        "}");
    //
    QGraphicsDropShadowEffect *shadow1 = new QGraphicsDropShadowEffect;
    shadow1->setBlurRadius(10);
    shadow1->setColor(QColor(0, 0, 0, 80));
    shadow1->setOffset(0, 0);
    ui->widget_6->setGraphicsEffect(shadow1);
}

Frm_StuInfoManage::~Frm_StuInfoManage()
{
    delete ui;
}

void Frm_StuInfoManage::on_SaveStateChanged(){
    if(this->saveState == SaveState::Add){
        ui->sp_NetID->setEnabled(true);
        ui->sp_Age->setEnabled(true);
        ui->sp_Grade->setEnabled(false);

        ui->le_Name->setEnabled(true);
        ui->le_Department->setEnabled(true);
        ui->le_Major->setEnabled(true);

        ui->cbb_UserType->setEnabled(false);
        ui->cbb_Gender->setEnabled(true);
    }else{
        ui->sp_NetID->setEnabled(false);
        ui->sp_Age->setEnabled(false);
        ui->sp_Grade->setEnabled(false);

        ui->le_Name->setEnabled(true);
        ui->le_Department->setEnabled(true);
        ui->le_Major->setEnabled(true);

        ui->cbb_UserType->setEnabled(false);
        ui->cbb_Gender->setEnabled(true);
    }
}

void Frm_StuInfoManage::on_btn_Exit_clicked()
{
    this->close();
}

void Frm_StuInfoManage::InitWindow(){

    this->InitStuTableWidget();
    //this->InitUserTableWidget();

    ui->tbW_StuInfo->show();

    ui->cbb_Gender->addItem("");
    ui->cbb_Gender->addItem("");
    ui->cbb_Gender->setItemText(GenderType::Male, "男");
    ui->cbb_Gender->setItemText(GenderType::Female, "女");

    ui->cbb_UserType->addItem("");
    ui->cbb_UserType->addItem("");
    ui->cbb_UserType->setItemText(UserType::Teacher-UserType::Teacher, "教师");
    ui->cbb_UserType->setItemText(UserType::Student-UserType::Teacher, "学生");

    ui->cbb_UserType->setEnabled(false);
    ui->cbb_UserType->setCurrentIndex(1);
}

void Frm_StuInfoManage::InitStuTableWidget(){
    //ui->tbW_StuInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem* item_NetID = new QTableWidgetItem;
    item_NetID->setText("NetID");

    QTableWidgetItem* item_Name = new QTableWidgetItem;
    item_Name->setText("姓名");

    QTableWidgetItem* item_Gender = new QTableWidgetItem;
    item_Gender->setText("性别");

    QTableWidgetItem* item_Age = new QTableWidgetItem;
    item_Age->setText("年龄");

    QTableWidgetItem* item_Department = new QTableWidgetItem;
    item_Department->setText("所在学院");

    QTableWidgetItem* item_Major = new QTableWidgetItem;
    item_Major->setText("所选专业");

    QTableWidgetItem* item_Grade = new QTableWidgetItem;
    item_Grade->setText("年级");

    ui->tbW_StuInfo->setColumnCount(StuInfoList::StuListCount);
    ui->tbW_StuInfo->setHorizontalHeaderItem(StuInfoList::StuNetID, item_NetID);
    ui->tbW_StuInfo->setHorizontalHeaderItem(StuInfoList::StuName, item_Name);
    ui->tbW_StuInfo->setHorizontalHeaderItem(StuInfoList::StuGender, item_Gender);
    ui->tbW_StuInfo->setHorizontalHeaderItem(StuInfoList::StuAge, item_Age);
    ui->tbW_StuInfo->setHorizontalHeaderItem(StuInfoList::StuDepartment, item_Department);
    ui->tbW_StuInfo->setHorizontalHeaderItem(StuInfoList::StuMajor, item_Major);
    ui->tbW_StuInfo->setHorizontalHeaderItem(StuInfoList::StuGrade, item_Grade);

    for(int i = 0; i < StuInfoList::StuListCount; i++){
        ui->tbW_StuInfo->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    this->DataBind_StuInfo();
}

void Frm_StuInfoManage::DataBind_StuInfo(){
    ui->tbW_StuInfo->setRowCount(0);

    QT_TRY{
        QSqlQuery query = SqlOperation::SearchStuInfo();

        while(query.next()){
            int curRow = ui->tbW_StuInfo->rowCount();
            ui->tbW_StuInfo->insertRow(curRow);

            QTableWidgetItem* item_NetID = new QTableWidgetItem;
            item_NetID->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Name = new QTableWidgetItem;
            item_Name->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Gender = new QTableWidgetItem;
            item_Gender->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Age = new QTableWidgetItem;
            item_Age->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Department = new QTableWidgetItem;
            item_Department->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Major = new QTableWidgetItem;
            item_Major->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Grade = new QTableWidgetItem;
            item_Grade->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            item_NetID->setText(query.value("stuID").toString());
            item_Name->setText(query.value("name").toString());
            item_Gender->setText(query.value("gender").toInt() == GenderType::Male ? "男" : "女");
            item_Age->setText(query.value("age").toString());
            item_Department->setText(query.value("department").toString());
            item_Major->setText(query.value("major").toString());
            item_Grade->setText(query.value("grade").toString());

            ui->tbW_StuInfo->setItem(curRow, StuInfoList::StuNetID, item_NetID);
            ui->tbW_StuInfo->setItem(curRow, StuInfoList::StuName, item_Name);
            ui->tbW_StuInfo->setItem(curRow, StuInfoList::StuGender, item_Gender);
            ui->tbW_StuInfo->setItem(curRow, StuInfoList::StuAge, item_Age);
            ui->tbW_StuInfo->setItem(curRow, StuInfoList::StuDepartment, item_Department);
            ui->tbW_StuInfo->setItem(curRow, StuInfoList::StuMajor, item_Major);
            ui->tbW_StuInfo->setItem(curRow, StuInfoList::StuGrade, item_Grade);
        }
    }
    QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }
}

void Frm_StuInfoManage::ClearInfo(){
    ui->sp_NetID->setValue(ui->sp_NetID->minimum());
    ui->le_Name->setText("");
    ui->cbb_Gender->setCurrentIndex(GenderType::Male-GenderType::Male);
    ui->sp_Age->setValue(ui->sp_Age->minimum());

    ui->le_Department->setText("");
    ui->le_Major->setText("");

    ui->cbb_UserType->setCurrentIndex(UserType::Student-UserType::Teacher);

    this->saveState = SaveState::Add;
    emit this->SaveStateChanged();
}

void Frm_StuInfoManage::on_btn_Clear_clicked()
{
    this->ClearInfo();
}

void Frm_StuInfoManage::on_btn_Delete_clicked()
{
    int curRow = ui->tbW_StuInfo->currentRow();
    if(curRow < 0 || curRow >= ui->tbW_StuInfo->rowCount()){
        return;
    }

    int id = ui->tbW_StuInfo->item(curRow, 0)->text().toInt();
    QString msg = QString("是否要删除NetID为%1的用户？").arg(id);
    if(QMessageBox::question(this, DELETE_INFO_NOTE, msg) == QMessageBox::Yes){
        QT_TRY{
            int res = SqlOperation::DeleteUserInfo(id);
            if(res > 0){
                QMessageBox::information(this, DELETE_INFO_NOTE, "删除成功！");
                this->DataBind_StuInfo();
                this->ClearInfo();
            }else{
                QMessageBox::information(this, DELETE_INFO_NOTE, "删除失败！");
            }
        }
        QT_CATCH(QString msg){
            QMessageBox::critical(this, ERR_NOTE, msg);
        }

    }
}

void Frm_StuInfoManage::on_btn_SaveInfo_clicked()
{
    int netID = ui->sp_NetID->value();
    QString pwd = QString("sysu_%1").arg(netID);
    QString name = ui->le_Name->text();
    GenderType gender = (GenderType)ui->cbb_Gender->currentIndex();
    int age = ui->sp_Age->value();
    ::UserType userType = ::UserType(ui->cbb_UserType->currentIndex() + UserType::Teacher);
    QString department = ui->le_Department->text();

    if(name == ""){
        QMessageBox::information(this, "提示","姓名不能为空！");
        return;
    }
    if(department == ""){
        QMessageBox::information(this, "提示","院系不能为空！");
        return;
    }

    QString major = ui->le_Major->text();
    int grade = ui->sp_Grade->value();

    if(major == ""){
        QMessageBox::information(this, "提示", "专业不能为空！");
        return;
    }

    if(this->saveState == SaveState::Add){
        QT_TRY{
            int res1 = SqlOperation::AddUserInfo(netID, pwd, userType, Status::On);
            int res2 = SqlOperation::AddStuInfo(netID, name, gender, age, department, major, grade, 0);
            if(res1 > 0 && res2 > 0){
                this->DataBind_StuInfo();
                this->ClearInfo();
                QMessageBox::information(this, "提示", "添加成功！");
            }else{
                SqlOperation::DeleteUserInfo(netID, false);
                QMessageBox::information(this, "提示", "添加失败！");
            }
        }QT_CATCH(QString msg){
            QMessageBox::critical(this, ERR_NOTE, msg);
        }
    }
    else{
        QT_TRY{
            int res = SqlOperation::UpdateStuInfo(netID, name, gender, age, department, major, grade);
            if(res > 0){
                this->DataBind_StuInfo();
                QMessageBox::information(this, "提示", "修改成功！");
            }else{
                SqlOperation::DeleteUserInfo(netID, false);
                QMessageBox::information(this, "提示", "修改失败！");
            }
        }QT_CATCH(QString msg){
            QMessageBox::critical(this, ERR_NOTE, msg);
        }
    }

}

void Frm_StuInfoManage::on_tbW_StuInfo_itemClicked(QTableWidgetItem *item)
{
    int curRow = ui->tbW_StuInfo->currentRow();

    ui->le_Name->setText(ui->tbW_StuInfo->item(curRow, StuInfoList::StuName)->text());
    ui->le_Department->setText(ui->tbW_StuInfo->item(curRow, StuInfoList::StuDepartment)->text());
    ui->le_Major->setText(ui->tbW_StuInfo->item(curRow, StuInfoList::StuMajor)->text());

    ui->sp_Age->setValue(ui->tbW_StuInfo->item(curRow, StuInfoList::StuAge)->text().toInt());
    ui->sp_Grade->setValue(ui->tbW_StuInfo->item(curRow, StuInfoList::StuGrade)->text().toInt());
    ui->sp_NetID->setValue(ui->tbW_StuInfo->item(curRow, StuInfoList::StuNetID)->text().toInt());

    QString str = ui->tbW_StuInfo->item(curRow, StuInfoList::StuGender)->text();
    for(int i = 0; i < UserEnum::GenderTypeCount; i++){
        if(UserEnum::GenderTypeStr[i] == str){
            ui->cbb_Gender->setCurrentIndex(i);
            break;
        }
    }

    this->saveState = SaveState::Save;
    emit this->SaveStateChanged();
}


void Frm_StuInfoManage::on_btn_HeadPortrait_clicked()
{
    admin_info* ai = new admin_info(this->admID);
    ai->setAttribute(Qt::WA_DeleteOnClose);
    ai->show();
}

