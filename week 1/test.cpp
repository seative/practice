#include <iostream>
using namespace std;

void test01( int *a)
{
    cout << *a;
}
int main(int argc, char *argv[])
{
    int temp = 300;
    const int *d = &temp;
    test01(d);
}