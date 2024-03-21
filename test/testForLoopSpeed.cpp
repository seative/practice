#include <chrono>
#include <iostream>

using namespace std;

__attribute_noinline__ int cal1(int n)
{
    int fact0 = 1, fact1 = 1, fact2 = 1, fact3 = 1;
    for (int i = 1; i < n; i += 4)
    {
        fact0 *= i;
        fact1 *= i + 1;
        fact2 *= i + 2;
        fact3 *= i + 3;
    }
    return fact0 * fact1 * fact2 * fact3;
}

__attribute_noinline__ int cal2(int n)
{
    int fact = 1;
    for (int i = 1; i < n; i += 4)
    {
        fact *= i;
        fact *= i + 1;
        fact *= i + 2;
        fact *= i + 3;
    }
    return fact;
}

__attribute_noinline__ int cal3(int n)
{
    int fact = 1;
    for (int i = 1; i < n; ++i)
    {
        fact *= i;
    }
    return fact;
}

int main()
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    int a = cal1(1000000000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() << std::endl;

    start = std::chrono::steady_clock::now();
    int b = cal2(1000000000);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() << std::endl;

    start = std::chrono::steady_clock::now();
    int c = cal3(1000000000);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() << std::endl;
}