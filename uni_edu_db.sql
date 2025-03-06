/*
 Navicat Premium Data Transfer

 Source Server         : root
 Source Server Type    : MySQL
 Source Server Version : 80033
 Source Host           : localhost:3306
 Source Schema         : uni_edu_db

 Target Server Type    : MySQL
 Target Server Version : 80033
 File Encoding         : 65001

 Date: 20/03/2024 23:50:19
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for adm_info
-- ----------------------------
DROP TABLE IF EXISTS `adm_info`;
CREATE TABLE `adm_info`  (
  `admID` int NOT NULL COMMENT '管理员NetID',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '姓名',
  `gender` int NOT NULL COMMENT '性别',
  `age` int NOT NULL COMMENT '年龄',
  PRIMARY KEY (`admID`) USING BTREE,
  CONSTRAINT `fk_ai_admID` FOREIGN KEY (`admID`) REFERENCES `user_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of adm_info
-- ----------------------------
INSERT INTO `adm_info` VALUES (10000000, 'Admin', 0, 27);

-- ----------------------------
-- Table structure for course_info
-- ----------------------------
DROP TABLE IF EXISTS `course_info`;
CREATE TABLE `course_info`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '课程编号',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '课程名称',
  `tchID` int NOT NULL COMMENT '授课教师编号',
  `credit` int NOT NULL COMMENT '学分',
  `period` double NOT NULL COMMENT '学时',
  `year` int NOT NULL COMMENT '年份',
  `term` int NOT NULL COMMENT '学期',
  `stuNum` int NOT NULL COMMENT '人数',
  `address` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '上课地点',
  `introduction` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL COMMENT '课程介绍',
  `courseType` int NOT NULL COMMENT '0：专选；1：专必；2：公必；3：公选；4：跨专业',
  `assessmentMethod` int NOT NULL COMMENT '0：开卷考；1：闭卷考；2：论文；3：小组作业；4：其他',
  `status` int NOT NULL COMMENT '0：已删除；1：开选；2：已开课；3：已停课；4：未开放',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_ci_tchID`(`tchID` ASC) USING BTREE,
  CONSTRAINT `fk_ci_tchID` FOREIGN KEY (`tchID`) REFERENCES `tch_info` (`tchID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 55 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of course_info
-- ----------------------------
INSERT INTO `course_info` VALUES (42, '基础算术', 30000000, 3, 57, 2020, 1, 50, '寺子屋', '        该课程案例开始减肥的离开撒娇开了房骄傲的说离开房间凉快我骄傲if就ois呢哦安家费哦阿松殴打峰年上的方便u哦阿尔我后来没戏了能看见noi就爱我if白\n        尽快落实到解放路口睡觉啊foi叫我i哦安抚就爱我if急哦i外藕粉就睡觉哦欧派克foi挖掘欧剑锋五年级呢基本框架发布水电费奥德赛发的顺丰', 3, 1, 3);
INSERT INTO `course_info` VALUES (43, '112', 30000000, 3, 27, 2020, 1, 1, '3213', '为瓦房撒答复我Roll	 F-=AV波规划那么小吗，sPOQW9PEC FHFVABENFM D,.Z,CK\'Sj{a()sh*g&(YVU GKJB,MX,./,X\'Z;LodaSI）——｝｛QU（）以h9ge2BVYILGHBABKN.SFM/,V;\'C.ZXLa+o_|｝I_U(S)*Yh9GUIFBHGBM', 4, 1, 3);
INSERT INTO `course_info` VALUES (44, 't', 30000000, 1, 13.5, 2020, 1, 1, 't', 'asfsaf', 0, 0, 0);
INSERT INTO `course_info` VALUES (45, '初级火焰魔法', 30000001, 2, 30, 2020, 1, 20, '迷途竹林', '', 3, 4, 3);
INSERT INTO `course_info` VALUES (46, '初级制药', 30000002, 1, 13.5, 2020, 1, 1, '迷途竹林', '', 4, 0, 3);
INSERT INTO `course_info` VALUES (47, '123', 30000000, 1, 13.5, 2020, 2, 1, '123', '', 0, 0, 0);
INSERT INTO `course_info` VALUES (48, '123', 30000000, 1, 13.5, 2020, 2, 1, '123', '123123123123123', 0, 0, 0);
INSERT INTO `course_info` VALUES (49, '123', 30000000, 1, 40.5, 2020, 2, 123, '123', '123456', 0, 0, 0);
INSERT INTO `course_info` VALUES (50, '123', 30000000, 1, 13.5, 2020, 2, 1, '123', '123', 2, 3, 2);
INSERT INTO `course_info` VALUES (51, '123', 30000000, 1, 13.5, 2020, 2, 1, '123', '本课程的目的是使学生了解中国共产党把马克思主义基本原理同中国具体实际相结合、同中华优秀传统文化相结合的历史进程，认识毛泽东思想和中国特色社会主义理论体系是“二个结合”的历史性飞跃的理论成果，是中国化时代化的马克思主义的结晶，是马克思主义与时俱进理论品质最显著最集中的体现。\n本课程以马克思主义中国化时代化为主线，以毛泽东思想、邓小平理论、“三个代表”重要思想和科学发展观为重点。通过本课程的学习，培养学生运用马克思主义的立场、观点和方法分析问题、解决问题的能力，使学生正确认识马克思主义中国化时代化的理论成果在指导中国革命、建设和改革中的重要历史地位和作用，不断增强道路自信、理论自信、制度自信和文化自信，坚定中国特色社会主义理想信念，帮助学生确立科学社会主义信仰和建设中国特色社会主义的共同理想，增强执行党的基本路线和基本纲领的自觉性和坚定性，坚定在党的领导下走中国特色社会主义道路的理想信念，为建设社会主义现代化强国做出应有的贡献。', 0, 0, 0);
INSERT INTO `course_info` VALUES (52, '数据结构与算法', 30000003, 3, 28.5, 2020, 2, 120, '寺子屋', '本课程全面系统地介绍计算机领域内基本的数据结构基本概念和相应的算法分析思想与技巧等方面内容。', 1, 0, 2);
INSERT INTO `course_info` VALUES (53, '计算机组成原理', 30000003, 3, 42, 2020, 2, 60, '寺子屋', '       通过本课程学习，使学生从总体上认识计算机的基本组成和工作原理。掌握计算机基本组成部件的结构、工作原理、内部运行机制及设计方法。加深学生对计算机软、硬件系统的整体化理解，建立硬件/软件协同的整机概念，提升学生计算机系统的分析与设计能力。把我国在计算机软、硬件领域取得的成就，包括我国计算机的发展历史、我国的储存产业等内容融入到课程讲解中，使学生认识到关键领域技术的重要性，激发他们的学习热情和探索精神。', 1, 0, 2);
INSERT INTO `course_info` VALUES (54, '离散数学基础', 30000003, 3, 57, 2020, 2, 1, '寺子屋', '《离散数学基础》课程是软件工程专业本科生必修的专业基础课程。它是学习后续专业课程不可缺少的数学工具。该课程结合软件工程学科的特点，主要研究世界事物间的离散结构和相互关系，是一门理论性较强，应用性较广的课程。本课程教学内容覆盖面了数理逻辑、集合论、图论、代数结构和组合数学这五部分。数理逻辑的重点是公式演算与推理证明；集合论的重点是关系理论与映射的描述；图论着重于数形结合的描述以及各种实际应用；代数结构则主要是从系统宏观的代数方法去研究客观事物的各种性质与特征；组合数学的重点是基本的组合计数公式、递推方程与生成函数等。通过本课程的学习，使学生掌握数理逻辑、集合论、图论、代数结构和组合数学等离散数学的基本概念和基本原理，接受现代数学关于离散结构的观点，会从系统结构的研究方法出发，研究事物间的有关属性；同时要应用数形结合方法，使事物论证简洁直观；通过描述方法和缜密思维方法的训练，使学生具有良好的抽象思维和逻辑思维能力。不但为学习软件工程专业的后续课程奠定坚实的理论基础，而且为学生今后从事软件工程方面的工作提供重要的工具。', 1, 0, 2);
INSERT INTO `course_info` VALUES (55, 'ASDF', 30000000, 2, 27, 2020, 2, 15, '123456', '', 2, 3, 2);

-- ----------------------------
-- Table structure for course_selection_info
-- ----------------------------
DROP TABLE IF EXISTS `course_selection_info`;
CREATE TABLE `course_selection_info`  (
  `courseID` int NOT NULL COMMENT '课程编号',
  `stuID` int NOT NULL COMMENT '学生编号',
  `status` int NOT NULL COMMENT '0：无法选；1：未选；2：已选；',
  `stuScore` int NULL DEFAULT NULL COMMENT '学生成绩',
  INDEX `fk_csi_courseID`(`courseID` ASC) USING BTREE,
  INDEX `fk_csi_stuID`(`stuID` ASC) USING BTREE,
  CONSTRAINT `fk_csi_courseID` FOREIGN KEY (`courseID`) REFERENCES `course_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_csi_stuID` FOREIGN KEY (`stuID`) REFERENCES `stu_info` (`stuID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of course_selection_info
-- ----------------------------
INSERT INTO `course_selection_info` VALUES (43, 20000000, 2, 0);
INSERT INTO `course_selection_info` VALUES (46, 20000000, 2, 1);
INSERT INTO `course_selection_info` VALUES (42, 20000000, 2, 96);
INSERT INTO `course_selection_info` VALUES (45, 20000000, 2, 75);
INSERT INTO `course_selection_info` VALUES (45, 20000001, 2, 96);
INSERT INTO `course_selection_info` VALUES (42, 20000001, 2, 98);
INSERT INTO `course_selection_info` VALUES (42, 20000002, 2, 94);
INSERT INTO `course_selection_info` VALUES (45, 20000002, 2, 86);
INSERT INTO `course_selection_info` VALUES (50, 20000000, 1, 99);
INSERT INTO `course_selection_info` VALUES (52, 20000000, 2, 70);
INSERT INTO `course_selection_info` VALUES (53, 20000000, 2, NULL);
INSERT INTO `course_selection_info` VALUES (54, 20000000, 2, NULL);
INSERT INTO `course_selection_info` VALUES (55, 20000000, 2, 78);

-- ----------------------------
-- Table structure for course_timetable
-- ----------------------------
DROP TABLE IF EXISTS `course_timetable`;
CREATE TABLE `course_timetable`  (
  `courseID` int NOT NULL COMMENT '课程编号',
  `week` int NOT NULL COMMENT '第几周',
  `whichHalfTerm` int NOT NULL COMMENT '0：上半学期；1：下半学期',
  `wc` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '哪几节课',
  INDEX `fk_ct_courseID`(`courseID` ASC) USING BTREE,
  CONSTRAINT `fk_ct_courseID` FOREIGN KEY (`courseID`) REFERENCES `course_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of course_timetable
-- ----------------------------
INSERT INTO `course_timetable` VALUES (42, 0, 0, '100000');
INSERT INTO `course_timetable` VALUES (42, 2, 0, '100000');
INSERT INTO `course_timetable` VALUES (42, 0, 1, '100000');
INSERT INTO `course_timetable` VALUES (42, 2, 1, '100000');
INSERT INTO `course_timetable` VALUES (43, 1, 0, '110000');
INSERT INTO `course_timetable` VALUES (45, 2, 1, '001100');
INSERT INTO `course_timetable` VALUES (46, 2, 0, '100000');
INSERT INTO `course_timetable` VALUES (50, 0, 0, '010000');
INSERT INTO `course_timetable` VALUES (53, 0, 0, '000010');
INSERT INTO `course_timetable` VALUES (53, 4, 0, '000010');
INSERT INTO `course_timetable` VALUES (53, 0, 1, '000010');
INSERT INTO `course_timetable` VALUES (54, 0, 0, '100000');
INSERT INTO `course_timetable` VALUES (54, 2, 0, '100000');
INSERT INTO `course_timetable` VALUES (54, 0, 1, '100000');
INSERT INTO `course_timetable` VALUES (54, 2, 1, '100000');
INSERT INTO `course_timetable` VALUES (52, 0, 0, '000100');
INSERT INTO `course_timetable` VALUES (52, 4, 1, '000100');
INSERT INTO `course_timetable` VALUES (55, 1, 0, '001000');
INSERT INTO `course_timetable` VALUES (55, 3, 0, '001000');

-- ----------------------------
-- Table structure for progress_table
-- ----------------------------
DROP TABLE IF EXISTS `progress_table`;
CREATE TABLE `progress_table`  (
  `idx` int NOT NULL,
  `progress` int NOT NULL COMMENT '0：教师准备课程\r\n1：学生选择课程\r\n2：开课\r\n3：结课，学期+1\r\n4：教师准备课程\r\n5：学生选择课程\r\n6：开课\r\n7：结课，学期置1，学年+1',
  `year` int NOT NULL,
  `term` int NOT NULL,
  PRIMARY KEY (`idx`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of progress_table
-- ----------------------------
INSERT INTO `progress_table` VALUES (0, 6, 2020, 2);

-- ----------------------------
-- Table structure for stu_info
-- ----------------------------
DROP TABLE IF EXISTS `stu_info`;
CREATE TABLE `stu_info`  (
  `stuID` int NOT NULL COMMENT '学生编号',
  `department` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '院系',
  `major` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '专业',
  `grade` int NOT NULL COMMENT '年级',
  `GPA` double NOT NULL COMMENT '绩点',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '姓名',
  `age` int NOT NULL COMMENT '年龄',
  `gender` int NOT NULL COMMENT '0：男；1：女',
  PRIMARY KEY (`stuID`) USING BTREE,
  INDEX `fk_si_stuID`(`stuID` ASC) USING BTREE,
  CONSTRAINT `fk_si_stuID` FOREIGN KEY (`stuID`) REFERENCES `user_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of stu_info
-- ----------------------------
INSERT INTO `stu_info` VALUES (10000001, '123', '123', 1, 0, '123', 123, 0);
INSERT INTO `stu_info` VALUES (20000000, '雾之湖', '冰魔法', 1, 0, '琪露诺', 72, 1);
INSERT INTO `stu_info` VALUES (20000001, '雾之湖', '自然魔法', 1, 0, '大妖精', 73, 1);
INSERT INTO `stu_info` VALUES (20000002, '兽道', '光学', 1, 0, '露米娅', 27, 1);
INSERT INTO `stu_info` VALUES (20000010, '123', '123', 1, 0, '123', 1, 0);
INSERT INTO `stu_info` VALUES (22330000, '岭南学院', '金融学', 1, 0, '李中序', 18, 1);
INSERT INTO `stu_info` VALUES (22330001, '中国语言文学系', '汉语言文学', 1, 0, '赵雪儿', 18, 1);
INSERT INTO `stu_info` VALUES (22330002, '历史学系', '历史学', 1, 0, '唐欧信', 19, 0);
INSERT INTO `stu_info` VALUES (22330003, '哲学系', '哲学', 1, 0, '吕徐', 18, 0);
INSERT INTO `stu_info` VALUES (22330004, '管理学院', '工商管理', 1, 0, '王雄安', 19, 0);
INSERT INTO `stu_info` VALUES (22330005, '软件工程学院', '软件工程', 1, 0, '理新锐', 18, 0);
INSERT INTO `stu_info` VALUES (22330006, '人工智能学院', '人工智能', 2, 0, '郑欣然', 19, 1);
INSERT INTO `stu_info` VALUES (22330007, '航空航天学院', '航空航天工程', 2, 0, '陈西山', 18, 0);
INSERT INTO `stu_info` VALUES (22330008, '电子与通信工程学院', '电子信息科学与技术', 2, 0, '张湘潭', 19, 1);
INSERT INTO `stu_info` VALUES (22330009, '物理学院', '物理学', 1, 0, '赵雪儿', 18, 1);
INSERT INTO `stu_info` VALUES (22330088, 'AAAAA', 'BBBBB', 1, 0, 'AAAAA', 20, 0);
INSERT INTO `stu_info` VALUES (22331090, '岭南学院', '金融学', 1, 0, '李中序', 18, 0);

-- ----------------------------
-- Table structure for tch_info
-- ----------------------------
DROP TABLE IF EXISTS `tch_info`;
CREATE TABLE `tch_info`  (
  `tchID` int NOT NULL COMMENT '教师编号',
  `department` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '院系',
  `position` int NOT NULL COMMENT '1：讲师；2：副教授；3：教授；4：特聘教授；5：终身教授',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '教师名称',
  `age` int NOT NULL COMMENT '年龄',
  `gender` int NOT NULL COMMENT '0：男；1：女',
  PRIMARY KEY (`tchID`) USING BTREE,
  CONSTRAINT `fk_ti_tchID` FOREIGN KEY (`tchID`) REFERENCES `user_info` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of tch_info
-- ----------------------------
INSERT INTO `tch_info` VALUES (10000002, '123', 1, '123', 23, 0);
INSERT INTO `tch_info` VALUES (30000000, '寺子屋', 5, '上白泽慧音', 99, 1);
INSERT INTO `tch_info` VALUES (30000001, '寺子屋', 4, '藤原妹红', 200, 1);
INSERT INTO `tch_info` VALUES (30000002, '永远亭', 5, '八意永琳', 200, 1);
INSERT INTO `tch_info` VALUES (30000003, '数学学院', 3, '八云蓝', 27, 1);
INSERT INTO `tch_info` VALUES (33220000, '物理学院', 3, '谢辛亥', 45, 0);
INSERT INTO `tch_info` VALUES (33220001, '软件工程学院', 3, '李元华', 49, 0);
INSERT INTO `tch_info` VALUES (33220002, '中国语言文学系', 2, '赵许巍', 35, 0);
INSERT INTO `tch_info` VALUES (33220003, '历史学系', 5, '赵凌霄', 50, 1);

-- ----------------------------
-- Table structure for user_info
-- ----------------------------
DROP TABLE IF EXISTS `user_info`;
CREATE TABLE `user_info`  (
  `id` int NOT NULL COMMENT '用户编号',
  `pwd` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '密码',
  `user_type` int NOT NULL COMMENT '用户类型（0：未定义；1：管理员；2：教师；3：学生）',
  `status` int NOT NULL COMMENT '0：启用；1：已删除',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of user_info
-- ----------------------------
INSERT INTO `user_info` VALUES (10000000, '123456', 1, 0);
INSERT INTO `user_info` VALUES (10000001, 'sysu_10000001', 3, 1);
INSERT INTO `user_info` VALUES (10000002, 'sysu_10000002', 2, 1);
INSERT INTO `user_info` VALUES (20000000, '123456', 3, 0);
INSERT INTO `user_info` VALUES (20000001, 'sysu_20000001', 3, 0);
INSERT INTO `user_info` VALUES (20000002, 'sysu_20000002', 3, 0);
INSERT INTO `user_info` VALUES (20000010, 'sysu_20000010', 3, 1);
INSERT INTO `user_info` VALUES (22330000, 'sysu_22330000', 3, 0);
INSERT INTO `user_info` VALUES (22330001, 'sysu_22330001', 3, 0);
INSERT INTO `user_info` VALUES (22330002, 'sysu_22330002', 3, 1);
INSERT INTO `user_info` VALUES (22330003, 'sysu_22330003', 3, 0);
INSERT INTO `user_info` VALUES (22330004, 'sysu_22330004', 3, 0);
INSERT INTO `user_info` VALUES (22330005, 'sysu_22330005', 3, 0);
INSERT INTO `user_info` VALUES (22330006, 'sysu_22330006', 3, 0);
INSERT INTO `user_info` VALUES (22330007, 'sysu_22330007', 3, 0);
INSERT INTO `user_info` VALUES (22330008, 'sysu_22330008', 3, 0);
INSERT INTO `user_info` VALUES (22330009, 'sysu_22330009', 3, 0);
INSERT INTO `user_info` VALUES (22330088, 'sysu_22330088', 3, 0);
INSERT INTO `user_info` VALUES (22331090, 'sysu_22331090', 3, 1);
INSERT INTO `user_info` VALUES (30000000, '123456', 2, 0);
INSERT INTO `user_info` VALUES (30000001, '123456', 2, 0);
INSERT INTO `user_info` VALUES (30000002, 'sysu_30000002', 2, 0);
INSERT INTO `user_info` VALUES (30000003, 'sysu_30000003', 2, 0);
INSERT INTO `user_info` VALUES (33220000, 'sysu_33220000', 2, 0);
INSERT INTO `user_info` VALUES (33220001, 'sysu_33220001', 2, 0);
INSERT INTO `user_info` VALUES (33220002, 'sysu_33220002', 2, 0);
INSERT INTO `user_info` VALUES (33220003, 'sysu_33220003', 2, 0);

SET FOREIGN_KEY_CHECKS = 1;
