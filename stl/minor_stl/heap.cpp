#include <iostream>
#include <vector>

class BigHeap {
  std::vector<int> meta;

 public:
  BigHeap(const std::vector<int>& data) { make_heap(data); }

  void make_heap(const std::vector<int>& data) {
    meta.resize(0);
    for (auto& elem : data) {
      push_heap(elem);
    }
  }

  void push_heap(int d) {
    meta.push_back(d);
    int hole = meta.size() - 1;
    int parent = (hole - 1) / 2;

    while (hole > 0 && meta[parent] < meta[hole]) {
      std::swap(meta[parent], meta[hole]);
      hole = parent;
      parent = (hole - 1) / 2;
    }
  }

  int pop_heap() {
    int first = meta[0];
    meta[0] = meta.back();
    meta.pop_back();
    adjust_heap(0);  // 一个下朔过程
    return first;
  }

  std::vector<int> sort_heap() {
    std::vector<int> ans;
    while (!meta.empty()) {
      ans.push_back(pop_heap());
    }
    return ans;
  }

  void adjust_heap(size_t parent) {
    int current = parent;
    int child = 2 * parent + 1;

    while (child < meta.size()) {
      if (child + 1 < meta.size() && meta[child] < meta[child + 1]) {
        child++;
      }

      if (meta[current] >= meta[child]) break;

      std::swap(meta[parent], meta[child]);
      parent = child;
      child = child * 2 + 1;
    }
  }

  void print() {
    for (auto elem : meta) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  std::vector<int> t1{1, 2, 3, 4, 5};

  BigHeap h1(t1);
  h1.print();

  std::vector<int> oredered = h1.sort_heap();
  for (auto elem : oredered) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  //   for (int i = 0; i < 5; ++i) {
  //     int d = h1.pop_heap();
  //     std::cout << d << std::endl;
  //     h1.print();
  //   }
}