#include <cstddef>
#include <set>
#include <unordered_set>

#include "cstdio"

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};
struct compFunc {
  bool operator()(ListNode* a, ListNode* b) const { return a->val < b->val; }
};

class Solution {
 public:
  ListNode* sortList(ListNode* head) {
    std::set<ListNode*, compFunc> s;
    while (head != nullptr) {
      s.insert(head);
      head = head->next;
    }
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    for (auto it : s) {
      cur->next = it;
      cur = cur->next;
    }
    return dummy->next;
  }
};

class Solution2 {
 public:
  ListNode* sortList(ListNode* head) { return sortList(head, nullptr); }

  ListNode* sortList(ListNode* head, ListNode* tail) {
    if (head == nullptr) {
      return head;
    }
    if (head->next == tail) {
      head->next = nullptr;
      return head;
    }
    ListNode *slow = head, *fast = head;
    while (fast != tail) {
      slow = slow->next;
      fast = fast->next;
      if (fast != tail) {
        fast = fast->next;
      }
    }
    ListNode* mid = slow;
    return merge(sortList(head, mid), sortList(mid, tail));
  }

  ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode* preHead = new ListNode(-1);

    ListNode* prev = preHead;
    while (l1 != nullptr && l2 != nullptr) {
      if (l1->val < l2->val) {
        prev->next = l1;
        l1 = l1->next;
      } else {
        prev->next = l2;
        l2 = l2->next;
      }
      prev = prev->next;
    }
    prev->next = l1 == nullptr ? l2 : l1;

    return preHead->next;
  }
};

// int main() {
//   Solution ans;
//   ListNode* head = new ListNode(4);
//   head->next = new ListNode(2);
//   head->next->next = new ListNode(1);
//   head->next->next->next = new ListNode(3);

//   auto res = ans.sortList(head);

//   printf("res: %i, %i, %i, %i", res->val, res->next->val,
//   res->next->next->val,
//          res->next->next->next->val);
// }