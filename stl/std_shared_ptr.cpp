#include <atomic>
#include <iostream>

class Sp_counted_base {
  std::atomic<long> use_count;
  std::atomic<long> weak_count;

 public:
  Sp_counted_base() : weak_count(1), use_count(1) {}

  Sp_counted_base(const Sp_counted_base &other) = delete;

  long get_use_count() { return use_count; }

  void weak_release() {
    if (--weak_count == 0) destroy();
  }

  void weak_add_ref() { ++weak_count; }

  void release() {
    if (--use_count == 0) {
      dispose();
      if (--weak_count == 0) {
        destroy();
      }
    }
  };

  void add_ref_copy() { ++use_count; }

  virtual void destroy(){};
  virtual void dispose(){};
};

template <typename T>
class Sp_counted_ptr : public Sp_counted_base {
  T *ptr;

 public:
  Sp_counted_ptr(T *pointer) : Sp_counted_base(), ptr(pointer) {}
  virtual void dispose() { delete ptr; }
  virtual void destroy() { delete this; };
};

class Shared_count {
  Sp_counted_base *pi;

 public:
  Shared_count() = default;

  template <typename T>
  Shared_count(T *pointer) {
    pi = new Sp_counted_ptr<T>(pointer);
  }

  Shared_count(const Shared_count &other) : pi(other.pi) {
    if (pi != nullptr) pi->add_ref_copy();
  }

  Shared_count &operator=(const Shared_count &other) {
    Sp_counted_base *temp = other.pi;
    if (temp != pi) {
      if (temp != nullptr) temp->add_ref_copy();

      if (pi != nullptr) pi->release();

      pi = temp;
    }
    return *this;
  }

  long use_count() { return pi->get_use_count(); }

  ~Shared_count() {
    if (pi != nullptr) pi->release();
  }
};

template <typename T>
class _shared_ptr {
  T *ptr;
  Shared_count refCount;

 public:
  _shared_ptr() : ptr(nullptr), refCount() {}

  _shared_ptr(T *pointer) : ptr(pointer), refCount(pointer) {}

  _shared_ptr(const _shared_ptr &other)
      : refCount(other.refCount), ptr(other.pointer) {}

  _shared_ptr &operator=(const _shared_ptr &other) {
    this->ptr = other.ptr;
    this->refCount = other.refCount;
    return *this;
  }

  long use_count() { return refCount.use_count(); }
  T *get() { return ptr; }
};

template <typename T>
class shared_ptr : public _shared_ptr<T> {
 public:
  // construct
  shared_ptr() noexcept = default;
  shared_ptr(std::nullptr_t) noexcept {}
  shared_ptr(T *pointer) : _shared_ptr<T>(pointer) {}

  // copy construct
  shared_ptr(const shared_ptr &other) : _shared_ptr<T>(other) {}

  // operator =
  shared_ptr &operator=(const shared_ptr &other) {
    this->_shared_ptr<T>::operator=(other);
    return *this;
  }
};

int main() {
  shared_ptr<int> a(new int(1));
  shared_ptr<int> b(new int(2));
  shared_ptr<int> c(new int(2));

  shared_ptr<int> d;
  // std::cout << d.use_count() << "\n";

  a = b;
  a = c;
  std::cout << a.use_count() << "\n";
  std::cout << b.use_count() << "\n";
  d = a;
  std::cout << a.use_count() << "\n";
  std::cout << d.use_count() << "\n";
  return 0;
}
