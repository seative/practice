#include "array_2.h"
#include "vector3.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Point
{
private:
    int *b;

public:
    Point(int *a = nullptr)
    {
        b = nullptr;
        b = a;
        std::cout << "default" << std::endl;
    }
    Point(const Point &other)
    {
        delete b;
        b = new int;
        b = other.b;
        std::cout << "copy" << std::endl;
    }
    template <typename callback>
    void testcallfunc(callback func)
    {
        func(*b);
    }
};

void func1(int)
{
    std::cout << "test func1" << std::endl;
}

template <typename T, typename... Args>
void foo(const T &t, const Args &...rest)
{
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(rest) << std::endl;
}

template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    return os << t;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args... rest)
{
    os << t << ", ";
    return print(os, rest...);
}

// template <typename T>
// std::string debug_rep(const T &t)
// {
//     std::ostringstream ret;
//     ret << t;
//     return ret.str();
// }

// template <typename... args>
// std::ostream &errorMsg(std::ostream &os, const args &...rest)
// {
//     return print(os, debug_rep(rest)...);
// }

class A
{
public:
    virtual int a1(int a, int b)
    {
        std::cout << a;
        return a;
    }

    const A &a2() const
    {
        return *this;
    }
};

class B : public A
{
public:
    int a1(int a, int b)
    {
        std::cout << b;
        return b;
    }
};

const double *c1(const double *a)
{
    return a;
}

struct bitrh
{
    int date;
    int year;
};

int main()
{
    // using namespace std;
    // string s;
    // std::string str("some thing");
    // std::string str1{"initial test"};
    // std::string str2 = {"initial Dest cBapy"};
    // decltype(s.size()) punch_cont = 0;
    // for (auto &c : str2)
    //     if (isupper(c))
    //         s += c;
    // cout << s << endl;

    // int x = 1;
    // Point a = Point(&x);
    // a.testcallfunc([](int)
    //                { std::cout << "test suggess" << std::endl; });
    // a.testcallfunc(func1);

    //test::Size2 size = {2, 3};
    //test::Array2<double> ate0 = {{1, 3, 4}, {3, 3, 5}};
    // test::Array2<double> ate1{{1, 3, 4}, {3, 3, 5}};
    // test::Array2<double> ate2 = ate1;
    // test::Array2<double> ate3(size);
    // const int heightt = ate0.height();

    test::Vector3<double> ate2 = {1.f, 2.f, 34.f};
    test::ScalarType<test::Vector3<double>>::value nn;

    int i = 0;
    double d = 3.14;
    std::string s = "how long now";

    foo(i, s, 42, d);
    foo(s, 42, "hi");
    foo(d, s);
    foo("hi");
    print(std::cout, i, s, 42);
    // errorMsg(std::cerr, 5, 3);
    A testa;
    B testb;
    A &rt = testb;
    rt.a1(3, 5);
    const double cc = 6.4;
    c1(&cc);

    bitrh mingbir {40, 30};
    bitrh catbir = {.date = 20,
                    .year = 40};
    bitrh dogbir = {
        date : 40,
        year : 20
    };
    // 二分法求根号2
    // double lvalue = 1.0;
    // double rvalue = 1.5;
    // std::vector<double> list;
    // for (int i = 0; i < 40; i++)
    // {
    //     list.clear();
    //     for (double j = lvalue; j < rvalue; j += (rvalue - lvalue) / 1000)
    //         list.push_back(j);
    //     auto beg = list.begin(), end = list.end();
    //     auto mid = list.begin() + (end - beg) / 2;
    //     if (pow(*mid, 2) < 2)
    //         lvalue = *mid;
    //     else
    //         rvalue = *mid;
    // }
    // cout << lvalue << " " << rvalue << endl;

    return 0;
}
