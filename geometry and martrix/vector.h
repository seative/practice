#ifndef VECTOR_H_
#define VECTOR_H_

#include <array>
#include "type_helpers.h"

namespace test
{
    template <typename T, size_t N>
    class Vector final
    {
    public:
        static_assert(N > 0, "size of vector should be greater than zero");
        static_assert(std::is_floating_point<T>::value, "vector onle be instanced with floating point types");
        typedef std::array<T, N> ContainerType;
        //构造函数
        Vector();

        template <typename... Params>
        explicit Vector(Params... params);

        void set(const T &s);

        template <typename U>
        Vector(const std::initializer_list<U> &lst);

        // template <typename E>
        // Vector(const VectorExpression<T, E> &other);

        Vector(const Vector &other);
    };
}
#endif