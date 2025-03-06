#ifndef TOTALNAMEDESIGN_H
#define TOTALNAMEDESIGN_H

#include<QString>

#define ERR_NOTE QString("错误提示")
#define ERR_DB_OPEN_FAIL QString("DataBase Open Fail!")
#define ERR_HAVE_SAME_ID QString("Have Same ID!")
#define ERR_NO_FOUND_USER QString("User No Found!")

#define DELETE_INFO_NOTE QString("删除提示")

#define NullCourseID -1

namespace UserEnum{
enum UserType: int{
    UnDefined,
    Admin,
    Teacher,
    Student
};

enum GenderType: int{
    Male,
    Female,
    GenderTypeCount
};
const QString GenderTypeStr[GenderTypeCount] = {
    "男",
    "女"
    };

enum Status: bool{
    On,
    Off
};

enum TchPosition: int{
    //讲师
    Lecture = 1,
    //副教授
    AssociateProfessor,
    //教授
    Professor,
    //特聘教授
    SpecialTermProfessor,
    //终身教授
    TenuredProfessor,

    TchPositionCount
};
const QString TchPositionStr[UserEnum::TchPositionCount]{
         "讲师",
         "副教授",
         "教授",
         "特聘教授",
         "终身教授"
    };

enum CourseSelectionStatus: int{
    CanNotSelect,
    NotSelect,
    Selected,
    CourseSelectionStatusCount
};
const QString CourseCourseSelectionStatusStr[CourseSelectionStatusCount] = {
    "不可选",
    "未选",
    "已选"
};
}

namespace CourseEnum{


enum CourseType: int{
    //专选
    MajorSelective,
    //专必
    MajorMust,
    //公选
    PublicSelective,
    //公必
    PublicMust,
    //跨专业
    Interdisciplinary,
    //数量
    CourseTypeCount
};
const QString CourseTypeStr[CourseEnum::CourseTypeCount] = {
    "专选",
    "专必",
    "公选",
    "公必",
    "跨专业"
};

enum CourseAssessmentMethod: int{
    //开卷考
    OpenBookExam,
    //闭卷考
    CloseBookExam,
    //论文
    Paper,
    //小组作业
    GroupWork,
    //其他
    Other,
    //数量
    CourseAssessmentMethodCount
};
const QString CourseAssessmentMethodStr[CourseEnum::CourseAssessmentMethodCount] = {
    "开卷考试",
    "闭卷考试",
    "论文",
    "小组作业",
    "其他"
};


enum CourseStatus: int{
    //已删除
    Delete,
    //开选
    CanSelect,
    //已开课
    Open,
    //已结课
    Close,
    //未开放
    UnOpen,
    CourseStatusCount
};
const QString CourseStatusStr[CourseEnum::CourseStatusCount] = {
    "已删除",
    "可选择",
    "已开课",
    "已结课",
    "未开放"
};


enum HalfTerm: int{
    FirstTerm,
    SecondTerm,
    HalfTermCount
};
const QString HalfTermStr[CourseEnum::HalfTermCount] = {
    "上半学期",
    "下半学期",
};

}

namespace TchClassEnum{
enum TchClassInfo: int{
    //NetID
    StuID,
    //名字
    StuName,
    //性别
    StuGender,
    //学院
    StuDepartment,
    //年级
    StuGrade,
    //成绩
    StuScore,
    //数量
    TchClassInfoCount
};

const QString TchClassInfoStr[TchClassInfoCount] = {
    "NetID",
    "姓名",
    "性别",
    "学院",
    "年级",
    "成绩"
};
}
enum IDType: int{
    UserID,
    AdmID,
    TchID,
    StuID,
    CourseID
};

enum ProgressInfo: int{
    PrepareCourse1,
    SelectCourse1,
    CourseOn1,
    CourseClosed1,

    PrepareCourse2,
    SelectCourse2,
    CourseOn2,
    CourseClosed2
};
const QString ProgressInfoStr[8] = {
    "教师开始准备课程",
    "学生开始选择课程",
    "开始上课",
    "结课",

    "教师开始准备课程",
    "学生开始选择课程",
    "开始上课",
    "结课",
};
#endif // TOTALNAMEDESIGN_H
