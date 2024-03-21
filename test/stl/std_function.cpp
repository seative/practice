#include "stdio.h"
#include "iostream"
#include <type_traits>
#include <functional>
#include <memory>

using namespace std;

template <class Fnsig>
struct Function
{
    static_assert(std::is_same_v<Fnsig, Fnsig>, "not a valid function signature");
};

template <class Ret, class... Args>
struct Function<Ret(Args...)>
{
    struct Funcbase
    {
        virtual Ret call(Args... args) = 0;
        virtual ~Funcbase() = default;
    };

    template <class F>
    struct FuncImpl : Funcbase
    {
        F f;
        FuncImpl(F f) : f(std::move(f)) {}
        virtual Ret call(Args... args) override
        {
            return std::invoke(f, std::forward<Args>(args)...);
        }
    };

    std::shared_ptr<Funcbase> m_base;
    Function() = default;

    template <class F>
        requires(std::__is_invocable_r_v<Ret, F, Args...> && !std::is_same_v<std::decay_t<F>, Function>)
    Function(F, f) : m_base(std::make_shared<FuncImpl<F>>(std::move(f)))
    {
    }

    Ret operator()(Args... args) const
    {
        if (!m_base) [[unlikely]]
            throw std::runtime_error("function uninitialized");
        return m_base->call(std::forward<Args>(args)...);
    }
};

typedef void (*pfunc)();

void func_hello()
{
    printf("Hello\n");
}

struct printnum_test_t
{
    int &x;
    int &y;
    void operator()() const
    {
        printf("%d,%d\n", x, y);
    }
};

// void func_printnum(pfunc func)
// {
//     func();
// }

void repeattwice(const std::function<void(void)> &fn)
{
    fn();
    fn();
}

int main()
{
    int x;
    int y;
    std::cin >> x >> y;
    const printnum_test_t a{x, y};
    pfunc pf1 = func_hello;
    // pfunc pf2 = func_printnum;
    repeattwice(a);
    std::cin >> x >> y;
    // a.x = x;
    // a.y = y;
    repeattwice(a);
    repeattwice(pf1);
    repeattwice([&x, &y]()
                { printf("numbers are: %d, %d\n", x, y); });
}