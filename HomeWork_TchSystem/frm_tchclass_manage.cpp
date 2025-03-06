#include "frm_tchclass_manage.h"
#include "ui_frm_tchclass_manage.h"
#include "SqlOperation.h"
#include "tch_info.h"
#include <QMessageBox>

Frm_TchClassManage::Frm_TchClassManage(int tchID, const QString& tchName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Frm_TchClassManage),
    tchID(tchID), tchName(tchName)
{
    ui->setupUi(this);
    this->beautify();

    ui->lbl_NetID->setText(QString::number(this->tchID));
    ui->lbl_TchName->setText(this->tchName);

    this->InitCourseList();
}

void Frm_TchClassManage::beautify(){
    this->setWindowTitle("班级管理");
    QIcon a(":/new/stu1/icon.jpg");
    this->setWindowIcon(a);
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

    //treewidget
    //美化
    ui->trW_CourseList->header()->setStyleSheet("QHeaderView::section{"
                                                "border-top-right-radius:5px;"
                                                "border-top-left-radius:5px;"
                                                "background-color:rgb(91, 155, 213);"
                                                "height:20px;"
                                                "border:5px solid rgb(91, 155, 213);}");
    //表格
    ui->tbW_ClassInfo->setAlternatingRowColors(true);
    QHeaderView *head = ui->tbW_ClassInfo->horizontalHeader();
    head->setFixedHeight(30);
    // 设置表头背景颜色和边框
    head->setStyleSheet("QHeaderView::section {"
                        "    background-color: #5b9bd5;"  // 设置表头背景颜色
                        "    border:solid rgb(210, 211, 255);"  // 设置表头边框宽度和颜色
                        "}");
}

Frm_TchClassManage::~Frm_TchClassManage()
{
    delete ui;
}

void Frm_TchClassManage::InitCourseList(){
    ui->trW_CourseList->setHeaderLabel("教学班信息");
    ui->tbW_ClassInfo->setColumnCount(TchClassEnum::TchClassInfoCount);

    QStringList list;
    for(int i = 0; i < TchClassEnum::TchClassInfoCount; i++){
        list << TchClassEnum::TchClassInfoStr[i];
    }
    ui->tbW_ClassInfo->setHorizontalHeaderLabels(list);
    for(int i = 0; i < TchClassEnum::TchClassInfoCount; i++){
        ui->tbW_ClassInfo->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    this->DataBind_CourseList();
}

void Frm_TchClassManage::DataBind_CourseList(){

    ui->trW_CourseList->clear();
    QT_TRY{
        QSqlQuery query = SqlOperation::SearchCourseList(this->tchID);
        int curYear = -1;
        QTreeWidgetItem* item_year = nullptr;
        QTreeWidgetItem* item_term[2] = {nullptr, nullptr};
        while(query.next()){
            if(curYear != query.value("year").toInt()){
                curYear = query.value("year").toInt();

                item_year = new QTreeWidgetItem;
                item_year->setText(0, QString("%1年").arg(curYear));

                item_term[0] = new QTreeWidgetItem;
                item_term[1] = new QTreeWidgetItem;

                item_term[0]->setText(0, "第一学期");
                item_term[1]->setText(0, "第二学期");

                item_year->addChild(item_term[0]);
                item_year->addChild(item_term[1]);

                ui->trW_CourseList->addTopLevelItem(item_year);
            }

            int term = query.value("course_info.term").toInt() - 1;

            QTreeWidgetItem* course = new QTreeWidgetItem;
            course->setText(0, query.value("course_info.name").toString());
            //把课程编号偷偷藏起来（
            course->setText(1, query.value("course_info.id").toString());
            course->setText(2, query.value("course_info.status").toString());
            item_term[term]->addChild(course);


        }
    }
    QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }
}

void Frm_TchClassManage::DataBind_TchClassInfo(int courseID, CourseEnum::CourseStatus courseStatus){

    ui->tbW_ClassInfo->setRowCount(0);

    if(courseStatus != CourseEnum::CourseStatus::Open){
        ui->tbW_ClassInfo->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    }else{
        ui->tbW_ClassInfo->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);
    }

    QSqlQuery query = SqlOperation::SearchTchClassInfo(courseID);
    QList<int> stuIDs;
    QList<QVariant> stuScores;
    while(query.next()){
        stuIDs.push_back(query.value("stuID").toInt());
        stuScores.push_back(query.value("stuScore"));
    }

    for(int i = 0; i < stuIDs.length(); i++){
        const int& stuID = stuIDs[i];
        const QVariant& stuScore = stuScores[i];
        int curRow = ui->tbW_ClassInfo->rowCount();
        ui->tbW_ClassInfo->insertRow(curRow);

        QSqlQuery stuInfo = SqlOperation::SearchTypStuInfo(stuID);
        if(stuInfo.next()){
            QTableWidgetItem* item_StuID = new QTableWidgetItem;
            item_StuID->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Name = new QTableWidgetItem;
            item_Name->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Gender = new QTableWidgetItem;
            item_Gender->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Department = new QTableWidgetItem;
            item_Department->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Grade = new QTableWidgetItem;
            item_Grade->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            QTableWidgetItem* item_Score = new QTableWidgetItem;
            item_Score->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            item_StuID->setText(stuInfo.value("stuID").toString());
            item_Name->setText(stuInfo.value("name").toString());

            QString gender = (UserEnum::GenderType)stuInfo.value("gender").toInt() == UserEnum::GenderType::Male ? "男" : "女";
            item_Gender->setText(gender);
            item_Department->setText(stuInfo.value("department").toString());
            item_Grade->setText(stuInfo.value("grade").toString());

            if(stuScore.isNull()){
                item_Score->setText("N/A");
            }else{
                item_Score->setText(stuScore.toString());
            }


            ui->tbW_ClassInfo->setItem(curRow, TchClassEnum::StuID, item_StuID);
            ui->tbW_ClassInfo->setItem(curRow, TchClassEnum::StuName, item_Name);
            ui->tbW_ClassInfo->setItem(curRow, TchClassEnum::StuGender, item_Gender);
            ui->tbW_ClassInfo->setItem(curRow, TchClassEnum::StuDepartment, item_Department);
            ui->tbW_ClassInfo->setItem(curRow, TchClassEnum::StuGrade, item_Grade);
            ui->tbW_ClassInfo->setItem(curRow, TchClassEnum::StuScore, item_Score);
        }

    }
}

void Frm_TchClassManage::on_trW_CourseList_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString str = item->text(1);
    bool ok[2] = {false};
    int id = str.toInt(ok);
    str = item->text(2);
    CourseEnum::CourseStatus status = (CourseEnum::CourseStatus)str.toInt(ok+1);
    if(!ok[0] || !ok[1]){
        return;
    }
    this->trW_currentSelectedCourse = id;
    this->trW_currentSelectedCourseStatus = status;
    this->DataBind_TchClassInfo(id, status);
}

void Frm_TchClassManage::on_btn_SaveScore_clicked()
{
    QT_TRY{
        int res = 0;
        int total = ui->tbW_ClassInfo->rowCount();
        for(int i = 0; i < ui->tbW_ClassInfo->rowCount(); i++){
            bool correct = false;
            int stuID = ui->tbW_ClassInfo->item(i, TchClassEnum::StuID)->text().toInt();
            QString score = ui->tbW_ClassInfo->item(i, TchClassEnum::StuScore)->text();
            if(score == ""){
                res += SqlOperation::SetStuScore(this->trW_currentSelectedCourse, stuID, QVariant());
            }
            else{
                score.toInt(&correct);
                if(correct){
                    res += SqlOperation::SetStuScore(this->trW_currentSelectedCourse, stuID, score.toInt());
                }
            }
        }

        QMessageBox::information(this, "提示", QString("共%1条信息，\n已成功录入%2条信息！").arg(total).arg(res));

    }QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }
    this->DataBind_TchClassInfo(this->trW_currentSelectedCourse, this->trW_currentSelectedCourseStatus);
}

void Frm_TchClassManage::on_btn_Exit_clicked()
{
    this->close();
}

void Frm_TchClassManage::on_btn_HeadPortrait_clicked()
{
    tch_info* ti = new tch_info(this->tchID);
    ti->setAttribute(Qt::WA_DeleteOnClose);
    ti->show();
}

