#include <cstdio>

double fx(double h)
{
    double f = 4 / (1 + h * h);
    return f;
}
int main(int argc, char *argv[])
{
    const int n = 1000000;
    double h = 1. / n;
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        double x = h * (double(i) + 0.5);
        sum += fx(x);
    }
    double pi=h*sum;
    printf("%24.16g",pi);
    return 0;
}