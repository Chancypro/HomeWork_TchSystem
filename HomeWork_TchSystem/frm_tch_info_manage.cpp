#include "frm_tch_info_manage.h"
#include "qgraphicseffect.h"
#include "ui_frm_tch_info_manage.h"
#include "SqlOperation.h"
#include "admin_info.h"
#include <QMessageBox>

using namespace UserEnum;

Frm_TchInfoManage::Frm_TchInfoManage(int admID, const QString& admName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frm_TchInfoManage),
    admID(admID), admName(admName)
{
    ui->setupUi(this);
    beautify();

    ui->lbl_AdmID->setText(QString::number(this->admID));
    ui->lbl_AdmName->setText(this->admName);

    connect(this, &Frm_TchInfoManage::SaveStateChanged, &Frm_TchInfoManage::on_SaveStateChanged);

    this->InitWindow();
}

void Frm_TchInfoManage::beautify()
{
    this->setWindowTitle("教师信息");
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
    ui->tbW_TchInfo->setAlternatingRowColors(true);
    QHeaderView *head = ui->tbW_TchInfo->horizontalHeader();
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

Frm_TchInfoManage::~Frm_TchInfoManage()
{
    delete ui;
}

void Frm_TchInfoManage::InitWindow(){

    this->InitTchTableWidget();
    //this->InitUserTableWidget();

    ui->cbb_Gender->addItem("");
    ui->cbb_Gender->addItem("");
    ui->cbb_Gender->setItemText(GenderType::Male, "男");
    ui->cbb_Gender->setItemText(GenderType::Female, "女");

    ui->cbb_UserType->setEnabled(false);
    ui->cbb_UserType->addItem("");
    ui->cbb_UserType->addItem("");
    ui->cbb_UserType->setItemText(UserType::Teacher-UserType::Teacher, "教师");
    ui->cbb_UserType->setItemText(UserType::Student-UserType::Teacher, "学生");

    for(int i = 0; i < UserEnum::TchPositionCount-1; i++){
        ui->cbb_Position->addItem(UserEnum::TchPositionStr[i]);
    }
}

void Frm_TchInfoManage::InitTchTableWidget(){
    //ui->tbW_TchInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

    QTableWidgetItem* item_Position = new QTableWidgetItem;
    item_Position->setText("职位");

    ui->tbW_TchInfo->setColumnCount(TchInfoList::TchListCount);
    ui->tbW_TchInfo->setHorizontalHeaderItem(TchInfoList::TchNetID, item_NetID);
    ui->tbW_TchInfo->setHorizontalHeaderItem(TchInfoList::TchName, item_Name);
    ui->tbW_TchInfo->setHorizontalHeaderItem(TchInfoList::TchGender, item_Gender);
    ui->tbW_TchInfo->setHorizontalHeaderItem(TchInfoList::TchAge, item_Age);
    ui->tbW_TchInfo->setHorizontalHeaderItem(TchInfoList::TchDepartment, item_Department);
    ui->tbW_TchInfo->setHorizontalHeaderItem(TchInfoList::TchPosition, item_Position);

    for(int i = 0; i < TchInfoList::TchListCount; i++){
        ui->tbW_TchInfo->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    this->DataBind_TchInfo();
}

void Frm_TchInfoManage::DataBind_TchInfo(){
    ui->tbW_TchInfo->setRowCount(0);

    QT_TRY{
        QSqlQuery query = SqlOperation::SearchTchInfo();

        while(query.next()){
            int curRow = ui->tbW_TchInfo->rowCount();
            ui->tbW_TchInfo->insertRow(curRow);

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

            QTableWidgetItem* item_Position = new QTableWidgetItem;
            item_Position->setTextAlignment(Qt::AlignmentFlag::AlignCenter);


            item_NetID->setText(query.value("tchID").toString());
            item_Name->setText(query.value("name").toString());
            item_Gender->setText(query.value("gender").toInt() == GenderType::Male ? "男" : "女");
            item_Age->setText(query.value("age").toString());
            item_Department->setText(query.value("department").toString());
            item_Position->setText(TchPositionStr[query.value("position").toInt()-1]);


            ui->tbW_TchInfo->setItem(curRow, TchInfoList::TchNetID, item_NetID);
            ui->tbW_TchInfo->setItem(curRow, TchInfoList::TchName, item_Name);
            ui->tbW_TchInfo->setItem(curRow, TchInfoList::TchGender, item_Gender);
            ui->tbW_TchInfo->setItem(curRow, TchInfoList::TchAge, item_Age);
            ui->tbW_TchInfo->setItem(curRow, TchInfoList::TchDepartment, item_Department);
            ui->tbW_TchInfo->setItem(curRow, TchInfoList::TchPosition, item_Position);
        }
    }
    QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }


}

void Frm_TchInfoManage::ClearInfo(){
    ui->sp_NetID->setValue(ui->sp_NetID->minimum());
    ui->le_Name->setText("");
    ui->cbb_Gender->setCurrentIndex(GenderType::Male-GenderType::Male);
    ui->sp_Age->setValue(ui->sp_Age->minimum());

    ui->le_Department->setText("");

    ui->cbb_UserType->setCurrentIndex(UserType::Teacher-UserType::Teacher);
    ui->cbb_Position->setCurrentIndex(UserEnum::TchPosition::Lecture - UserEnum::TchPosition::Lecture);

    this->saveState = SaveState::Add;
    emit this->SaveStateChanged();
}

void Frm_TchInfoManage::on_SaveStateChanged(){
    if(this->saveState == SaveState::Add){
        ui->le_Name->setEnabled(true);
        ui->le_Department->setEnabled(true);

        ui->sp_Age->setEnabled(true);
        ui->sp_NetID->setEnabled(true);

        ui->cbb_Gender->setEnabled(true);
        ui->cbb_Position->setEnabled(true);
        ui->cbb_UserType->setEnabled(false);

    }else{
        ui->le_Name->setEnabled(true);
        ui->le_Department->setEnabled(true);

        ui->sp_Age->setEnabled(false);
        ui->sp_NetID->setEnabled(false);

        ui->cbb_Gender->setEnabled(true);
        ui->cbb_Position->setEnabled(true);
        ui->cbb_UserType->setEnabled(false);
    }
}

void Frm_TchInfoManage::on_btn_Exit_clicked()
{
    this->close();
}

void Frm_TchInfoManage::on_btn_Clear_clicked()
{
    this->ClearInfo();
}

void Frm_TchInfoManage::on_btn_Delete_clicked()
{
    int curRow = ui->tbW_TchInfo->currentRow();
    if(curRow < 0 || curRow >= ui->tbW_TchInfo->rowCount()){
        return;
    }

    int id = ui->tbW_TchInfo->item(curRow, 0)->text().toInt();
    QString msg = QString("是否要删除NetID为%1的用户？").arg(id);
    if(QMessageBox::question(this, DELETE_INFO_NOTE, msg) == QMessageBox::Yes){
        QT_TRY{
            int res = SqlOperation::DeleteUserInfo(id);
            if(res > 0){
                QMessageBox::information(this, DELETE_INFO_NOTE, "删除成功！");
                this->DataBind_TchInfo();
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

void Frm_TchInfoManage::on_btn_SaveInfo_clicked()
{
    int netID = ui->sp_NetID->value();
    QString pwd = QString("sysu_%1").arg(netID);
    QString name = ui->le_Name->text();
    GenderType gender = (GenderType)ui->cbb_Gender->currentIndex();
    int age = ui->sp_Age->value();
    ::UserType userType = ::UserType(ui->cbb_UserType->currentIndex() + UserType::Teacher);
    QString department = ui->le_Department->text();
    UserEnum::TchPosition position = UserEnum::TchPosition(ui->cbb_Position->currentIndex() + UserEnum::TchPosition::Lecture);

    if(name == ""){
        QMessageBox::information(this, "提示", "姓名不能为空！");
        return;
    }
    if(department == ""){
        QMessageBox::information(this, "提示", "院系不能为空！");
        return;
    }

    if(this->saveState == SaveState::Add){
        QT_TRY{
            int res1 = SqlOperation::AddUserInfo(netID, pwd, userType, Status::On);
            int res2 = SqlOperation::AddTchInfo(netID, name, gender, age, department, position);
            if(res1 > 0 && res2 > 0){
                this->DataBind_TchInfo();
                this->ClearInfo();
                QMessageBox::information(this, "提示", "添加成功！");
            }else{
                SqlOperation::DeleteUserInfo(netID, false);
                QMessageBox::information(this, "提示", "添加失败！");
            }
        }QT_CATCH(QString msg){
            QMessageBox::critical(this, ERR_NOTE, msg);
        }
    }else{

        QT_TRY{
            int res = SqlOperation::UpdateTchInfo(netID, name, gender, age, department, position);
            if(res > 0){
                this->DataBind_TchInfo();
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

void Frm_TchInfoManage::on_tbW_TchInfo_itemClicked(QTableWidgetItem *item)
{
    int curRow = ui->tbW_TchInfo->currentRow();

    ui->le_Name->setText(ui->tbW_TchInfo->item(curRow, TchInfoList::TchName)->text());
    ui->le_Department->setText(ui->tbW_TchInfo->item(curRow, TchInfoList::TchDepartment)->text());

    ui->sp_Age->setValue(ui->tbW_TchInfo->item(curRow, TchInfoList::TchAge)->text().toInt());
    ui->sp_NetID->setValue(ui->tbW_TchInfo->item(curRow, TchInfoList::TchNetID)->text().toInt());

    QString gender = ui->tbW_TchInfo->item(curRow, TchInfoList::TchGender)->text();
    for(int i = 0; i < UserEnum::GenderTypeCount; i++){
        if(UserEnum::GenderTypeStr[i] == gender){
            ui->cbb_Gender->setCurrentIndex(i);
            break;
        }
    }

    QString position = ui->tbW_TchInfo->item(curRow, TchInfoList::TchPosition)->text();
    for(int i = 0; i < UserEnum::TchPositionCount-1; i++){
        if(UserEnum::TchPositionStr[i] == position){
            ui->cbb_Position->setCurrentIndex(i);
            break;
        }
    }

    this->saveState = SaveState::Save;
    emit this->SaveStateChanged();
}


void Frm_TchInfoManage::on_btn_HeadPortrait_clicked()
{
    admin_info* ai = new admin_info(this->admID);
    ai->setAttribute(Qt::WA_DeleteOnClose);
    ai->show();
}

