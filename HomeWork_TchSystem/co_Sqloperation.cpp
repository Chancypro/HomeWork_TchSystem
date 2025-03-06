#include "SqlOperation.h"

QSqlQuery SqlOperation::SearchTypUserInfo(int netID){
    if (!SqlOperation::database.open())
    {
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString(
                            "select * "
                            "from user_info "
                            "where id = %1").arg(netID);
    //qDebug() << selectStr;
    query.exec(selectStr);

    // SqlOperation::database.close();
    return query;
}

// 返回某学生的基础信息——已知ID
QSqlQuery SqlOperation::SearchTypStuInfo(int stuID)
{
    if (!SqlOperation::database.open())
    {
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString(
        "select * "
        "from stu_info "
        "where stuID = %1 and "
        "grade > 0 and "
        "grade < 5").arg(stuID);
    //qDebug() << selectStr;
    query.exec(selectStr);

    // SqlOperation::database.close();
    return query;
}

// 返回某教师的基础信息——已知ID
QSqlQuery SqlOperation::SearchTypTchInfo(int tchID)
{
    if (!SqlOperation::database.open())
    {
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString(
        "select * "
        "from tch_info "
        "where tchID = %1").arg(tchID);
    query.exec(selectStr);

    // SqlOperation::database.close();
    return query;
}

QSqlQuery SqlOperation::SearchTypAdmInfo(int admID){
    if (!SqlOperation::database.open())
    {
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString(
                            "select * "
                            "from adm_info "
                            "where admID = %1").arg(admID);
    query.exec(selectStr);

    // SqlOperation::database.close();
    return query;
}

/* 返回某教师的基础信息——只知NetID
static QSqlQuery SearchMyInfo(const QString& NetID)
{
    if (!SqlOperation::database.open())
    {
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString(
        "select *"
        "from tch_info"
        "where tchID = (select id from user_info where user_info.NetID = %1 ").arg(id); //标量子查询
        query.exec(selectStr);

    //SqlOperation::database.close();
    return query;
}
*/

// 查询带排名的学生课程成绩表
QSqlQuery SqlOperation::SearchTypStuScoreTable(int stuID, int year, int term)
{
    if (!SqlOperation::database.open())
    {
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    /*"select ci.*, tch_info.name, min(stuScore) 'score', count(csi1.courseID) 'rank' "
      "from course_selection_info csi1, "
            "course_info ci, "
            "course_timetable ct, "
            "tch_info "
        "where csi1.stuScore >= "
              "(select csi2.stuScore "
               "from course_selection_info csi2 "
               "where csi2.stuID = 22330000 "
                 "and csi1.courseID = csi2.courseID) "
          "and ci.id = csi1.courseid "
          "and ci.tchid = tch_info.tchID "
          "and ci.id = ct.courseID "
          "and ci.year = :year "
          "and ci.term = :term "
        "group by csi1.courseID;"
    */

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString("select ci.*, tch_info.name, min(stuScore) 'score', count(csi1.courseID) 'rank' "
                                "from course_selection_info csi1, "
                                        "course_info ci, "
                                        "tch_info "
                                            "where csi1.stuScore >= "
                                                "(select csi2.stuScore "
                                                "from course_selection_info csi2 "
                                                    "where csi2.stuID = :stuID "
                                                        "and csi1.courseID = csi2.courseID) "
                                            "and ci.id = csi1.courseid "
                                            "and ci.tchid = tch_info.tchID "
                                            "and ci.year = :year "
                                            "and ci.term = :term "
                                            "group by csi1.courseID;");
    query.prepare(selectStr);
    query.bindValue(":stuID", stuID);
    query.bindValue(":year", year);
    query.bindValue(":term", term);

    query.exec();
    // SqlOperation::database.close();
    return query;
}


int SqlOperation::upd_CourseStatusUp(int year, int term){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;

    QSqlQuery query(SqlOperation::database);
    QString updstr[3] = {
        QString("update course_info set status = %1 where "
                "status = %2 and year = :year and term = :term;").arg(CourseEnum::CourseStatus::Close).arg(CourseEnum::CourseStatus::Open),

        QString("update course_info set status = %1 where "
                "status = %2 and year = :year and term = :term;").arg(CourseEnum::CourseStatus::Open).arg(CourseEnum::CourseStatus::CanSelect),

        QString("update course_info set status = %1 where "
                "status = %2 and year = :year and term = :term;").arg(CourseEnum::CourseStatus::CanSelect).arg(CourseEnum::CourseStatus::UnOpen),
    };

    for(int i = 0; i < 3; i++){
        query.prepare(updstr[i]);

        query.bindValue(":year", year);
        query.bindValue(":term", term);

        query.exec();

        res += query.numRowsAffected();
    }

    return res;
}

int SqlOperation::upd_CourseStatusDown(int year, int term){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;

    QSqlQuery query(SqlOperation::database);
    QString updstr[3] = {
        QString("update course_info set status = %1 where "
                "status = %2 and year = :year and term = :term;").arg(CourseEnum::CourseStatus::UnOpen).arg(CourseEnum::CourseStatus::CanSelect),

        QString("update course_info set status = %1 where "
                "status = %2 and year = :year and term = :term;").arg(CourseEnum::CourseStatus::CanSelect).arg(CourseEnum::CourseStatus::Open),

        QString("update course_info set status = %1 where "
                "status = %2 and year = :year and term = :term;").arg(CourseEnum::CourseStatus::Open).arg(CourseEnum::CourseStatus::Close),
    };

    for(int i = 0; i < 3; i++){
        query.prepare(updstr[i]);

        query.bindValue(":year", year);
        query.bindValue(":term", term);

        query.exec();

        res += query.numRowsAffected();
    }

    return res;
}

int SqlOperation::upd_YearPlus(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString updstr[3] = {
                         QString("update stu_info set age = age+1, grade = grade+1"),
                         QString("update tch_info set age = age+1"),
                         QString("update adm_info set age = age+1")
                        };

    for(int i = 0; i < 3; i++){
        query.exec(updstr[i]);
        res += query.numRowsAffected();
    }

    return res;
}

int SqlOperation::upd_YearMinus(){
    if(!SqlOperation::database.open()){
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    int res = 0;
    QSqlQuery query(SqlOperation::database);
    QString updstr[3] = {
        QString("update stu_info set age = age-1, grade = grade-1"),
        QString("update tch_info set age = age-1"),
        QString("update adm_info set age = age-1")
    };

    for(int i = 0; i < 3; i++){
        query.exec(updstr[i]);
        res += query.numRowsAffected();
    }

    return res;
}


QSqlQuery SqlOperation::DataForCountAvg(int stuID)
{
    if (!SqlOperation::database.open())
    {
        QT_THROW(ERR_DB_OPEN_FAIL);
    }

    QSqlQuery query(SqlOperation::database);
    QString selectStr = QString("select courseID, ci.credit, csi.stuScore "
                                    "from course_selection_info csi, "
                                    "course_info ci "
                                    "where csi.courseID = ci.id "
                                    "and stuID = :stuID "
                                    "order by courseID;");
    query.prepare(selectStr);
    query.bindValue(":stuID", stuID);
    query.exec();

    // SqlOperation::database.close();
    return query;
}
