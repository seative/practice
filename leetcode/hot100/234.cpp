// 给你一个单链表的头节点 head ，请你判断该链表是否为
// 回文链表
// 。如果是，返回 true ；否则，返回 false 。

// 示例 1：

// 输入：head = [1,2,2,1]
// 输出：true
// 示例 2：

// 输入：head = [1,2]
// 输出：false

// 提示：

// 链表中节点数目在范围[1, 105] 内
// 0 <= Node.val <= 9

// 进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
#include <vector>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  bool isPalindrome(ListNode* head) {
    vector<int> vals;
    while (head != nullptr) {
      vals.emplace_back(head->val);
      head = head->next;
    }
    for (int i = 0, j = (int)vals.size() - 1; i < j; ++i, --j) {
      if (vals[i] != vals[j]) {
        return false;
      }
    }
    return true;
  }
};

class Solution1 {
  ListNode* frontPointer;

 public:
  bool recursivelyCheck(ListNode* currentNode) {
    if (currentNode != nullptr) {
      if (!recursivelyCheck(currentNode->next)) {
        return false;
      }
      if (currentNode->val != frontPointer->val) {
        return false;
      }
      frontPointer = frontPointer->next;
    }
    return true;
  }

  bool isPalindrome(ListNode* head) {
    frontPointer = head;
    return recursivelyCheck(head);
  }
};

class Solution2 {
 public:
  bool isPalindrome(ListNode* head) {
    if (head == nullptr) {
      return true;
    }

    // 找到前半部分链表的尾节点并反转后半部分链表
    ListNode* firstHalfEnd = endOfFirstHalf(head);
    ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

    // 判断是否回文
    ListNode* p1 = head;
    ListNode* p2 = secondHalfStart;
    bool result = true;
    while (result && p2 != nullptr) {
      if (p1->val != p2->val) {
        result = false;
      }
      p1 = p1->next;
      p2 = p2->next;
    }

    // 还原链表并返回结果
    firstHalfEnd->next = reverseList(secondHalfStart);
    return result;
  }

  ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr != nullptr) {
      ListNode* nextTemp = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nextTemp;
    }
    return prev;
  }

  ListNode* endOfFirstHalf(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return slow;
  }
};