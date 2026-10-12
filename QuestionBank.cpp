/*  QuestionBank.cpp —— 题库类（整体类）的定义
    组合关系体现在：成员 t[MAX_Q] 是一个 Triangle 对象数组  */

#include "QuestionBank.h"
#include <iostream>
#include <sstream>        // 把输入的字符串变成数字
#include <iomanip>        // 用 setprecision 控制小数点后几位
using namespace std;

// ---------- 辅助函数：把字符串转成数字，转不了就返回 -1 ----------
// 放在文件开头，不加 static 也没问题，但加上 static 表示“只给这个文件用”
static double textToNum(string s)
{
    if (s == "") return -1;            // 空字符串
    stringstream ss(s);
    double v;
    char c;
    if (ss >> v)                       // 能转成数字
    {
        if (ss >> c) return -1;        // 后面还有别的字符，说明不是纯数字，例如 "abc"
        return v;
    }
    return -1;
}

// ---------- 构造函数 ----------
// 重点：本类构造函数要先让内嵌对象（数组 t 的每个元素）构造好，
// 再执行自己的函数体。这里是“先构造部分，再构造整体”。

QuestionBank::QuestionBank()
{
    name = "几何图形题库";          // 当 count = 0 时 m 用不到
    count = 0;
    totalScore = 0;
}

QuestionBank::QuestionBank(string na, int m)
{
    name = na;
    count = 0;
    totalScore = 0;

    if (m > MAX_Q) m = MAX_Q;        // 不能超过题库容量
    if (m < 0) m = 0;

    // 一次性往题库里放 m 道题（题目编号从 1 开始）
    if (m >= 1) addQuestion(Triangle(1, 3, 4, 5));
    if (m >= 2) addQuestion(Triangle(2, 6, 6, 6));
    if (m >= 3) addQuestion(Triangle(3, 3, 4, 5));
    if (m >= 4) addQuestion(Triangle(4, 5, 5, 6));
    if (m >= 5) addQuestion(Triangle(5, 6, 8, 10));
    if (m >= 6) addQuestion(Triangle(6, 2, 3, 4));
    if (m >= 7) addQuestion(Triangle(7, 7, 8, 9));
    if (m >= 8) addQuestion(Triangle(8, 1, 1, 1));
    if (m >= 9) addQuestion(Triangle(9, 5, 12, 13));
    if (m >= 10) addQuestion(Triangle(10, 8, 15, 17));
}

// ---------- 基本操作：初始化、修改、获取 ----------

void QuestionBank::setName(string na) { name = na; }

string QuestionBank::getName() { return name; }

int QuestionBank::getCount() { return count; }

int QuestionBank::getTotalScore() { return totalScore; }

// 平均分 = 总分 / 题目数量
double QuestionBank::getAverage()
{
    if (count == 0) return 0;        // 防止除以 0
    return (double)totalScore / count;
}

string QuestionBank::getAverageStr()
{
    return roundToStr(getAverage(), 2);   // roundToStr 是 Triangle.h 里声明的函数
}

// ---------- 输出 ----------

void QuestionBank::printInfo()
{
    cout << "题库名称：" << name << endl;
    cout << "题目数量：" << count << " 道" << endl;
    cout << "所做题目总分：" << totalScore << " 分" << endl;
    cout << "平均分：" << getAverageStr() << " 分" << endl;
}

void QuestionBank::printAll()
{
    if (count == 0)
    {
        cout << "题库里还没有题目。" << endl;
        return;
    }
    for (int i = 0; i < count; i++)
        t[i].printQuestion();
}

void QuestionBank::printTitles()
{
    for (int i = 0; i < count; i++)
    {
        cout << "  [" << i + 1 << "] 第 " << t[i].getID() << " 题：边长 "
             << t[i].getA() << "、" << t[i].getB() << "、" << t[i].getC();

        if (t[i].isAnswered())
            cout << "（已作答，得 " << t[i].getScore() << " 分）";
        else
            cout << "（未作答）";

        cout << endl;
    }
}

// ---------- 其他操作 ----------

// 向题库内增加题目：加得下返回 true，满了返回 false
bool QuestionBank::addQuestion(Triangle q)
{
    if (count >= MAX_Q) return false;      // 题库已满

    t[count] = q;                          // 对象之间可以直接赋值（整体复制）
    score[count] = 0;
    count++;
    return true;
}

// 在题库内删除题目：后面所有题目往前挪一位
bool QuestionBank::deleteQuestion(int index)
{
    if (index < 0 || index >= count) return false;

    for (int i = index; i < count - 1; i++)
        t[i] = t[i + 1];      
    count--;
 
    return true;
}

// 查询题库的题目：打印出来，并返回做完这些题的总得分
int QuestionBank::query(int index)
{
    if (index < 0 || index >= count)
    {
        cout << "没有这道题。" << endl;
        return totalScore;
    }
    t[index].printQuestion();
    return totalScore;
}

// 按题目编号查询，返回数组下标；找不到返回 -1
int QuestionBank::queryByID(int id)
{
    for (int i = 0; i < count; i++)
        if (t[i].getID() == id) return i;
    return -1;
}

// 输入自己这道题的答案：答对得 10 分，答错得 0 分
bool QuestionBank::setUserAnswer(int index, string ans)
{
    if (index < 0 || index >= count)
    {
        cout << "没有这道题。" << endl;
        return false;
    }
    if (textToNum(ans) < 0)               // 检查输入的是不是数字
    {
        cout << "答案必须是数字，例如 6 或 6.00。" << endl;
        return false;
    }

    t[index].setUserAnswer(ans);          // 交给内嵌对象去保存

    if (t[index].isRight())
        t[index].setScore(10);
    else
        t[index].setScore(0);

    score[index] = t[index].getScore();
    gradeAll();

    // 每作答一次，就往交卷记录（vector）里追加一条
    string rec = "第 " + to_string(index + 1) + " 道题：我答 " + ans
        + "，正确答案 " + t[index].getCorrectAnswer()
        + "，" + (t[index].isRight() ? "答对了" : "答错了");
    addHistory(rec);

    return true;
}

// 按题目编号答题
bool QuestionBank::answerByID(int id, string ans)
{
    int index = queryByID(id);
    if (index == -1)
    {
        cout << "题库里没有编号为 " << id << " 的题目。" << endl;
        return false;
    }
    return setUserAnswer(index, ans);
}

// 全部批改：把每道题的得分加起来，就是总分
int QuestionBank::gradeAll()
{
    totalScore = 0;
    for (int i = 0; i < count; i++)
    {
        score[i] = t[i].getScore();
        totalScore = totalScore + score[i];
    }
    return totalScore;
}

// ---------- STL 容器 vector 的用法 ----------

// 往交卷记录里追加一条：push_back 会在 vector 末尾加元素，
// 容器会自动扩容，不用像数组那样提前定死长度
void QuestionBank::addHistory(string record)
{
    history.push_back(record);
}

// 把交卷记录全部打印出来：用 size() 拿元素个数，用下标 [i] 取出第 i 条
void QuestionBank::printHistory()
{
    if (history.size() == 0)
    {
        cout << "  还没有任何答题记录。" << endl;
        return;
    }

    for (int i = 0; i < (int)history.size(); i++)      // size() 返回的是无符号数，转成 int 再比较
        cout << "  第 " << (i + 1) << " 次作答 —— " << history[i] << endl;
}

int QuestionBank::getHistorySize()
{
    return (int)history.size();
}
