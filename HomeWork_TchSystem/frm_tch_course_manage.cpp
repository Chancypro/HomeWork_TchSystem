#include "frm_tch_course_manage.h"
#include "ui_frm_tch_course_manage.h"
#include "SqlOperation.h"
#include "frm_course_detial_info.h"
#include "tch_info.h"
#include <QMessageBox>

Frm_TchCourseManage::Frm_TchCourseManage(int tchID, const QString& tchName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frm_TchCourseManage),
    tchID(tchID), tchName(tchName)
{
    ui->setupUi(this);
    this->beautify();

    this->courseInfoListHeader[CourseInfoList::CourseID] = "课程编号";
    this->courseInfoListHeader[CourseInfoList::CourseName] = "课程名称";
    this->courseInfoListHeader[CourseInfoList::CourseAddress] = "开课地点";
    this->courseInfoListHeader[CourseInfoList::CourseCredit] = "学分";
    this->courseInfoListHeader[CourseInfoList::CoursePeriod] = "学时";
    this->courseInfoListHeader[CourseInfoList::CourseStatus] = "状态";
    this->courseInfoListHeader[CourseInfoList::CourseTch] = "授课教师";
    this->courseInfoListHeader[CourseInfoList::CourseType] = "类型";

    ui->lbl_TchID->setText(QString::number(this->tchID));
    ui->lbl_TchID2->setText(QString::number(this->tchID));
    ui->lbl_TchName->setText(this->tchName);
    ui->lbl_TchName2->setText(this->tchName);

    ui->cbb_Term->addItem("第一学期");
    ui->cbb_Term->addItem("第二学期");

    this->trW_currentSelectedCourse = NullCourseID;

    QSqlQuery query = SqlOperation::ProgressQuery();
    query.next();
    int year = query.value("year").toInt();
    int term = query.value("term").toInt();
    ui->spb_Year->setValue(year);
    ui->cbb_Term->setCurrentIndex(term-1);

    this->InitCourseTableWidget();

}

void Frm_TchCourseManage::beautify()
{
    this->setWindowTitle("课程管理");
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
    ui->tbW_CourseInfo->verticalHeader()->setVisible(false);
    ui->tbW_CourseInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //美化
    //顶部栏
    ui->widget_4->setStyleSheet("background-color:#138dff;");
    //label
    QPixmap p(":/new/stu1/bkjw.jpg");
    ui->jwTitle_4->setPixmap(p);
    ui->jwTitle_4->setScaledContents(true);
    //按钮
    QPixmap i(":/new/stu1/user48.png");
    ui->btn_HeadPortrait->setIcon(i);
    ui->btn_HeadPortrait->setIconSize(i.size());
    QPixmap x(":/new/stu1/exit48.png");
    ui->btn_Exit->setIcon(QIcon(x));
    ui->btn_Exit->setIconSize(x.size());
    //表格
    ui->tbW_CourseInfo->setAlternatingRowColors(true);
    QHeaderView *head = ui->tbW_CourseInfo->horizontalHeader();
    head->setFixedHeight(30);
    // 设置表头背景颜色和边框
    head->setStyleSheet("QHeaderView::section {"
                        "    background-color: #5b9bd5;"  // 设置表头背景颜色
                        "    border:solid rgb(210, 211, 255);"  // 设置表头边框宽度和颜色
                        "}");
}

void Frm_TchCourseManage::InitCourseTableWidget(){
    ui->tbW_CourseInfo->setColumnCount(CourseInfoList::CourseInfoListCount);
    ui->tbW_CourseInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tbW_CourseInfo->setSelectionBehavior(QAbstractItemView::SelectRows);

    for(int i = 0; i < CourseInfoList::CourseInfoListCount; i++){
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(this->courseInfoListHeader[i]);
        ui->tbW_CourseInfo->setHorizontalHeaderItem(i, item);
        ui->tbW_CourseInfo->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());

}

void Frm_TchCourseManage::DataBind_CourseInfo(int year, int term, const QString& courseName, const QString& courseTchName){
    ui->tbW_CourseInfo->setRowCount(0);

    QT_TRY{
        QSqlQuery query = SqlOperation::SearchCourseInfo(year, term, courseName, courseTchName);
        while(query.next()){
            int curRow = ui->tbW_CourseInfo->rowCount();
            ui->tbW_CourseInfo->insertRow(curRow);

            QTableWidgetItem* item_id = new QTableWidgetItem;
            item_id->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_name = new QTableWidgetItem;
            item_name->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_courseType = new QTableWidgetItem;
            item_courseType->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_address = new QTableWidgetItem;
            item_address->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_credit = new QTableWidgetItem;
            item_credit->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_period = new QTableWidgetItem;
            item_period->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_status = new QTableWidgetItem;
            item_status->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Tch = new QTableWidgetItem;
            item_Tch->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            item_id->setText(query.value("course_info.id").toString());
            item_name->setText(query.value("course_info.name").toString());
            item_Tch->setText(query.value("tch_info.name").toString());
            item_courseType->setText(CourseEnum::CourseTypeStr[query.value("courseType").toInt()]);
            item_credit->setText(query.value("credit").toString());
            item_period->setText(QString::number(query.value("period").toDouble(), 'f', 2));
            item_status->setText(CourseEnum::CourseStatusStr[query.value("status").toInt()]);
            item_address->setText(query.value("address").toString());

            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CourseID, item_id);
            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CourseName, item_name);
            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CourseTch, item_Tch);
            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CourseType, item_courseType);
            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CourseCredit, item_credit);
            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CoursePeriod, item_period);
            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CourseAddress, item_address);
            ui->tbW_CourseInfo->setItem(curRow, CourseInfoList::CourseStatus, item_status);
        }
    }
    QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }


}

Frm_TchCourseManage::~Frm_TchCourseManage()
{
    delete ui;
}

void Frm_TchCourseManage::on_spb_Year_valueChanged(int arg1)
{
    this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());
}


void Frm_TchCourseManage::on_cbb_Term_currentIndexChanged(int index)
{
    this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());
}


void Frm_TchCourseManage::on_tbW_CourseInfo_itemDoubleClicked(QTableWidgetItem *item)
{
    int curRow = ui->tbW_CourseInfo->currentRow();
    int courseID = ui->tbW_CourseInfo->item(curRow, CourseInfoList::CourseID)->text().toInt();
    Frm_CourseDetialInfo* frm_CDI = new Frm_CourseDetialInfo(courseID, this->tchID, this->tchName, IDType::TchID);
    frm_CDI->setAttribute(Qt::WA_DeleteOnClose);
    frm_CDI->show();

    connect(frm_CDI, &Frm_CourseDetialInfo::DataChanged, this, &Frm_TchCourseManage::on_frm_cdi_data_changed);
}


void Frm_TchCourseManage::on_btn_AddCourse_clicked()
{
    QSqlQuery query = SqlOperation::ProgressQuery();
    query.next();
    int progress = query.value("progress").toInt();
    int year = query.value("year").toInt();
    int term = query.value("term").toInt();
    if(progress != ProgressInfo::PrepareCourse1 && progress != ProgressInfo::PrepareCourse2){
        QMessageBox::information(this, "提示", "已过准备课程信息时间，无法再添加课程！");
        return;
    }

    Frm_CourseDetialInfo* frm_CDI = new Frm_CourseDetialInfo(NullCourseID, this->tchID, this->tchName, IDType::TchID, year, term);
    frm_CDI->setAttribute(Qt::WA_DeleteOnClose);
    frm_CDI->show();
    connect(frm_CDI, &Frm_CourseDetialInfo::DataChanged, this, &Frm_TchCourseManage::on_frm_cdi_data_changed);
}


void Frm_TchCourseManage::on_btn_RemoveCourse_clicked()
{
    QSqlQuery query = SqlOperation::ProgressQuery();
    query.next();
    int progress = query.value("progress").toInt();
    if(progress != ProgressInfo::PrepareCourse1 && progress != ProgressInfo::PrepareCourse2){
        QMessageBox::information(this, "提示", "已过准备课程信息时间，无法再删除课程！");
        return;
    }

    int curRow = ui->tbW_CourseInfo->currentRow();
    if(curRow >= 0){
        QString courseStatus = ui->tbW_CourseInfo->item(curRow, CourseInfoList::CourseStatus)->text();
        QString courseTchName = ui->tbW_CourseInfo->item(curRow, CourseInfoList::CourseTch)->text();
        if(courseTchName != this->tchName){
            QMessageBox::information(this, "提示", "无法删除该课程！");
            return;
        }
        //未开放才能删除
        if(courseStatus == CourseEnum::CourseStatusStr[CourseEnum::CourseStatus::UnOpen]){
            int courseID = ui->tbW_CourseInfo->item(curRow, CourseInfoList::CourseID)->text().toInt();
            if(QMessageBox::question(this, "提示", QString("是否删除课程编号为 %1 的课程？").arg(courseID)) == QMessageBox::Yes){
                QT_TRY{
                    int res = SqlOperation::DeleteCourseInfo(courseID);
                    if(res > 0){
                        QMessageBox::information(this, "提示", "删除成功！");
                        this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());
                    }else{
                        QMessageBox::information(this, "提示", "删除失败！");
                    }
                }QT_CATCH(QString msg){
                    QMessageBox::warning(this, ERR_NOTE, msg);
                }

            }

        }else{
            QMessageBox::information(this, "提示", "该课程已无法删除！");
        }
    }
}

void Frm_TchCourseManage::on_frm_cdi_data_changed(){
    this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());
}


void Frm_TchCourseManage::on_btn_Search_clicked()
{
    this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());
}


void Frm_TchCourseManage::on_btn_Exit_clicked()
{
    this->close();
}


void Frm_TchCourseManage::on_le_CourseName_textChanged(const QString &arg1)
{
    this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());
}


void Frm_TchCourseManage::on_le_CourseTchName_textChanged(const QString &arg1)
{
    this->DataBind_CourseInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->le_CourseName->text(), ui->le_CourseTchName->text());
}


void Frm_TchCourseManage::on_btn_HeadPortrait_clicked()
{
    tch_info* ti = new tch_info(this->tchID);
    ti->setAttribute(Qt::WA_DeleteOnClose);
    ti->show();
}

