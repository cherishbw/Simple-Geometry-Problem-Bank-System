/*  Triangle.cpp —— 类的定义：写函数里面的代码，函数名前面要加 Triangle::  */

#include "Triangle.h"
#include <iostream>
#include <cmath>          // 求面积要用开平方 sqrt()
using namespace std;

// ---------- 构造函数 ----------

Triangle::Triangle()                    // 默认构造函数
{
    a = 3;
    b = 4;
    c = 5;
}

Triangle::Triangle(double x, double y, double z)     // 重载构造函数
{
    a = x;
    b = y;
    c = z;
    if (isTriangle() == false)          // 这三条边不能构成三角形
    {
        a = 3;                          // 就换成默认的 3、4、5
        b = 4;
        c = 5;
    }
}

// ---------- 修改边长（带合法性验证）----------
// 做法：先把新值放进去，检查还能不能构成三角形，不能就改回原来的值

bool Triangle::setA(double x)
{
    double old = a;
    a = x;
    if (isTriangle() == false) { a = old; return false; }
    return true;
}

bool Triangle::setB(double y)
{
    double old = b;
    b = y;
    if (isTriangle() == false) { b = old; return false; }
    return true;
}

bool Triangle::setC(double z)
{
    double old = c;
    c = z;
    if (isTriangle() == false) { c = old; return false; }
    return true;
}

// ---------- 获取边长 ----------

double Triangle::getA() { return a; }
double Triangle::getB() { return b; }
double Triangle::getC() { return c; }

// ---------- 输出 ----------

void Triangle::print()
{
    cout << "  三条边：" << a << "、" << b << "、" << c << endl;
    cout << "  周长  ：" << perimeter() << endl;
    cout << "  面积  ：" << area() << endl;
    cout << "  类型  ：" << type() << endl;
}

// ---------- 其他操作 ----------

// 判断三条边能否构成三角形：每条边都要是正数，并且任意两边之和都要大于第三边
bool Triangle::isTriangle()
{
    if (a <= 0 || b <= 0 || c <= 0) return false;
    if (a + b <= c) return false;
    if (a + c <= b) return false;
    if (b + c <= a) return false;
    return true;
}

// 周长
double Triangle::perimeter()
{
    return a + b + c;
}

// 面积（海伦公式：先求半周长 p，再开平方）
double Triangle::area()
{
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// 三角形的类型
string Triangle::type()
{
    if (a == b && b == c) return "等边三角形";
    if (a == b || b == c || a == c) return "等腰三角形";
    if (a * a + b * b == c * c) return "直角三角形";
    if (a * a + c * c == b * b) return "直角三角形";
    if (b * b + c * c == a * a) return "直角三角形";
    return "普通三角形";
}
