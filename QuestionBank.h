/*  QuestionBank.h —— 题库类（整体类）
    组合关系：题库里“有”很多道三角形题目，所以把 Triangle 对象数组当成成员变量。
    调用内嵌对象构造函数的顺序，就是数组里 t[0]、t[1]、t[2]…… 的顺序。  */

#pragma once
#include <string>
#include <vector>          // 交卷记录用 vector 保存（STL 容器）
#include "Triangle.h"
using namespace std;

const int MAX_Q = 10;          // 题库最多放 10 道题

class QuestionBank
{
public:
    QuestionBank();                                   // 默认构造函数
    QuestionBank(string na, int m);                   // 重载构造函数：题库名 + 最多几道题

    // ---------- 基本操作：初始化、修改、获取、输出 ----------
    void   setName(string na);        // 修改题库名称
    string getName();                 // 获取题库名称


    int    getCount();                // 获取题目数量
    int    getTotalScore();           // 获取总分
    double getAverage();              // 获取平均分
    string getAverageStr();           // 平均分（保留 2 位的字符串）

    void   printInfo();               // 输出题库的整体信息
    void   printAll();                // 输出题库里所有的题目
    void   printTitles();             // 只输出标题，用来显示菜单

    // ---------- 其他操作 ----------
    bool   addQuestion(Triangle t);            // 向题库内增加题目
    bool   deleteQuestion(int index);          // 在题库内删除题目（index 从 0 开始）
    int    query(int index);                   // 查询题库的题目：打印出来并返回总得分
    int    queryByID(int id);                  // 按题目编号查询，返回下标；找不到返回 -1
    bool   setUserAnswer(int index, string ans); // 输入自己这道题的答案
    bool   answerByID(int id, string ans);       // 按编号答题
    int    gradeAll();                         // 全部批改一遍，算出总分

    // ---------- STL 容器：用 vector 保存交卷记录 ----------
    // 用数组的话要提前定大小、还可能存满；vector 能自动变长，想存多少条都行
    void   addHistory(string record);          // 往交卷记录里追加一条
    void   printHistory();                     // 把交卷记录全部打印出来
    int    getHistorySize();                   // 交卷记录有多少条


private:
    string   name;            // 题库名称      —— 基本类型成员
    Triangle t[MAX_Q];        // 包含的所有题目 —— 内嵌对象成员（对象数组）
    int      count;           // 题目数量
    int      score[MAX_Q];    // 所做每道题的得分
    int      totalScore;      // 总分
    vector<string> history;   // 交卷记录（STL 容器 vector）
};
