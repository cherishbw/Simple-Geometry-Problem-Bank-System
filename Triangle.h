/*  Triangle.h —— 类的声明：只写“有哪些数据、有哪些函数”  */

#pragma once
#include <string>
using namespace std;

class Triangle
{
public:
    Triangle();                                    // 默认构造函数（3、4、5）
    Triangle(double x, double y, double z);         // 重载构造函数

    // 修改边长：合法返回 true，不合法返回 false
    bool setA(double x);
    bool setB(double y);
    bool setC(double z);

    // 获取边长
    double getA();
    double getB();
    double getC();

    void print();             // 输出三条边、周长、面积、类型

    bool isTriangle();        // 三条边能否构成三角形（合法性验证）
    double perimeter();       // 周长
    double area();            // 面积
    string type();            // 三角形的类型

private:
    double a, b, c;           // 三条边长
};
