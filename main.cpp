/*  main.cpp —— 对象的生成与使用（这里不写成员函数的实现）  */

#include <iostream>
#include "Triangle.h"
using namespace std;

int main()
{
    // ========== 1. 生成对象 ==========
    Triangle t1;                  // 默认构造函数：3、4、5
    Triangle t2(6, 6, 6);         // 重载构造函数：等边三角形
    Triangle t3(1, 1, 10);        // 1+1 不大于 10，不能构成三角形

    cout << "t1（默认构造函数，3、4、5）：" << endl;
    t1.print();

    cout << "\nt2（重载构造函数，6、6、6）：" << endl;
    t2.print();

    cout << "\nt3（输入 1、1、10 不合法，程序自动换成默认的 3、4、5）：" << endl;
    t3.print();

    // ========== 2. 修改边长（set 函数会验证数据是否合法）==========
    cout << "\n修改 t1 的边长：" << endl;

    if (t1.setA(5) == true)
        cout << "  把 a 改成 5   —— 成功" << endl;
    else
        cout << "  把 a 改成 5   —— 失败" << endl;

    if (t1.setA(100) == true)
        cout << "  把 a 改成 100 —— 成功" << endl;
    else
        cout << "  把 a 改成 100 —— 失败（4+5 不大于 100，不能构成三角形）" << endl;

    if (t1.setB(-2) == true)
        cout << "  把 b 改成 -2  —— 成功" << endl;
    else
        cout << "  把 b 改成 -2  —— 失败（边长必须是正数）" << endl;

    cout << "  修改后的 t1：" << endl;
    t1.print();

    // ========== 3. 获取边长 ==========
    cout << "\n用获取函数读出 t1 的三条边："
         << t1.getA() << "、" << t1.getB() << "、" << t1.getC() << endl;

    // ========== 4. 其他操作 ==========
    cout << "\n对 t2 做其他操作：" << endl;
    cout << "  能否构成三角形：" << (t2.isTriangle() ? "能" : "不能") << endl;
    cout << "  周长：" << t2.perimeter() << endl;
    cout << "  面积：" << t2.area() << endl;
    cout << "  类型：" << t2.type() << endl;

    return 0;
}
