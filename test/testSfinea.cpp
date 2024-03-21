#include <iostream>

using namespace std;

class A
{
public:
    int operator()() { return 1; }
};

template <typename, typename = bool>
constexpr bool has_func_v = false;

template <typename T>
constexpr bool has_func_v<T, decltype(std::declval<T>().operator()())> = true;

// template <typename T, typename U, typename BoolType = std::true_type>
// class Add;

// template <typename T, typename U>
// struct Add<T, U, std::integral_constant<bool, std::is_base_of<T, U>::value>>
// {
// };

// template <typename T, typename U>
// struct Add<T, U, std::integral_constant<bool, !std::is_base_of<T, U>::value>>
// {
// };

// template <typename T, typename U, bool NeeeDerivedType = true>
// class Add;

// template <typename T, typename U>
// class Add<T, U, std::is_base_of<T, U>::value>
// {
//     部分专用化的模板实参列表包含类型取决于模板形参的非类型实参C
// };
template <typename T, typename E1, typename E2, typename E3>
struct Vector
{
    E1 x;
    E2 y;
    E3 z;
};

// template <typename T>
// Vector<T, T, T> vec(const typename std::enable_if_t<std::is_floating_point_v<T>, T> &u,
//                     const typename std::enable_if_t<std::is_floating_point_v<T>, T> &v,
//                     const typename std::enable_if_t<std::is_floating_point_v<T>, T> &w)
// {
//     return Vector<T, T, T>{u, v, w};
// }

template <typename E1, typename E2, typename E3>
decltype(auto) vec(E1 u, E2 v, E3 w)
{

    return Vector<std::enable_if_t<std::is_floating_point_v<E1>, E1>, E1, E2, E3>{u, v, w};
}

int main()
{
    cout << has_func_v<A> << endl;

    vec(1.5, 2.5, 3.5);
    // Add<int, float> b; // ??
    return 0;
}