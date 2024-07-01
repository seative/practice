// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

// 示例 1：

// 输入：head = [1,2,3,4,5]
// 输出：[5,4,3,2,1]
// 示例 2：

// 输入：head = [1,2]
// 输出：[2,1]
// 示例 3：

// 输入：head = []
// 输出：[]

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <cstddef>
#include <set>
#include <unordered_set>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;
    while (cur) {
      ListNode* temp = cur->next;
      cur->next = prev;
      prev = cur;
      cur = temp;
    }
    return prev;
  }
};
