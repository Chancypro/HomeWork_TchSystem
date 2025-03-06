#include "frm_stu_pick_class.h"
#include "ui_frm_stu_pick_class.h"
#include "stu_info.h"
#include <QSplitter>
#include <qpixmap.h>
Frm_StuPickClass::Frm_StuPickClass(int stuID, QString stuName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm_stu_pick_class),
    stuID(stuID), stuName(stuName)
{
    ui->setupUi(this);
    this->beautify();
    QSqlQuery query = SqlOperation::ProgressQuery();
    query.next();
    this->curSelectedYear = query.value("year").toInt();
    this->curSelectedTerm = query.value("term").toInt();

    this->InitCourseInfo();
    this->InitSelectedCourseInfo();
    this->InitYearTerm();

    ui->lbl_StuID->setText(QString::number(this->stuID));
    ui->lbl_StuName->setText(this->stuName);
}

void Frm_StuPickClass::beautify(){
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

    //查询栏
    QPixmap m(":/new/stu1/search24.png");
    ui->btn_Search->setIcon(QIcon(m));
    ui->btn_Search->setIconSize(m.size());
    ui->btn_Search->setText("查询");
    //ui->pushButton_2->setFixedSize(m.size());

    //treewidget
    // 创建一个QTreeWidgetItem项
    //QTreeWidgetItem *item1 = new QTreeWidgetItem();
    //item1->setText(0, "Item 1");
    //QTreeWidgetItem *item2 = new QTreeWidgetItem();
    //item2->setText(0, "Item 2");

    // 将项添加为根项
    //ui->trw_YearTerm->addTopLevelItem(item1);
    //ui->trw_YearTerm->addTopLevelItem(item2);
    //美化
    ui->trw_YearTerm->header()->setStyleSheet("QHeaderView::section{"
                                            "border-top-right-radius:5px;"
                                            "border-top-left-radius:5px;"
                                            "background-color:rgb(91, 155, 213);"
                                            "height:20px;"
                                            "border:5px solid rgb(91, 155, 213);}");
    //表格
    ui->tbw_CourseInfo->setAlternatingRowColors(true);
    QHeaderView *head = ui->tbw_CourseInfo->horizontalHeader();
    head->setFixedHeight(30);
    // 设置表头背景颜色和边框
    head->setStyleSheet("QHeaderView::section {"
                        "    background-color: #5b9bd5;"  // 设置表头背景颜色
                        "    border:solid rgb(210, 211, 255);"  // 设置表头边框宽度和颜色
                        "}");

    //listview
    ui->lw_SelectedCourseInfo->setStyleSheet("QListWidget::item {"
                                  "height: 25px;"
                                  "}");
    ui->lw_SelectedCourseInfo->setStyleSheet("QListView::item:hover {"
                                  "padding: 10px;"
                                  "border-left: 3px solid rgb(91, 155, 213);"
                                  "}");
}

void Frm_StuPickClass::InitCourseInfo(){
    ui->tbw_CourseInfo->setColumnCount(CourseInfoList::CourseInfoListCount);
    ui->tbw_CourseInfo->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    for(int i = 0; i < CourseInfoList::CourseInfoListCount; i++){
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(CourseInfoListStr[i]);
        ui->tbw_CourseInfo->setHorizontalHeaderItem(i, item);
        ui->tbw_CourseInfo->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }
    this->DataBind_CourseInfo(this->curSelectedYear, this->curSelectedTerm, ui->le_CourseName->text());
}

void Frm_StuPickClass::InitSelectedCourseInfo(){
    this->DataBind_SelectedCourseInfo(this->curSelectedYear, this->curSelectedTerm);
}

void Frm_StuPickClass::InitYearTerm(){
    int beginYear = 2025;
    int endYear = 2019;

    for(int i = beginYear; i >= endYear; i--){
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, QString::number(i));

        QTreeWidgetItem* term1 = new QTreeWidgetItem;
        QTreeWidgetItem* term2 = new QTreeWidgetItem;
        term1->setText(0, "第一学期");
        term1->setText(1, "1");

        term2->setText(0, "第二学期");
        term2->setText(1, "2");

        item->addChild(term1);
        item->addChild(term2);

        ui->trw_YearTerm->addTopLevelItem(item);
    }
}

void Frm_StuPickClass::DataBind_CourseInfo(int year, int term, const QString& courseName){
    ui->tbw_CourseInfo->setRowCount(0);

    unordered_map<int, int> courseIndex;

    QSqlQuery query = SqlOperation::SearchCourseInfo(year, term, courseName, "");
    while(query.next()){
        int curRow = ui->tbw_CourseInfo->rowCount();
        ui->tbw_CourseInfo->insertRow(curRow);

        int courseID = query.value("course_info.id").toInt();

        courseIndex.insert(std::make_pair(courseID, curRow));

        QTableWidgetItem* item_CourseID = new QTableWidgetItem;
        item_CourseID->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_CourseName = new QTableWidgetItem;
        item_CourseName->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_TchName = new QTableWidgetItem;
        item_TchName->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_CourseCredit = new QTableWidgetItem;
        item_CourseCredit->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_CourseAddress = new QTableWidgetItem;
        item_CourseAddress->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_CourseType = new QTableWidgetItem;
        item_CourseType->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_StuNum = new QTableWidgetItem;
        item_StuNum->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_CourseAssessmentMethod = new QTableWidgetItem;
        item_CourseAssessmentMethod->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        QTableWidgetItem* item_SelectionState = new QTableWidgetItem;
        item_SelectionState->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

        item_CourseID->setText(query.value("course_info.id").toString());
        item_CourseName->setText(query.value("course_info.name").toString());
        item_TchName->setText(query.value("tch_info.name").toString());
        item_CourseCredit->setText(query.value("credit").toString());
        item_CourseAddress->setText(query.value("address").toString());

        int courseType = query.value("courseType").toInt();
        item_CourseType->setText(CourseEnum::CourseTypeStr[courseType]);

        item_StuNum->setText(query.value("stuNum").toString());

        int assessmentMethod = query.value("assessmentMethod").toInt();
        item_CourseAssessmentMethod->setText(CourseEnum::CourseAssessmentMethodStr[assessmentMethod]);

        //如果不是处于开放状态，课程一律不可选，否则先默认置为未选
        CourseEnum::CourseStatus courseStatus = (CourseEnum::CourseStatus)query.value("status").toInt();
        qDebug() << courseStatus;
        if(courseStatus != CourseEnum::CourseStatus::CanSelect){
            item_SelectionState->setText(UserEnum::CourseCourseSelectionStatusStr[UserEnum::CourseSelectionStatus::CanNotSelect]);
        }else{
            item_SelectionState->setText(UserEnum::CourseCourseSelectionStatusStr[UserEnum::CourseSelectionStatus::NotSelect]);
        }

        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::CourseID, item_CourseID);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::CourseName, item_CourseName);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::TchName, item_TchName);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::CourseCredit, item_CourseCredit);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::CourseAddress, item_CourseAddress);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::CourseType, item_CourseType);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::StuNum, item_StuNum);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::CourseAssessmentMethod, item_CourseAssessmentMethod);
        ui->tbw_CourseInfo->setItem(curRow, CourseInfoList::SelectionState, item_SelectionState);

    }

    //设置选课人数
    for(int i = 0; i < ui->tbw_CourseInfo->rowCount(); i++){
        int courseID = ui->tbw_CourseInfo->item(i, CourseInfoList::CourseID)->text().toInt();
        int totalNum = ui->tbw_CourseInfo->item(i, CourseInfoList::StuNum)->text().toInt();

        query = SqlOperation::SearchTchClassInfo(courseID);
        int selectedNum = 0;
        while(query.next()){
            selectedNum++;
        }

        QString str = QString("%1/%2").arg(selectedNum).arg(totalNum-selectedNum);
        ui->tbw_CourseInfo->item(i, CourseInfoList::StuNum)->setText(str);
    }

    //查找学生所有选过的课程
    query = SqlOperation::SearchCourseSelectionInfo(this->stuID, IDType::StuID);
    while(query.next()){
        int courseID = query.value("courseID").toInt();

        //查找是否在列表上展示了该课程
        unordered_map<int, int>::const_iterator it = courseIndex.find(courseID);
        if(it != courseIndex.end() && query.value("status").toInt() == UserEnum::CourseSelectionStatus::Selected){
            ui->tbw_CourseInfo->item(it->second, CourseInfoList::SelectionState)->setText(UserEnum::CourseCourseSelectionStatusStr[UserEnum::CourseSelectionStatus::Selected]);

        }
    }
}

void Frm_StuPickClass::DataBind_SelectedCourseInfo(int year, int term){
    ui->lw_SelectedCourseInfo->clear();
    this->tbwIdxToSelectedCourseID.clear();

    QListWidgetItem* item = new QListWidgetItem;
    //item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
    item->setFlags(Qt::ItemFlag::ItemIsSelectable);

    QSqlQuery query = SqlOperation::SearchSelectedCourse(this->stuID, year, term);
    while(query.next()){
        int courseID = query.value("course_info.id").toInt();
        //届时方便下标索引课程编号
        this->tbwIdxToSelectedCourseID.push_back(courseID);
        ui->lw_SelectedCourseInfo->addItem("  " + query.value("course_info.name").toString());
    }
}

Frm_StuPickClass::~Frm_StuPickClass()
{
    delete ui;
}

void Frm_StuPickClass::on_trw_YearTerm_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0){
        this->curSelectedYear = item->parent()->text(0).toInt();
        this->curSelectedTerm = item->text(1).toInt();

        this->DataBind_CourseInfo(this->curSelectedYear, this->curSelectedTerm, ui->le_CourseName->text());
        this->DataBind_SelectedCourseInfo(this->curSelectedYear, this->curSelectedTerm);
    }
}

void Frm_StuPickClass::on_btn_Exit_clicked()
{
    this->close();
}


void Frm_StuPickClass::on_tbw_CourseInfo_itemDoubleClicked(QTableWidgetItem *item)
{
    int curRow = ui->tbw_CourseInfo->currentRow();
    int courseID = ui->tbw_CourseInfo->item(curRow, CourseInfoList::CourseID)->text().toInt();

    Frm_CourseDetialInfo* dtl = new Frm_CourseDetialInfo(courseID, this->stuID, this->stuName, IDType::StuID);
    dtl->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    dtl->show();
}


void Frm_StuPickClass::on_lw_SelectedCourseInfo_itemDoubleClicked(QListWidgetItem *item)
{
    int curRow = ui->lw_SelectedCourseInfo->currentRow();
    int courseID = this->tbwIdxToSelectedCourseID[curRow];
    Frm_CourseDetialInfo* dtl = new Frm_CourseDetialInfo(courseID, this->stuID, this->stuName, IDType::StuID);
    dtl->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);

    dtl->show();
}

void Frm_StuPickClass::on_btn_Cancel_clicked()
{

    if(ui->tbw_CourseInfo->currentRow() >= 0){
        int row = ui->tbw_CourseInfo->currentRow();
        QString selectStatus = ui->tbw_CourseInfo->item(row, CourseInfoList::SelectionState)->text();
        if(selectStatus == UserEnum::CourseCourseSelectionStatusStr[UserEnum::Selected]){

            int courseID = ui->tbw_CourseInfo->item(row, CourseInfoList::CourseID)->text().toInt();
            QSqlQuery query = SqlOperation::SearchCourseInfo(courseID, IDType::CourseID);
            query.next();

            if(query.value("status").toInt() == (int)CourseEnum::CourseStatus::CanSelect){
                query = SqlOperation::UpdateSelectionInfo(this->stuID, courseID, UserEnum::NotSelect);
                if(query.numRowsAffected() > 0){
                    QMessageBox::information(this, "提示", QString("已成功取消选择课程《%1》！").arg(ui->tbw_CourseInfo->item(row, CourseInfoList::CourseName)->text()));
                }else{
                    QMessageBox::information(this, "提示", "取消选课失败！");
                }
            }else{
                QMessageBox::information(this, "提示", "该课程已无法取消！");
            }
            this->DataBind_CourseInfo(this->curSelectedYear, this->curSelectedTerm, "");
            this->DataBind_SelectedCourseInfo(this->curSelectedYear, this->curSelectedTerm);

        }
    }
}


void Frm_StuPickClass::on_btn_Select_clicked()
{
    QSqlQuery query = SqlOperation::ProgressQuery();
    query.next();
    int progress = query.value("progress").toInt();
    if(progress != ProgressInfo::SelectCourse1 && progress != ProgressInfo::SelectCourse2){
        QMessageBox::information(this, "提示", "选课时间已结束，已无法选课！");
        return;
    }

    if(ui->tbw_CourseInfo->currentRow() >= 0){
        int row = ui->tbw_CourseInfo->currentRow();
        QString selectStatus = ui->tbw_CourseInfo->item(row, CourseInfoList::SelectionState)->text();
        if(selectStatus == UserEnum::CourseCourseSelectionStatusStr[UserEnum::NotSelect]){

            QString surplus = ui->tbw_CourseInfo->item(row, CourseInfoList::StuNum)->text();
            QStringList sl = surplus.split('/');
            if(sl[1] == "0"){
                QMessageBox::information(this, "提示", "选课人数已满，该课程已无法选择！");
                return;
            }

            int courseID = ui->tbw_CourseInfo->item(row, CourseInfoList::CourseID)->text().toInt();
            QSqlQuery query = SqlOperation::AddSelectionInfo(this->stuID, courseID);
            if(query.numRowsAffected() > 0){
                QMessageBox::information(this, "提示", QString("已成功选择课程《%1》！").arg(ui->tbw_CourseInfo->item(row, CourseInfoList::CourseName)->text()));
            }else{
                QMessageBox::information(this, "提示", "选课失败！");
            }
        }else if(selectStatus == UserEnum::CourseCourseSelectionStatusStr[UserEnum::Selected]){
            QMessageBox::information(this, "提示", "已选择该课程！");
        }else if(selectStatus == UserEnum::CourseCourseSelectionStatusStr[UserEnum::CanNotSelect]){
            QMessageBox::information(this, "提示", "该课程已无法选择！");
        }
        DataBind_CourseInfo(this->curSelectedYear, this->curSelectedTerm, "");
        DataBind_SelectedCourseInfo(this->curSelectedYear, this->curSelectedTerm);
    }
}


void Frm_StuPickClass::on_le_CourseName_textChanged(const QString &arg1)
{
    this->DataBind_CourseInfo(this->curSelectedYear, this->curSelectedTerm, ui->le_CourseName->text());
}


void Frm_StuPickClass::on_btn_HeadPortrait_clicked()
{
    stu_info* si = new stu_info(this->stuID);
    si->setAttribute(Qt::WA_DeleteOnClose);
    si->show();
}

