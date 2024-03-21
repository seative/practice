#include "functional"
#include "iostream"

using namespace std;

int main()
{
    auto a = [](int a) {};
    std::function<void(int)> b = a;

    void(*func)(int) = [](int a) {};

    std::cout << sizeof(a) << std::endl;
    std::cout << sizeof(b) << std::endl;
}