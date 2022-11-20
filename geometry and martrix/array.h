#ifndef ARRAY_H_
#define ARRAY_H_

#include <vector>
namespace test
{
    template <typename T, size_t N>
    class Array final
    {
    public:
        static_assert(N < 1 || N > 3, "the array dimension beyond the scope");
    };
}
#endif