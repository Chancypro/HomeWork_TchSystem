#include "frm_stu_my_class.h"
#include "qgraphicseffect.h"
#include "ui_frm_stu_my_class.h"
#include "stu_info.h"

Frm_StuMyClass::Frm_StuMyClass(int stuID, QString stuName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm_stu_my_class),
    stuID(stuID), stuName(stuName)
{
    ui->setupUi(this);
    this->beautify();
    //初始化姓名学号
    ui->lbl_StuID->setText(QString::number(this->stuID));
    ui->lbl_StuID2->setText(QString::number(this->stuID));
    ui->lbl_StuName->setText(this->stuName);
    ui->lbl_StuName2->setText(this->stuName);
    //下拉框初始化
    ui->cbb_HalfTerm->addItem("上半学期");
    ui->cbb_HalfTerm->addItem("下半学期");
    ui->cbb_Term->addItem("第一学期");
    ui->cbb_Term->addItem("第二学期");

    this->InitCourseTimeInfo();

    QSqlQuery query = SqlOperation::ProgressQuery();
    query.next();
    int year = query.value("year").toInt();
    int term = query.value("term").toInt();
    qDebug() << year << term;
    ui->spb_Year->setValue(year);
    ui->cbb_Term->setCurrentIndex(term-1);
}

void Frm_StuMyClass::beautify(){
    //美化
    //顶部栏
    ui->widget_4->setStyleSheet("background-color:#138dff;");
    //label
    QPixmap p(":/new/stu1/bkjw.jpg");
    ui->jwTitle_2->setPixmap(p);
    ui->jwTitle_2->setScaledContents(true);

    //按钮
    QPixmap i(":/new/stu1/user48.png");
    ui->btn_HeadPortriat->setIcon(i);
    ui->btn_HeadPortriat->setIconSize(i.size());
    QPixmap x(":/new/stu1/exit48.png");
    ui->btn_Exit->setIcon(QIcon(x));
    ui->btn_Exit->setIconSize(x.size());
    //表格
    ui->tbw_ScoreInfo->setAlternatingRowColors(true);
    QHeaderView *head = ui->tbw_ScoreInfo->horizontalHeader();
    head->setFixedHeight(30);
    // 设置表头背景颜色和边框
    head->setStyleSheet("QHeaderView::section {"
                        "    background-color: #5b9bd5;"  // 设置表头背景颜色
                        "    border:solid rgb(210, 211, 255);"  // 设置表头边框宽度和颜色
                        "}");
    //白色框阴影效果
   QGraphicsDropShadowEffect *shadow1 = new QGraphicsDropShadowEffect;
    shadow1->setBlurRadius(10);
    shadow1->setColor(QColor(0, 0, 0, 80));
    shadow1->setOffset(0, 0);
    ui->widget_1->setGraphicsEffect(shadow1);

//    //表格
//    ui->tbw_ScoreInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
//    ui->tbw_ScoreInfo->setColumnWidth(3,70);
//    //上面两行根据情况改
//    for(int i=0;i<8;i++)
//    {
//        if(i!=3)
//        {
//            ui->tbw_ScoreInfo->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
//        }

//    }

    //管理端两个子窗口取消锁窗口+设置最小宽度

}

void Frm_StuMyClass::InsertTableItems(void)
{
    //填充前需要new QTableWidgetItem
    //需要setTextAlignment(Qt::AlignCenter)
    for(int i=0; i < 11; i++)
    {
        int curRow = ui->tbw_ScoreInfo->rowCount();
        ui->tbw_ScoreInfo->insertRow(curRow);
        QTableWidgetItem *item = new QTableWidgetItem(QString("第 %1 节").arg(curRow+1));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tbw_ScoreInfo->setItem(curRow,0,item);
        ui->tbw_ScoreInfo->verticalHeader()->setSectionResizeMode(curRow,QHeaderView::Stretch);

        for(int column = 0; column < 7; column++){
            QTableWidgetItem* _item = new QTableWidgetItem;
            _item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);

            //_item->setText("test");
            ui->tbw_ScoreInfo->setItem(curRow, column+1, _item);

            this->CourseID[i][column] = -1;
        }
    }
}

Frm_StuMyClass::~Frm_StuMyClass()
{
    delete ui;
}

void Frm_StuMyClass::InitCourseTimeInfo(){
    ui->tbw_ScoreInfo->setColumnCount(8);
    QStringList header;
    header<<"节次"<<"星期日"<<"星期一"<<"星期二"<<"星期三"<<"星期四"<<"星期五"<<"星期六";
    ui->tbw_ScoreInfo->setHorizontalHeaderLabels(header);
    ui->tbw_ScoreInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tbw_ScoreInfo->setColumnWidth(0,70);
    for(int i=1;i<8;i++)
    {
        ui->tbw_ScoreInfo->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    ui->tbw_ScoreInfo->verticalHeader()->setVisible(false);
    ui->tbw_ScoreInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->DataBind_CourseTimeInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->cbb_HalfTerm->currentIndex());
}

void Frm_StuMyClass::DataBind_CourseTimeInfo(int year, int term, int halfTerm){
    ui->tbw_ScoreInfo->setRowCount(0);
    this->InsertTableItems();

    QSqlQuery query = SqlOperation::SearchCourseTimeInfo(this->stuID, year, term, halfTerm);
    while(query.next()){
        int week = query.value("week").toInt();
        QString str = query.value("wc").toString();
        for(int i = 0; i < str.length(); i++){
            if(str[i] == '1'){
                int row = i*2;
                ui->tbw_ScoreInfo->item(row + ClassOffset, week + WeekOffset)->setText(query.value("course_info.name").toString());
                this->CourseID[row][week+1] = query.value("courseID").toInt();
                if(row + 1 <12){
                    ui->tbw_ScoreInfo->item(row + 1 + ClassOffset, week + WeekOffset)->setText(query.value("course_info.name").toString());
                    this->CourseID[row+1][week+1] = query.value("courseID").toInt();
                }
            }
        }
    }
}

void Frm_StuMyClass::on_btn_Exit_clicked()
{
    this->close();
}

void Frm_StuMyClass::on_spb_Year_textChanged(const QString &arg1)
{
    this->DataBind_CourseTimeInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->cbb_HalfTerm->currentIndex());
}

void Frm_StuMyClass::on_cbb_HalfTerm_currentIndexChanged(int index)
{
    this->DataBind_CourseTimeInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->cbb_HalfTerm->currentIndex());
}


void Frm_StuMyClass::on_cbb_Term_currentIndexChanged(int index)
{
    this->DataBind_CourseTimeInfo(ui->spb_Year->value(), ui->cbb_Term->currentIndex()+1, ui->cbb_HalfTerm->currentIndex());
}


void Frm_StuMyClass::on_tbw_ScoreInfo_itemDoubleClicked(QTableWidgetItem *item)
{
    int column = ui->tbw_ScoreInfo->currentColumn();
    int row = ui->tbw_ScoreInfo->currentRow();

    if(row < 0 || column < 1){
        return;
    }
    int courseID = this->CourseID[row][column-1];
    qDebug() << QString("%1 %2 %3").arg(row).arg(column).arg(courseID);
    if(courseID != -1){
        Frm_CourseDetialInfo* dtl = new Frm_CourseDetialInfo(courseID, this->stuID, this->stuName, IDType::StuID);
        dtl->setAttribute(Qt::WA_DeleteOnClose);
        dtl->show();
    }

}


void Frm_StuMyClass::on_btn_HeadPortriat_clicked()
{
    stu_info* si = new stu_info(this->stuID);
    si->setAttribute(Qt::WA_DeleteOnClose);
    si->show();
}

