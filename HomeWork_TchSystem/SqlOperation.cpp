#include "SqlOperation.h"
#include <QSqlError>

QSqlDatabase SqlOperation::database = QSqlDatabase::addDatabase("QODBC");

void SqlOperation::InitDatabase(){
    SqlOperation::database.setHostName("127.0.0.1");
    SqlOperation::database.setPort(3306);
    SqlOperation::database.setDatabaseName("uni_edu_db");
    SqlOperation::database.open();
}

void SqlOperation::ClearDatabase(){
    SqlOperation::database.close();
}


//用户数据操作

//new：改用NetID作为登录账号
QSqlQuery SqlOperation::new_Login(const int& NetID, const QString& pwd){
    if(!SqlOperation::database.open()){
        QT_THROW(SqlOperation::database.lastError().text());
    }

    QString selectStr = QString("select id, user_type from user_info where id=%1 and pwd='%2' and status=%3").arg(NetID).arg(pwd).arg(UserEnum::Status::On);
    QSqlQuery query(SqlOperation::database);
    query.exec(selectStr);
    //SqlOperation::database.close();
    return query;
}

//new: 移除了name, gender, age字段，新增NetID字段即登录账号
int SqlOperation::AddUserInfo(int id, const QString& pwd, UserEnum::UserType user_type, UserEnum::Status status){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;

    QSqlQuery query(SqlOperation::database);
    if(query.exec(QString("select id from user_info where id=%1").arg(id)) && query.next()){
        QT_THROW(ERR_HAVE_SAME_ID);
    }else{
        query.prepare("insert into user_info(id, pwd, user_type, status) values(:id, :pwd,  :ut, :status)");

        query.bindValue(":id", id);
        query.bindValue(":pwd", pwd);
        query.bindValue(":ut", user_type);
        query.bindValue(":status", status);

        query.exec();
        res = query.numRowsAffected();
    }

    //SqlOperation::database.close();
    return res;
}

//new: 添加name, gender, age字段
int SqlOperation::AddStuInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, const QString& major, int grade, double GPA){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;

    QSqlQuery query(SqlOperation::database);
    if(query.exec(QString("select id from user_info where id=%1 and status=%2").arg(id).arg(UserEnum::Status::On)) && !query.next()){
        QT_THROW(ERR_HAVE_SAME_ID);
    }else{
        query.prepare("insert into stu_info(stuID, name, gender, age, department, major, grade, GPA) values(:stuID, :name, :gender, :age, :department, :major, :grade, :GPA)");

        query.bindValue(":stuID", id);
        query.bindValue(":name", name);
        query.bindValue(":gender", gender);
        query.bindValue(":age", age);
        query.bindValue(":department", department);
        query.bindValue(":major", major);
        query.bindValue(":grade", grade);
        query.bindValue(":GPA", GPA);

        query.exec();
        res = query.numRowsAffected();
    }

    //SqlOperation::database.close();
    return res;
}

//new: 添加name, gender, age字段
int SqlOperation::AddTchInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, UserEnum::TchPosition position){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;

    QSqlQuery query(SqlOperation::database);
    if(query.exec(QString("select id from user_info where id=%1 and status=%2").arg(id).arg(UserEnum::Status::On)) && !query.next()){
        QT_THROW(ERR_HAVE_SAME_ID);
    }else{
        query.prepare("insert into tch_info(tchID,name, gender, age, department, position) values(:tchID, :name, :gender, :age, :department, :position)");

        query.bindValue(":tchID", id);
        query.bindValue(":name", name);
        query.bindValue(":gender", gender);
        query.bindValue(":age", age);
        query.bindValue(":department", department);
        query.bindValue(":position", position);

        query.exec();
        res = query.numRowsAffected();
    }

    //SqlOperation::database.close();
    return res;
}

int SqlOperation::AddCourseInfo(const QString& name, int tchID, int credit, double period, int stuNum, const QString& address, int year, int term,
                                const QString& introduction, CourseEnum::CourseType courseType,
                                CourseEnum::CourseAssessmentMethod assessmentMethod, CourseEnum::CourseStatus status){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = NullCourseID;
    QSqlQuery query(SqlOperation::database);
    QString str = QString("insert into course_info(name, tchID, credit, period, stuNum, address, year, term, introduction, courseType, assessmentMethod, status) "
                          "values(:name, :tchID, :credit, :period, :stuNum, :address, :year, :term, :introduction, :courseType, :assessmentMethod, :status);");
    query.prepare(str);
    query.bindValue(":name", name);
    query.bindValue(":tchID", tchID);
    query.bindValue(":credit", credit);
    query.bindValue(":period", period);
    query.bindValue(":stuNum", stuNum);
    query.bindValue(":address", address);
    query.bindValue(":year", year);
    query.bindValue(":term", term);
    query.bindValue(":introduction", introduction);
    query.bindValue(":courseType", courseType);
    query.bindValue(":assessmentMethod", assessmentMethod);
    query.bindValue(":status", status);

    query.exec();


    str = QString("select id from course_info "
                  "where name=:name and"
                  " tchID=:tchID and "
                  "credit=:credit and "
                  "period=:period and "
                  "stuNum=:stuNum and "
                  "address=:address and "
                  "year=:year and "
                  "term=:term and "
                  "introduction=:introduction and "
                  "courseType=:courseType and "
                  "assessmentMethod=:assessmentMethod and "
                  "status=:status");
    query.prepare(str);
    query.bindValue(":name", name);
    query.bindValue(":tchID", tchID);
    query.bindValue(":credit", credit);
    query.bindValue(":period", period);
    query.bindValue(":stuNum", stuNum);
    query.bindValue(":address", address);
    query.bindValue(":year", year);
    query.bindValue(":term", term);
    query.bindValue(":introduction", introduction);
    query.bindValue(":courseType", courseType);
    query.bindValue(":assessmentMethod", assessmentMethod);
    query.bindValue(":status", status);

    if(query.exec() && query.next()){
        res = query.value("id").toInt();
    }

    return res;
}

int SqlOperation::AddCourseTimeInfo(int courseID, int week, int whichHalfTerm, const QString& wc){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString str = QString("insert into course_timetable(courseID, week, whichHalfTerm, wc) "
                          "values(:courseID, :week, :whichHalfTerm, :wc)");
    query.prepare(str);
    query.bindValue(":courseID", courseID);
    query.bindValue(":week", week);
    query.bindValue(":whichHalfTerm", whichHalfTerm);
    query.bindValue(":wc", wc);

    query.exec();
    res = query.numRowsAffected();
    return res;
}


//new: 数据库增加了各个表的外键约束“删除行为”：cascade
int SqlOperation::DeleteUserInfo(int uid, bool isLogic){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString str;
    if(isLogic){
        str = QString("update user_info set status=%1 where id=%2").arg(UserEnum::Status::Off).arg(uid);
    }else{
        str = QString("delete from user_info where id=%1").arg(uid);
    }
    int res = query.exec(str);
    return res;
}

int SqlOperation::DeleteCourseInfo(int courseID, bool isLogic){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString str;
    if(isLogic){
        str = QString("update course_info set status=%1 where id=%2").arg(CourseEnum::CourseStatus::Delete).arg(courseID);
    }else{
        query.exec(QString("delete from course_timetable where courseID=%1").arg(courseID));
        str = QString("delete from course_info where id=%1").arg(courseID);
    }
    query.exec(str);
    res = query.numRowsAffected();

    SqlOperation::DeleteCourseTimeInfo(courseID);
    SqlOperation::DeleteCourseSelectionInfo(courseID);
    return res;
}

int SqlOperation::DeleteCourseTimeInfo(int courseID){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    query.exec(QString("delete from course_timetable where courseID=%1").arg(courseID));
    int res = query.numRowsAffected();
    return res;
}

int SqlOperation::DeleteCourseSelectionInfo(int courseID){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    query.exec(QString("delete from course_selection_info where courseID=%1").arg(courseID));
    int res = query.numRowsAffected();
    return res;
}

//new：移除基础信息字段, 增加NetID字段
int SqlOperation::UpdateUserInfo(int id, const QString& pwd, UserEnum::UserType user_type, UserEnum::Status status){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString str = QString("update user_info set pwd=:pwd, user_type=:ut, status=:status where id=%1 and status=%2").arg(id).arg(UserEnum::Status::On);
    query.prepare(str);
    query.bindValue(":pwd", pwd);
    query.bindValue(":ut", user_type);
    query.bindValue(":status", status);

    query.exec();
    res = query.numRowsAffected();
    return res;
}

//new：增加基础信息字段
int SqlOperation::UpdateStuInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, const QString& major, int grade){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString str = QString("select id from user_info where id=%1 and status=%2 and user_type=%3").arg(id).arg(UserEnum::Status::On).arg(UserEnum::UserType::Student);
    if(query.exec(str) && query.next()){
        str = QString("update stu_info set name=:name, gender=:gender, age=:age, department=:department, major=:major, grade=:grade where stuID=%1").arg(id);
        query.prepare(str);
        query.bindValue(":name", name);
        query.bindValue(":gender", gender);
        query.bindValue(":age", age);
        query.bindValue(":department", department);
        query.bindValue(":major", major);
        query.bindValue(":grade", grade);
        query.exec();
        res = query.numRowsAffected();
        return res;
    }
    QT_THROW(ERR_NO_FOUND_USER);
}

//new：增加基础信息字段
int SqlOperation::UpdateTchInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, UserEnum::TchPosition position){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString str = QString("select id from user_info where id=%1 and status=%2 and user_type=%3").arg(id).arg(UserEnum::Status::On).arg(UserEnum::UserType::Teacher);
    if(query.exec(str) && query.next()){
        str = QString("update tch_info set name=:name, gender=:gender, age=:age, department=:department, position=:position where tchID=%1").arg(id);
        query.prepare(str);
        query.bindValue(":name", name);
        query.bindValue(":gender", gender);
        query.bindValue(":age", age);
        query.bindValue(":department", department);
        query.bindValue(":position", position);
        query.exec();
        res = query.numRowsAffected();
        return res;
    }
    QT_THROW(ERR_NO_FOUND_USER);
}

int SqlOperation::UpdateCourseInfo(int id, const QString& name, int tchID, int credit, double period, int stuNum, const QString& address, int year, int term,
                                   const QString& introduction, CourseEnum::CourseType courseType,
                                   CourseEnum::CourseAssessmentMethod assessmentMethod, CourseEnum::CourseStatus status){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = NullCourseID;
    QSqlQuery query(SqlOperation::database);
    QString str = QString("update course_info set "
                          "name=:name, "
                          "tchID=:tchID, "
                          "credit=:credit, "
                          "period=:period, "
                          "stuNum=:stuNum, "
                          "address=:address, "
                          "year=:year, "
                          "term=:term, "
                          "introduction=:introduction, "
                          "courseType=:courseType, "
                          "assessmentMethod=:assessmentMethod, "
                          "status=:status "
                          "where id=%1").arg(id);
    query.prepare(str);
    query.bindValue(":name", name);
    query.bindValue(":tchID", tchID);
    query.bindValue(":credit", credit);
    query.bindValue(":period", period);
    query.bindValue(":stuNum", stuNum);
    query.bindValue(":address", address);
    query.bindValue(":year", year);
    query.bindValue(":term", term);
    query.bindValue(":introduction", introduction);
    query.bindValue(":courseType", courseType);
    query.bindValue(":assessmentMethod", assessmentMethod);
    query.bindValue(":status", status);

    query.exec();
    res = query.numRowsAffected();
    return res;
}

int SqlOperation::UpdateCourseTimeInfo(int courseID, int week, int whichHalfTerm, const QString& wc){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = NullCourseID;
    QSqlQuery query(SqlOperation::database);
    QString str = QString("update course_timetable set "
                          "week=:week, "
                          "whichHalfTerm=:whichHalfTerm, "
                          "wc=:wc, "
                          "where courseID=%1").arg(courseID);
    query.prepare(str);
    query.bindValue(":week", week);
    query.bindValue(":whichHalfTerm", whichHalfTerm);
    query.bindValue(":wc", wc);

    query.exec();
    res = query.numRowsAffected();
    return res;
}

int SqlOperation::SetStuScore(int courseID, int stuID, QVariant score){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString str;
    if(score.isNull()){
        str = QString("update course_selection_info set stuScore=null where "
                "courseID=:courseID and "
                "stuID=:stuID");
    }else{
        int _score = score.toInt();
        if(_score < 0 || _score > 100){
            QT_THROW(QString("成绩小于0或超过100！"));
        }

        str = QString("update course_selection_info set stuScore=%1 where "
                "courseID=:courseID and "
                "stuID=:stuID").arg(score.toInt());
    }
    query.prepare(str);

    query.bindValue(":courseID", courseID);
    query.bindValue(":stuID", stuID);
    qDebug() << query.executedQuery();
    query.exec();
    res = query.numRowsAffected();
    return res;
}

//new：取消了user表的关联
QSqlQuery SqlOperation::SearchStuInfo(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString("select stu_info.* from stu_info, user_info where "
                                "stu_info.stuID = user_info.id and "
                                "user_info.status = %1 and "
                                "stu_info.grade > 0 and "
                                "stu_info.grade < 5").arg(UserEnum::Status::On);
    query.exec(selectStr);
    //SqlOperation::database.close();
    return query;
}

//new：取消了user表的关联
QSqlQuery SqlOperation::SearchTchInfo(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString("select tch_info.* from tch_info, user_info where "
                                "tch_info.tchID = user_info.id and "
                                "user_info.status = %1").arg(UserEnum::Status::On);
    query.exec(selectStr);
    //SqlOperation::database.close();
    return query;
}

QSqlQuery SqlOperation::SearchUserInfo(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString("select * from user_info where user_type>1 and status=%1").arg(UserEnum::Status::On);
    query.exec(selectStr);
    //SqlOperation::database.close();
    return query;
}

QSqlQuery SqlOperation::SearchCourseInfo(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString str = QString("select course_info.*, tch_info.* from course_info, tch_info where course_info.status>%1 and course_info.tchID=tch_info.tchID").arg(CourseEnum::CourseStatus::Delete);

    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::SearchCourseInfo(int year, int term, const QString& courseName, const QString& tchName){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }


    QSqlQuery query(SqlOperation::database);
    QString str = QString("select course_info.*, tch_info.* from course_info, tch_info where "
                          "course_info.status>%1 and "
                          "course_info.tchID=tch_info.tchID and "
                          "year=%2 and "
                          "term=%3 and 1=1 ").arg(CourseEnum::CourseStatus::Delete).arg(year).arg(term);
    if(courseName != ""){
        str += QString(" and course_info.name regexp '%1' ").arg(courseName);

    }
    if(tchName != ""){
        str += QString(" and tch_info.name regexp '%1' ").arg(tchName);
    }

    qDebug() << str;

    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::SearchCourseInfo(int id, IDType type){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }
    QSqlQuery query(SqlOperation::database);
    QString str = "";
    if(type == IDType::TchID){
        str = QString("select course_info.*, tch_info.* from course_info, tch_info where "
                      "course_info.status>%1 and "
                      "tchID=%2 and "
                      "course_info.tchID=tch_info.tchID").arg(CourseEnum::CourseStatus::Delete).arg(id);
    }else if(type == IDType::CourseID){
        str = QString("select course_info.*, tch_info.* from course_info, tch_info where "
                      "course_info.status>%1 and "
                      "course_info.id=%2 and "
                      "course_info.tchID=tch_info.tchID").arg(CourseEnum::CourseStatus::Delete).arg(id);
    }
    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::SearchCourseTimeInfo(int courseID){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }
    QSqlQuery query(SqlOperation::database);
    QString str = "";
    str = QString("select course_timetable.*, course_info.status from course_info, course_timetable where "
                  "course_timetable.courseID=course_info.id and "
                  "course_timetable.courseID=%1 and "
                  "course_info.status>%2").arg(courseID).arg(CourseEnum::CourseStatus::Delete);

    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::SearchCourseList(int tchID){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }
    QSqlQuery query(SqlOperation::database);
    QString str = "";
    str = QString("select course_info.* from course_info where "
                  "course_info.tchID=%1 and "
                  "course_info.status>%2 "
                  "order by course_info.year desc").arg(tchID).arg(CourseEnum::CourseStatus::Delete);

    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::SearchTchClassInfo(int courseID){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString str = QString("select * from course_selection_info where "
                          "courseID=%1 and "
                          "status=%2 "
                          "order by stuID").arg(courseID).arg(UserEnum::CourseSelectionStatus::Selected);
    qDebug() << str;

    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::SearchCourseSelectionInfo(int id, IDType type){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString str;
    if(type == IDType::StuID){
        str = QString("select * from course_selection_info where "
                              "stuID=%1").arg(id);
    }else if(type == IDType::CourseID){
        str = QString("select * from course_selection_info where "
                      "courseID=%1").arg(id);
    }

    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::SearchSelectedCourse(int stuID, int year, int term){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString str = QString("select course_info.*, course_selection_info.status from course_info, course_selection_info where "
                          "year=:year and "
                          "term=:term and "
                          "course_selection_info.stuID=:stuID and "
                          "course_selection_info.status=%1 and "
                          "course_selection_info.courseID=course_info.id").arg(UserEnum::CourseSelectionStatus::Selected);

    query.prepare(str);
    query.bindValue(":year", year);
    query.bindValue(":term", term);
    query.bindValue(":stuID", stuID);
    query.exec();
    return query;
}

QSqlQuery SqlOperation::SearchCourseTimeInfo(int stuID, int year, int term, int halfTerm){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    /*
    select course_timetable.*, course_info.name
                                   from course_timetable,
        course_info
            where id in (select csi.courseID
                   from course_selection_info csi,
               course_info ci,
               course_timetable ct
                   where stuID = :stuID
                         and year = :year
                             and term = :term
                                 and whichHalfTerm = :whichHalfTerm
                                     and csi.status = 2
                                       and csi.courseID = ci.id
                                       and ci.id = ct.courseID)
                and course_timetable.courseID = course_info.id;
    */
    QSqlQuery query(SqlOperation::database);

    QString selectStr = QString("select course_timetable.*, course_info.name "
                                                        "from course_timetable, course_info where "
                                "id in (select csi.courseID from "
                                                            "course_selection_info csi, "
                                                            "course_timetable ct, "
                                                            "course_info ci where "
                                                                                    "stuID = :stuID and "
                                                                                    "ci.year = :year and "
                                                                                    "ci.term = :term and "
                                                                                    "whichHalfTerm = :whichHalfTerm and "
                                                                                    "csi.status = :selectionStatus and "
                                                                                    "csi.courseID = ci.id and "
                                                                                    "(ci.status = :courseStatus1 or "
                                                                                    "ci.status = :courseStatus2) and "
                                                                                    "ci.id = ct.courseID) and "
                                "course_timetable.courseID = course_info.id and "
                                "course_timetable.whichHalfTerm = :whichHalfTerm;");

    query.prepare(selectStr);

    query.bindValue(":stuID", stuID);
    query.bindValue(":year", year);
    query.bindValue(":term", term);
    query.bindValue(":whichHalfTerm", halfTerm);
    query.bindValue(":selectionStatus", UserEnum::CourseSelectionStatus::Selected);
    query.bindValue(":courseStatus1", CourseEnum::CourseStatus::Open);
    query.bindValue(":courseStatus2", CourseEnum::CourseStatus::Close);

    qDebug() << query.executedQuery();

    query.exec();
    return query;
}

QSqlQuery SqlOperation::AddSelectionInfo(int stuID, int courseID){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);

    QString searchStr = QString("select * from course_selection_info where "
                                "stuID=%1 and "
                                "courseID=%2").arg(stuID).arg(courseID);
    query.exec(searchStr);
    QString str;
    if(query.next()){
        str = QString("update course_selection_info "
                                    "set status=%1 where "
                                    "stuID=%2 and "
                                    "courseID=%3").arg(UserEnum::CourseSelectionStatus::Selected).arg(stuID).arg(courseID);
    }else{
        str = QString("insert into course_selection_info(stuID, courseID, status) "
                      "values(%1, %2, %3)").arg(stuID).arg(courseID).arg(UserEnum::CourseSelectionStatus::Selected);
    }
    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::UpdateSelectionInfo(int stuID, int courseID, UserEnum::CourseSelectionStatus status){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);

    QString str = QString("update course_selection_info "
                  "set status=%1 where "
                  "stuID=%2 and "
                  "courseID=%3").arg(status).arg(stuID).arg(courseID);
    query.exec(str);
    return query;
}

QSqlQuery SqlOperation::ProgressQuery(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);

    QString str = QString("select * from progress_table where idx=0");
    query.exec(str);
    return query;
}

void SqlOperation::ProgressUp(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);

    query = SqlOperation::ProgressQuery();
    if(query.next()){
        int curVal = query.value("progress").toInt();
        curVal = (curVal+1)%8;
        int year = query.value("year").toInt();
        int term = query.value("term").toInt();

        SqlOperation::upd_CourseStatusUp(year, term);

        if(curVal == ProgressInfo::PrepareCourse2){
            term = 2;
        }else if(curVal == ProgressInfo::PrepareCourse1){
            term = 1;
            year += 1;
            SqlOperation::upd_YearPlus();
        }

        QString str = QString("update progress_table set "
                              "progress = %1, "
                              "year = %2, "
                              "term = %3 "
                              "where idx=0").arg(curVal).arg(year).arg(term);
        query = QSqlQuery(SqlOperation::database);
        query.exec(str);
        if(query.numRowsAffected() > 0){
            return;
        }
    }
    QT_THROW(QString("Progress Table Update Fail!"));
}

void SqlOperation::ProgressDown(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);

    query = SqlOperation::ProgressQuery();
    if(query.next()){
        int curVal = query.value("progress").toInt();
        curVal = (curVal-1 + 8)%8;
        int year = query.value("year").toInt();
        int term = query.value("term").toInt();

        SqlOperation::upd_CourseStatusDown(year, term);

        if(curVal == ProgressInfo::CourseClosed1){
            term = 1;
        }else if(curVal == ProgressInfo::CourseClosed2){
            term = 2;
            year -= 1;
            SqlOperation::upd_YearMinus();
        }

        QString str = QString("update progress_table set "
                              "progress = %1, "
                              "year = %2, "
                              "term = %3 "
                              "where idx=0").arg(curVal).arg(year).arg(term);
        query = QSqlQuery(SqlOperation::database);
        query.exec(str);
        if(query.numRowsAffected() > 0){
            return;
        }
    }
    QT_THROW(QString("Progress Table Update Failed!"));
}
