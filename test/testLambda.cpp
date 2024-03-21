#include <iostream>

int main()
{
    // 最简单的lamber表达式，没有任何意义
    [] {};

    // 省略参数列表和返回值类型，由编译器推导
    int a = 3, b = 4;
    [=]
    { return a + b; }; // 函数体内的分号不要忘记

    // 引用传递的方式可以改变变量的值
    auto func1 = [&](int c)
    { return b = a + c; };
    std::cout << func1(10) << std::endl;

    // 值传递捕获不能改变变量的值，除非使用mutable
    auto fun2 = [=](int c) mutable -> int
    { return b = a + c; };
    fun2(10);
    return 0;
}

// lamda表达式的本质是构造一个未命名的函数对象
