#include <iostream>
#include <vector>
using namespace std;

// 快速排序的分区函数（选择最后一个元素作为基准）
int partition(vector<int>& arr, int low, int high) {
  int pivot = arr[high];  // 选择第一个元素作为基准
  int i = low;            // i 指向小于基准的区域的下一个位置

  for (int j = low; j < high; ++j) {
    if (arr[j] < pivot) {
      swap(arr[i], arr[j]);  // 将小于基准的元素交换到左侧
                             // 扩大小于基准的区域
      ++i;
    }
  }
  swap(arr[i], arr[high]);  // 将基准元素放到正确的位置
  return i;                 // 返回基准元素的索引
}

// 快速排序的递归函数
void quickSort(vector<int>& arr, int low, int high) {
  if (low < high) {
    int pivotIndex = partition(arr, low, high);  // 分区操作
    quickSort(arr, low, pivotIndex - 1);         // 递归排序左侧子数组
    quickSort(arr, pivotIndex + 1, high);        // 递归排序右侧子数组
  }
}

int main() {
  vector<int> arr = {10, 7, 8, 9, 1, 5, 3, 7, 8};

  cout << "排序前的数组: ";
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;

  quickSort(arr, 0, arr.size() - 1);

  cout << "排序后的数组: ";
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;

  return 0;
}