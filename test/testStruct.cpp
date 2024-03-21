#include <iostream>

template <typename E1, typename E2, typename E3>
struct Triple
{
    E1 x;
    E2 y;
    E3 z;
};

int main()
{
    auto temp = (3, 2, 9);

    Triple<int, Triple<int, int, int>, double> a;
    auto [b, c, d] = a;
}