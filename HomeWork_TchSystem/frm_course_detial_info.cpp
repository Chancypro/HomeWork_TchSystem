#include "frm_course_detial_info.h"
#include "ui_frm_course_detial_info.h"
#include "stu_info.h"
#include "tch_info.h"
#include <QGraphicsDropShadowEffect>

Frm_CourseDetialInfo::Frm_CourseDetialInfo(int courseID, int netID, QString name, IDType type, int year, int term, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frm_course_detial_info),
    courseID(courseID), netID(netID), name(name), idType(type)
{
    ui->setupUi(this);
    this->beautify();

    ui->lbl_Name->setText(this->name);
    ui->lbl_ID->setText(QString::number(this->netID));

    this->InitCheckBox_TimeSelect();

    //初始化几个ComboBox
    for(int i = 0; i < CourseStatus::CourseStatusCount; i++){
        ui->cbb_courseStatus->addItem(CourseEnum::CourseStatusStr[i]);
    }
    for(int i = 0; i < CourseType::CourseTypeCount; i++){
        ui->cbb_courseType->addItem(CourseEnum::CourseTypeStr[i]);
    }
    for(int i = 0; i < CourseAssessmentMethod::CourseAssessmentMethodCount; i++){
        ui->cbb_courseAssessmentType->addItem(CourseAssessmentMethodStr[i]);
    }
    for(int i = 0; i < HalfTerm::HalfTermCount; i++){
        ui->cbb_HalfTerm->addItem(HalfTermStr[i]);
    }

    ui->spb_Year->setEnabled(false);
    ui->spb_Term->setEnabled(false);
    ui->dspb_coursePeriod->setEnabled(false);

    //初始化上半学期与下半学期的学时
    this->course_period[0] = this->course_period[1] = 0;
    //利用槽机制，将每一个CheckBox关联到学时的更新函数
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            connect(this->cb_TimeSelect[i][j], &QCheckBox::stateChanged, [=]() {
                //qDebug() << this->cb_TimeSelect[i][j]->isChecked();

                //qDebug() << "in slot, now " << i << " " << j << " state is " << this->cb_TimeSelect[i][j]->isChecked();

                int halfTerm = ui->cbb_HalfTerm->currentIndex();
                if(this->cbTimeSelectValue[i][j][halfTerm] == this->cb_TimeSelect[i][j]->isChecked()){
                    return;
                }
                this->cbTimeSelectValue[i][j][halfTerm] = this->cb_TimeSelect[i][j]->isChecked();

                double curPeriod = ui->dspb_coursePeriod->value();

                int direction = this->cb_TimeSelect[i][j]->isChecked() ? 1 : -1;
                int base = j == 5 ? 1 : 2;
                curPeriod += BaseHalfTermPeriod[halfTerm] * base * direction;

                ui->dspb_coursePeriod->setValue(curPeriod);
            });
        }
    }

    //不是添加课程状态
    if(courseID != NullCourseID){
        this->DataBind();

        //仅有在打开该窗口的用户是对应的老师，而且课程处于未开放状态，才能修改课程信息
        if(this->tchID == this->netID && this->courseStatus == CourseStatus::UnOpen){

        }else{
            ui->le_courseName->setReadOnly(true);
            ui->spb_courseCredit->setReadOnly(true);
            ui->le_courseAddress->setReadOnly(true);
            ui->cbb_courseType->setEnabled(false);
            ui->spb_StuNum->setReadOnly(true);
            ui->cbb_courseAssessmentType->setEnabled(false);
            ui->txte_courseIntroduction->setReadOnly(true);
            ui->spb_Year->setReadOnly(true);
            ui->spb_Term->setReadOnly(true);
            ui->btn_Save->hide();

            for(int week = 0; week < 6; week++){
                for(int wc = 0; wc < 6; wc++){
                    this->cb_TimeSelect[week][wc]->setEnabled(false);
                }
            }
        }

    }
    //处于添加课程状态
    else{
        ui->le_tchName->setText(this->name);
        this->tchID = this->netID;
        ui->cbb_courseStatus->setCurrentIndex(CourseStatus::UnOpen);

        ui->spb_Year->setValue(year);
        ui->spb_Term->setValue(term);
    }

}

void Frm_CourseDetialInfo::beautify()
{
    this->setWindowTitle("课程详细信息");
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


    //登录框
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(0, 0);
    ui->widget_6->setGraphicsEffect(shadow);
    ui->widget_7->setGraphicsEffect(shadow);
    ui->widget_18->setGraphicsEffect(shadow);

    //ui->gridLayout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    for (int row = 0; row < ui->gridLayout->rowCount(); ++row) {
        for (int col = 0; col < ui->gridLayout->columnCount(); ++col) {
            QLayoutItem *item = ui->gridLayout->itemAtPosition(row, col);
            if(item)
            {
                QWidget *widget = item->widget();
                if (widget) {
                    ui->gridLayout->setAlignment(widget, Qt::AlignVCenter | Qt::AlignHCenter);

                }
            }
        }
    }
}

Frm_CourseDetialInfo::~Frm_CourseDetialInfo()
{
    delete ui;
}

//利用数组对CheckBox矩阵进行绑定，方便后续操作
void Frm_CourseDetialInfo::InitCheckBox_TimeSelect(){
    this->cb_TimeSelect[0][0] = ui->cb_Mon12;
    this->cb_TimeSelect[0][1] = ui->cb_Mon34;
    this->cb_TimeSelect[0][2] = ui->cb_Mon56;
    this->cb_TimeSelect[0][3] = ui->cb_Mon78;
    this->cb_TimeSelect[0][4] = ui->cb_Mon910;
    this->cb_TimeSelect[0][5] = ui->cb_Mon11;

    this->cb_TimeSelect[1][0] = ui->cb_Tue12;
    this->cb_TimeSelect[1][1] = ui->cb_Tue34;
    this->cb_TimeSelect[1][2] = ui->cb_Tue56;
    this->cb_TimeSelect[1][3] = ui->cb_Tue78;
    this->cb_TimeSelect[1][4] = ui->cb_Tue910;
    this->cb_TimeSelect[1][5] = ui->cb_Tue11;

    this->cb_TimeSelect[2][0] = ui->cb_Wed12;
    this->cb_TimeSelect[2][1] = ui->cb_Wed34;
    this->cb_TimeSelect[2][2] = ui->cb_Wed56;
    this->cb_TimeSelect[2][3] = ui->cb_Wed78;
    this->cb_TimeSelect[2][4] = ui->cb_Wed910;
    this->cb_TimeSelect[2][5] = ui->cb_Wed11;

    this->cb_TimeSelect[3][0] = ui->cb_Thu12;
    this->cb_TimeSelect[3][1] = ui->cb_Thu34;
    this->cb_TimeSelect[3][2] = ui->cb_Thu56;
    this->cb_TimeSelect[3][3] = ui->cb_Thu78;
    this->cb_TimeSelect[3][4] = ui->cb_Thu910;
    this->cb_TimeSelect[3][5] = ui->cb_Thu11;

    this->cb_TimeSelect[4][0] = ui->cb_Fri12;
    this->cb_TimeSelect[4][1] = ui->cb_Fri34;
    this->cb_TimeSelect[4][2] = ui->cb_Fri56;
    this->cb_TimeSelect[4][3] = ui->cb_Fri78;
    this->cb_TimeSelect[4][4] = ui->cb_Fri910;
    this->cb_TimeSelect[4][5] = ui->cb_Fri11;

    this->cb_TimeSelect[5][0] = ui->cb_Sat12;
    this->cb_TimeSelect[5][1] = ui->cb_Sat34;
    this->cb_TimeSelect[5][2] = ui->cb_Sat56;
    this->cb_TimeSelect[5][3] = ui->cb_Sat78;
    this->cb_TimeSelect[5][4] = ui->cb_Sat910;
    this->cb_TimeSelect[5][5] = ui->cb_Sat11;
}

void Frm_CourseDetialInfo::DataBind(){
    QT_TRY{
        QSqlQuery query = SqlOperation::SearchCourseInfo(this->courseID, IDType::CourseID);

        if(query.next()){
            this->tchID = query.value("course_info.tchID").toInt();
            this->courseStatus = (CourseStatus)query.value("course_info.status").toInt();

            ui->le_courseName->setText(query.value("course_info.name").toString());
            ui->le_tchName->setText(query.value("tch_info.name").toString());
            ui->spb_courseCredit->setValue(query.value("course_info.credit").toInt());
            ui->dspb_coursePeriod->setValue(0);
            ui->le_courseAddress->setText(query.value("address").toString());
            ui->cbb_courseType->setCurrentIndex(query.value("courseType").toInt());
            ui->cbb_courseAssessmentType->setCurrentIndex(query.value("assessmentMethod").toInt());
            ui->cbb_courseStatus->setCurrentIndex(query.value("status").toInt());
            ui->txte_courseIntroduction->setText(query.value("introduction").toString());
            ui->spb_StuNum->setValue(query.value("course_info.stuNum").toInt());
            ui->spb_Year->setValue(query.value("year").toInt());
            ui->spb_Term->setValue(query.value("term").toInt());
        }

        query = SqlOperation::SearchCourseTimeInfo(this->courseID);
        while(query.next()){

            int whichHalfTerm = query.value("whichHalfTerm").toInt();
            int week = query.value("week").toInt();
            QString wcList = query.value("wc").toString();
            for(int wc = 0; wc < wcList.length(); wc++){
                //qDebug() << wcList[wc].digitValue();
                this->cbTimeSelectValue[week][wc][whichHalfTerm] = wcList[wc].digitValue();

                int direction = wcList[wc].digitValue();
                double curPeriod = ui->dspb_coursePeriod->value();

                int base = wc == 5 ? 1 : 2;
                curPeriod += BaseHalfTermPeriod[whichHalfTerm] * base * direction;

                ui->dspb_coursePeriod->setValue(curPeriod);
            }
        }
        //刷新checkbox
        ui->cbb_HalfTerm->setCurrentIndex(1);
        ui->cbb_HalfTerm->setCurrentIndex(0);
    }QT_CATCH(QString msg){
        QMessageBox::critical(this, ERR_NOTE, msg);
    }
}

void Frm_CourseDetialInfo::on_cbb_HalfTerm_currentIndexChanged(int index)
{
    for(int week = 0; week < 6; week++){
        for(int wc = 0; wc < 6; wc++){
            bool isCheck = this->cbTimeSelectValue[week][wc][index];
            qDebug() << "before set value";
            this->cb_TimeSelect[week][wc]->setCheckState(isCheck ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
            qDebug() << "after set value";
        }
    }
}

void Frm_CourseDetialInfo::on_btn_Save_clicked()
{
    QString courseName = ui->le_courseName->text();
    int courseCredit = ui->spb_courseCredit->value();
    double coursePeriod = ui->dspb_coursePeriod->value();
    QString courseAddress = ui->le_courseAddress->text();
    CourseType courseType = (CourseType)ui->cbb_courseType->currentIndex();
    int courseStuNum = ui->spb_StuNum->value();
    CourseAssessmentMethod cam = (CourseAssessmentMethod)ui->cbb_courseAssessmentType->currentIndex();
    QString introduction = ui->txte_courseIntroduction->toPlainText();
    CourseStatus courseStatus = (CourseStatus)ui->cbb_courseStatus->currentIndex();
    int year = ui->spb_Year->value();
    int term = ui->spb_Term->value();

    if(courseName == ""){
        QMessageBox::information(this, "提示", "课程名称不能为空！");
        return;
    }
    if(courseAddress == ""){
        QMessageBox::information(this, "提示", "上课地点不能为空！");
        return;
    }
    if(coursePeriod == 0){
        QMessageBox::information(this, "提示", "请设置上课时间！");
        return;
    }

    //处于修改状态
    if(this->courseID != NullCourseID){
        QT_TRY{
            SqlOperation::UpdateCourseInfo(this->courseID, courseName, this->tchID, courseCredit, coursePeriod, courseStuNum, courseAddress, year, term, introduction, courseType, cam, courseStatus);

            bool totalFlag = true;
            SqlOperation::DeleteCourseTimeInfo(this->courseID);
            //修改时间数据
            for(int halfTerm = 0; halfTerm < 2; halfTerm++){
                for(int week = 0; week < 6; week++){
                    QString wc = "";
                    bool flag = false;
                    for(int i = 0; i < 6; i++){
                        if(this->cbTimeSelectValue[week][i][halfTerm]){
                            flag = true;
                            wc += '1';
                        }else{
                            wc += '0';
                        }
                    }
                    //不全为0才添加数据
                    if(flag){
                        if(SqlOperation::AddCourseTimeInfo(this->courseID, week, halfTerm, wc) <= 0){
                            totalFlag = false;
                        }
                    }

                }
            }
            //修改成功后
            if(totalFlag){
                QMessageBox::information(this, "提示", "修改成功！");
                emit DataChanged();
            }else{
                QMessageBox::information(this, "提示", "修改失败！");
            }
        }
        QT_CATCH(QString msg){
            QMessageBox::critical(this, ERR_NOTE, msg);
        }
    }
    //处于添加状态
    else{
        QT_TRY{
            this->courseID = SqlOperation::AddCourseInfo(courseName, this->tchID, courseCredit, coursePeriod, courseStuNum, courseAddress, year, term, introduction, courseType, cam, courseStatus);

            //添加成功后
            if(this->courseID != NullCourseID){
                bool totalFlag = true;
                //添加时间数据
                for(int halfTerm = 0; halfTerm < 2; halfTerm++){
                    for(int week = 0; week < 6; week++){
                        QString wc = "";
                        bool flag = false;
                        for(int i = 0; i < 6; i++){
                            if(this->cbTimeSelectValue[week][i][halfTerm]){
                                flag = true;
                                wc += '1';
                            }else{
                                wc += '0';
                            }
                        }
                        //不全为0才添加数据
                        if(flag){
                            if(SqlOperation::AddCourseTimeInfo(this->courseID, week, halfTerm, wc) <= 0){
                                totalFlag = false;
                            }
                        }

                    }
                }
                if(totalFlag){
                    QMessageBox::information(this, "提示", "添加成功！");
                    emit DataChanged();
                }else{
                    QMessageBox::information(this, "提示", "添加失败！");
                    //删除已添加的数据
                    SqlOperation::DeleteCourseInfo(this->courseID);
                    this->courseID = NullCourseID;
                }
            }else{
                QMessageBox::information(this, "提示", "添加失败！");
            }
        }
        QT_CATCH(QString msg){
            QMessageBox::critical(this, ERR_NOTE, msg);
            SqlOperation::DeleteCourseInfo(this->courseID);
            this->courseID = NullCourseID;
        }

    }

}

void Frm_CourseDetialInfo::on_btn_Exit_clicked()
{
    this->close();
}

void Frm_CourseDetialInfo::on_btn_HeadPortrait_clicked()
{
    if(this->idType == IDType::TchID){
        tch_info* ti = new tch_info(this->netID);
        ti->setAttribute(Qt::WA_DeleteOnClose);
        ti->show();
    }else{
        stu_info* si = new stu_info(this->netID);
        si->setAttribute(Qt::WA_DeleteOnClose);
        si->show();
    }
}

