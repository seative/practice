#include <chrono>
#include <iostream>

class B
{
public:
    B() : i_(0) {}
    virtual ~B() {}
    virtual void f(int i) = 0;
    int get() const { return i_; }

protected:
    int i_;
};
class D : public B
{
public:
    void f(int i) { i_ += i; }
};

class A
{
public:
    A() : i_(0) {}
    void f(int i) { i_ += i; }
    int get() const { return i_; }

protected:
    int i_;
};

template <typename T>
class C
{
public:
    C() : i_(0) {}
    void f(int i)
    {
        static_cast<T *>(this)->f(i); // 强制转换为子类，调用子类的f(int i)
    }
    int get() const { return i_; }

protected:
    int i_;
};

class F : C<F>
{
public:
    void f(int i)
    {
        i_ += i;
    }
};

int main()
{
    D d;
    A a;
    F g;
    std::chrono::system_clock::time_point time1 = std::chrono::system_clock::now();
    for (int i = 0; i < 1e4; ++i)
    {
        d.f(1);
    }
    std::chrono::system_clock::time_point time2 = std::chrono::system_clock::now();
    std::cout << (time2 - time1).count() << std::endl;

    std::chrono::system_clock::time_point time3 = std::chrono::system_clock::now();
    for (int i = 0; i < 1e4; ++i)
    {
        a.f(1);
    }
    std::chrono::system_clock::time_point time4 = std::chrono::system_clock::now();
    std::cout << (time4 - time3).count() << std::endl;

    std::chrono::system_clock::time_point time5 = std::chrono::system_clock::now();
    for (int i = 0; i < 1e4; ++i)
    {
        g.f(1);
    }
    std::chrono::system_clock::time_point time6 = std::chrono::system_clock::now();
    std::cout << (time6 - time5).count() << std::endl;
}