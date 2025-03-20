#include <atomic>
#include <iostream>
#include <memory>

namespace minor_stl {

class SpCountBase {
  std::atomic<int> use_count;
  std::atomic<int> weak_count;

 public:
  SpCountBase() : use_count(1), weak_count(1) {}

  int get_use_count() { return use_count; }

  void add_ref_copy() { ++use_count; }

  void release() {
    if (--use_count == 0) {
      dispose();
      if (--weak_count == 0) {
        destroy();
      }
    }
  }

  virtual void dispose() = 0;
  virtual void destroy() = 0;
};

template <typename T>
class SpCountPtr : public SpCountBase {
  T* ptr;

 public:
  SpCountPtr(T* p) : ptr(p) {}

  void dispose() override { delete ptr; }

  void destroy() override { delete this; }
};

template <typename T>
class shared_ptr {
  SpCountBase* count;
  T* ptr;

 public:
  shared_ptr(T* p) : ptr(p), count(new SpCountPtr<T>(p)) {}

  ~shared_ptr() {
    if (count != nullptr) {
      count->release();
    }
  }

  shared_ptr(const shared_ptr& other) {
    if (other.count != nullptr) {
      ptr = other.ptr;
      count = other.count;
      count->add_ref_copy();
    }
  }

  shared_ptr& operator=(const shared_ptr& other) {
    if (count != other.count) {
      if (count != nullptr) {
        count->release();
      }
      ptr = other.ptr;
      count = other.count;
      if (count != nullptr) {
        count->add_ref_copy();
      }
    }
    return *this;
  }

  T* get() { return ptr; }

  T& operator*() { return *ptr; };

  T* operator->() { return ptr; };

  int use_count() { return count->get_use_count(); }
};
}  // namespace minor_stl
