#include <format>
#include <iostream>
#include <type_traits>

// 一个永远都能匹配成功的concept
template <typename T>
concept always_satisfied = true;

// 一个约束T只能是整数类型的concept，整数类型包括 char, unsigned char, short, ushort, int, unsinged int, long等。
template <typename T>
concept integral = std::is_integral_v<T>;

// 一个约束T只能是整数类型，并且是有符号的concept
template <typename T>
concept signed_integral = integral<T> && std::is_signed_v<T>;

// 任意类型都能匹配成功的约束，因此mul只要支持乘法运算符的类型都可以匹配成功。
template <always_satisfied T>
T mul(T a, T b)
{
    return a * b;
}

// 整型才能匹配add函数的T
template <integral T>
T add(T a, T b)
{
    return a + b;
}

// 有符号整型才能匹配subtract函数的T
template <signed_integral T>
T subtract(T a, T b)
{
    return a - b;
}

int main()
{
    mul(1, 2);       // 匹配成功, T => int
    mul(1.0f, 2.0f); // 匹配成功，T => float

    add(1, -2);       // 匹配成功, T => int
    add(1.0f, 2.0f);  // 匹配失败, T => float，而T必须是整型
    subtract(1U, 2U); // 匹配失败，T => unsigned int,而T必须是有符号整型
    subtract(1, 2);   // 匹配成功, T => int

    double pi = 3.14159265358979;
    printf("%f\n", pi);         // 输出3.141593，后面的被四舍五入了
    cout << format("{}\n", pi); // format，输出完整的3.14159265358979

    // 与snprintf函数对应的是format_to_n
    char buff[50];
    sprintf(buff, "%f", pi);
    cout << buff << "\n"; // 与printf一样，输出3.141593
    format_to_n(buff, sizeof(buff), "{}", pi);
    cout << buff << "\n"; // 3.14159265358979
}