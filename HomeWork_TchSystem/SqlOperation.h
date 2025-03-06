#ifndef SQLOPERATION_H
#define SQLOPERATION_H

#include<QSqlDatabase>
#include<QSqlQuery>
#include<vector>

#include"TotalNameDesign.h"

class SqlOperation
{
protected:
    static QSqlDatabase database;
public:
    //SqlOperation();
    static void InitDatabase();
    static void ClearDatabase();

    //返回用户类型
    static QSqlQuery new_Login(const int& NetID, const QString& pwd);

    //增，返回修改行数
    static int AddUserInfo(int id, const QString& pwd, UserEnum::UserType user_type, UserEnum::Status status);
    static int AddStuInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, const QString& major, int grade, double GPA);
    static int AddTchInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, UserEnum::TchPosition position);

        //特例，返回课程编号，没有就返回NullCourseID
    static int AddCourseInfo(const QString& name, int tchID, int credit, double period, int stuNum, const QString& address, int year, int term,
                             const QString& introduction, CourseEnum::CourseType courseType, CourseEnum::CourseAssessmentMethod assessmentMethod, CourseEnum::CourseStatus status);
    static int AddCourseTimeInfo(int courseID, int week, int whichHalfTerm, const QString& wc);

    //删，返回修改行数
    static int DeleteUserInfo(int uid, bool isLogic = true);
    static int DeleteCourseInfo(int courseID, bool isLogic = true);
    static int DeleteCourseTimeInfo(int courseID);
    static int DeleteCourseSelectionInfo(int courseID);

    //改，返回修改行数
    static int UpdateUserInfo(int id, const QString& pwd, UserEnum::UserType user_type, UserEnum::Status status);
    static int UpdateStuInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, const QString& major, int grade);
    static int UpdateTchInfo(int id, QString& name, UserEnum::GenderType gender, int age, const QString& department, UserEnum::TchPosition position);
    static int UpdateCourseInfo(int id, const QString& name, int tchID, int credit, double period, int stuNum, const QString& address, int year, int term,
                                const QString& introduction, CourseEnum::CourseType courseType, CourseEnum::CourseAssessmentMethod assessmentMethod, CourseEnum::CourseStatus status);
    static int UpdateCourseTimeInfo(int courseID, int week, int whichHalfTerm, const QString& wc);
    static int SetStuScore(int courseID, int stuID, QVariant score);

    //查，返回查询到的数据行数
    static QSqlQuery SearchStuInfo();//返回学生表
    static QSqlQuery SearchTchInfo();//返回教师表
    static QSqlQuery SearchUserInfo();//返回用户表
    
    /*---新增---*/
    static QSqlQuery SearchTypUserInfo(int netID);
    static QSqlQuery SearchTypStuInfo(int stuID);//返回某学生的基础信息
    static QSqlQuery SearchTypTchInfo(int tchID);//返回某老师的基础信息
    static QSqlQuery SearchTypAdmInfo(int admID);//返回某管理员的基础信息
    static QSqlQuery SearchTypStuScoreTable(int stuID, int year, int term);//返回某学生成绩表，各科带排名
    /*----------*/

    static QSqlQuery SearchCourseInfo();
    static QSqlQuery SearchCourseInfo(int year, int term, const QString& courseName, const QString& tchName);
    static QSqlQuery SearchCourseInfo(int id, IDType type);

    static QSqlQuery SearchCourseTimeInfo(int courseID);

    static QSqlQuery SearchCourseList(int tchID);

    static QSqlQuery SearchTchClassInfo(int courseID);

    static QSqlQuery SearchCourseSelectionInfo(int id, IDType type);

    static QSqlQuery SearchSelectedCourse(int stuID, int year, int term);

    static QSqlQuery SearchCourseTimeInfo(int stuID, int year, int term, int halfTerm);

    static QSqlQuery AddSelectionInfo(int stuID, int courseID);
    static QSqlQuery UpdateSelectionInfo(int stuID, int courseID, UserEnum::CourseSelectionStatus status);

    static int upd_CourseStatusUp(int year, int term);
    static int upd_CourseStatusDown(int year, int term);
    static int upd_YearPlus();
    static int upd_YearMinus();

    static QSqlQuery DataForCountAvg(int stuID);

    //查看当前时间进展
    static QSqlQuery ProgressQuery();
    static void ProgressUp();
    static void ProgressDown();
};

#endif // SQLOPERATION_H
