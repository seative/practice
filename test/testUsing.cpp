template <typename T>
class parent
{
protected:
    double a;
};

// template <typename T>
class child : public parent<double> //<Derived>
{
    // using parent<Derived>::a;

public:
    void f1()
    {
        a = 2;
    }
};

int main()
{
    child dd;
}

// template <typename Derived>
// class parent
// {
// protected:
//     double a;
// };

// template <typename T>
// class child : public parent<child<T>>
// {
// public:
//     void f1()
//     {
//         a = 2;
//     }
// };

// int main()
// {
//     child<double> dd;
//     dd.f1();
//     return 0;
// }
