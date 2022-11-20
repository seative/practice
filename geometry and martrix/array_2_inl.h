#ifndef ARRAY_2_INL_H
#define ARRAY_2_INL_H
#include <vector>
#include <cmath>
#include "macros.h"

namespace test
{
    template <typename T>
    Array<T, 2>::Array(){};

    template <typename T>
    Array<T, 2>::Array(const Size2 &size, const T &initval)
    {
        resize(size, initval);
    }

    template <typename T>
    Array<T, 2>::Array(size_t width, size_t height, const T &initval)
    {
        resize(width, height, initval);
    }

    template <typename T>
    Array<T, 2>::Array(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        set(lst);
    }

    template <typename T>
    Array<T, 2>::Array(const Array &other)
    {
        set(other);
    }

    template <typename T>
    Array<T, 2>::Array(Array &&other)
    {
        (*this) = std::move(other);
    }

    template <typename T>
    void Array<T, 2>::set(const T &value)
    {
        for (auto &c : _data)
            c = value;
    }

    template <typename T>
    void Array<T, 2>::set(const Array &other)
    {
        _data.resize(other._data.size());
        std::copy(other._data.begin(), other._data.end(), _data.begin());
        _size = other._size;
    }

    template <typename T>
    void Array<T, 2>::set(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        size_t height = lst.size();
        size_t width = (height > 0) ? lst.begin()->size() : 0;
        resize(Size2{width, height});
        auto rowiter = lst.begin();
        for (size_t j = 0; j < height; ++j)
        {
            auto coliter = rowiter->begin();
            JET_ASSERT(width == rowiter->size());
            for (size_t i = 0; i < width; ++i)
            {
                (*this)(i, j) = *coliter;
                ++coliter;
            }
            ++rowiter;
        }
    }

    template <typename T>
    void Array<T, 2>::clear()
    {
        _data.clear();
        _size = Size2{0, 0};
    }

    template <typename T>
    void Array<T, 2>::resize(const Size2 &size, const T &initvalue)
    {
        // _size.x = size.x;
        // _size.y = size.y;
        // size_t total = _size.x * _size.y;
        // for (auto c : total)
        //     _data.push_back(T);

        Array grid;
        grid._data.resize(size.x * size.y, initvalue);
        grid._size = size;
        size_t imin = std::min(_size.x, size.x);
        size_t jmin = std::min(_size.y, size.y);
        for (size_t j = 0; j < jmin; ++j)
        {
            for (size_t i = 0; i < imin; ++i)
            {
                grid(i, j) = at(i, j);
            }
        }
        swap(grid);
    }

    template <typename T>
    void Array<T, 2>::resize(size_t width, size_t height, const T &initval)
    {
        resize(Size2(width, height), initval);
    }

    template <typename T>
    T &Array<T, 2>::at(size_t i)
    {
        JET_ASSERT(i < _size.x * _size.y);
        return _data[i];
    }

    template <typename T>
    const T &Array<T, 2>::at(size_t i) const
    {
        JET_ASSERT(i < _size.x * _size.y);
        return _data[i];
    }

    template <typename T>
    T &Array<T, 2>::at(size_t i, size_t j)
    {
        JET_ASSERT(i < _size.x && j < _size.y);
        return _data[i + _size.x * j];
    }

    template <typename T>
    const T &Array<T, 2>::at(size_t i, size_t j) const
    {
        JET_ASSERT(i < _size.x && j < _size.y);
        return _data[i + _size.x * j];
    }

    template <typename T>
    Size2 Array<T, 2>::size() const
    {
        return _size;
    }

    template <typename T>
    size_t Array<T, 2>::width() const
    {
        return _size.x;
    }

    template <typename T>
    size_t Array<T, 2>::height() const
    {
        return _size.y;
    }

    template <typename T>
    T *Array<T, 2>::data()
    {
        return _data.data();
    }

    template <typename T>
    const T *const Array<T, 2>::data() const
    {
        return _data.data();
    }

    template <typename T>
    typename Array<T, 2>::Iterator Array<T, 2>::begin()
    {
        return _data.begin();
    }

    template <typename T>
    typename Array<T, 2>::ConstIterator Array<T, 2>::begin() const
    {
        return _data.cbegin();
    }

    template <typename T>
    typename Array<T, 2>::Iterator Array<T, 2>::end()
    {
        return _data.end();
    }

    template <typename T>
    typename Array<T, 2>::ConstIterator Array<T, 2>::end() const
    {
        return _data.cend();
    }

    template <typename T>
    void Array<T, 2>::swap(Array &other)
    {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
    }

    template <typename T>
    T &Array<T, 2>::operator()(size_t i, size_t j)
    {
        JET_ASSERT(i < _size.x && j < _size.y);
        return _data[i + _size.x * j];
    }
}

#endif