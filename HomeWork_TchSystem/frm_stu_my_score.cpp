#include "frm_stu_my_score.h"
#include "ui_frm_stu_my_score.h"
#include "stu_info.h"
Frm_StuMyScore::Frm_StuMyScore(int stuID, QString stuName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm_stu_my_score),
    stuID(stuID), stuName(stuName)
{
    ui->setupUi(this);
    this->beautify();

    ui->lbl_StuID->setText(QString::number(this->stuID));
    ui->lbl_StuName->setText(this->stuName);

    this->InitScoreTableInfo();
    this->InitYearTermInfo();
    this->InitCreditGPA();

}

void Frm_StuMyScore::beautify(){
    //美化
    //顶部栏
    ui->widget_4->setStyleSheet("background-color:#138dff;");
    //label
    QPixmap p(":/new/stu1/bkjw.jpg");
    ui->jwTitle_2->setPixmap(p);
    ui->jwTitle_2->setScaledContents(true);
    //表格
    ui->tbw_ScoreTable->setAlternatingRowColors(true);
    QHeaderView *head = ui->tbw_ScoreTable->horizontalHeader();
    head->setFixedHeight(30);
    //按钮
    QPixmap i(":/new/stu1/user48.png");
    ui->btn_HeadPortrait->setIcon(i);
    ui->btn_HeadPortrait->setIconSize(i.size());
    QPixmap x(":/new/stu1/exit48.png");
    ui->btn_Exit->setIcon(QIcon(x));
    ui->btn_Exit->setIconSize(x.size());
    // 设置表头背景颜色和边框
    head->setStyleSheet("QHeaderView::section {"
                        "    background-color: #5b9bd5;"  // 设置表头背景颜色
                        "    border:solid rgb(210, 211, 255);"  // 设置表头边框宽度和颜色
                        "}");

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
}

void Frm_StuMyScore::InitCreditGPA(){
    QSqlQuery query = SqlOperation::DataForCountAvg(this->stuID);
    int totalCredit = 0;
    double avgGPA = 0;
    while(query.next()){
        int credit = query.value("credit").toInt();
        int score = query.value("stuScore").toInt();
        if(score >= 60){
            totalCredit += credit;
            avgGPA += credit * (score-50.0) / 10.0;
        }
    }
    if(totalCredit != 0){
        avgGPA /= totalCredit;
    }

    ui->lbl_Credit->setText(QString::number(totalCredit));
    ui->lbl_AverageGPA->setText(QString::number(avgGPA, 'f', 2));
}

void Frm_StuMyScore::InitScoreTableInfo(){
    ui->tbw_ScoreTable->setColumnCount(ScoreInfoListCount);
    QStringList header;
    for(int i = 0; i < ScoreInfoListCount; i++){
        header << ScoreInfoListStr[i];
    }
    ui->tbw_ScoreTable->setHorizontalHeaderLabels(header);
    //ui->tbw_ScoreTable->setColumnWidth(0,70);
    for(int i=0;i<ScoreInfoListCount;i++)
    {
        ui->tbw_ScoreTable->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    ui->tbw_ScoreTable->verticalHeader()->setVisible(false);
    ui->tbw_ScoreTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->DataBind_ScoreInfo(2023,1);
}

void Frm_StuMyScore::InitYearTermInfo(){
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

void Frm_StuMyScore::DataBind_ScoreInfo(int year, int term){
    ui->tbw_ScoreTable->setRowCount(0);

    QSqlQuery query = SqlOperation::SearchTypStuScoreTable(this->stuID, year, term);
    while(query.next()){
        int curRow = ui->tbw_ScoreTable->rowCount();
        ui->tbw_ScoreTable->insertRow(curRow);

        QTableWidgetItem* item[ScoreInfoListCount];
        for(int i = 0; i < ScoreInfoListCount; i++){
            item[i] = new QTableWidgetItem;
            item[i]->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
            ui->tbw_ScoreTable->setItem(curRow, i, item[i]);
        }

        item[ScoreInfoList::SerialNum]->setText(QString("%1").arg(curRow+1));
        item[ScoreInfoList::CourseType]->setText(CourseEnum::CourseTypeStr[query.value("course_info.courseType").toInt()]);
        item[ScoreInfoList::CourseName]->setText(query.value("course_info.name").toString());
        item[ScoreInfoList::TchName]->setText(query.value("tch_info.name").toString());
        item[ScoreInfoList::Credit]->setText(query.value("course_info.credit").toString());

        QVariant score = query.value("score");
        if(score.isNull()){
            item[ScoreInfoList::Score]->setText("N/A");
        }else{
            item[ScoreInfoList::Score]->setText(score.toString());
            if(score.toInt() < 60){
                item[ScoreInfoList::IsPass]->setText("否");
                item[ScoreInfoList::GPA]->setText("0");
            }else{
                item[ScoreInfoList::GPA]->setText(QString::number((score.toDouble()-50.0)/10.0, 'f', 2));
                item[ScoreInfoList::IsPass]->setText("是");
            }

        }

        item[ScoreInfoList::Rank]->setText(query.value("rank").toString());
    }
}

Frm_StuMyScore::~Frm_StuMyScore()
{
    delete ui;
}

void Frm_StuMyScore::on_btn_Exit_clicked()
{
    this->close();
}

void Frm_StuMyScore::on_trw_YearTerm_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount() == 0){
        int year = item->parent()->text(0).toInt();
        int term = item->text(1).toInt();

        this->DataBind_ScoreInfo(year, term);
    }
}


void Frm_StuMyScore::on_btn_HeadPortrait_clicked()
{
    stu_info* si = new stu_info(this->stuID);
    si->setAttribute(Qt::WA_DeleteOnClose);
    si->show();
}

