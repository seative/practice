
template <typename T>
class A
{
    // template <typename U>
    // friend class VectorCpu;
    friend void foo();

public:
    int a = 5;
};

int main()
{
    A<int> a;
}