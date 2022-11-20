#ifndef TYPE_HELPERS_H_
#define TYPE_HELPERS_H_

namespace test
{
    template <typename T>
    struct ScalarType
    {
        typedef T value;
    };
}

#endif