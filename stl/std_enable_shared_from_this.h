#include "std_shared_ptr.h"
#include "std_weak_ptr.h"

template <typename T> class enable_shared_from_this {
  shared_ptr<const T> shared_from_this() const {
    return shared_ptr<const T>(this->_M_weak_this);
  }

  mutable weak_ptr<T> _M_weak_this;
};