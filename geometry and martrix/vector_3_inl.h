#ifndef VECTOR_3_INL_H_
#define VECTOR_3_INL_H_

#include "macros.h"
#include <algorithm>
#include <limits>
#include <tuple>

namespace test
{
    template <typename T>
    template <typename U>
    Vector<T, 3>::Vector(const std::initializer_list<U> lst)
    {
        set(lst);
    }

    template <typename T>
    void Vector<T, 3>::set(T s)
    {
        x = s;
        y = s;
        z = s;
    }

    template <typename T>
    void Vector<T, 3>::set(T newx, T newy, T newz)
    {
        x = newx;
        y = newy;
        z = newz;
    }

    // template <typename T>
    // void Vector<T, 3>::set(const Vector2<T> &pt, T newZ)
    // {
    //     x = pt.x;
    //     y = pt.y;
    //     z = newZ;
    // }

    template <typename T>
    template <typename U>
    void Vector<T, 3>::set(const std::initializer_list<U> &lst)
    {
        JET_ASSERT(lst.size() >= 3);
        auto inputElem = lst.begin();
        x = static_cast<T>(*inputElem);
        y = static_cast<T>(*(++inputElem));
        z = static_cast<T>(*(++inputElem));
    }

    template <typename T>
    void Vector<T, 3>::set(const Vector &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    template <typename T>
    void Vector<T, 3>::setZero()
    {
        x = y = z = 0;
    }

    template <typename T>
    void Vector<T, 3>::normalize()
    {
        T l = length();
        x /= l;
        y /= l;
        z /= l;
    }

    template <typename T>
    T Vector<T, 3>::length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
}
#endif