// 给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。

// 示例 1：

// 输入：head = [1,2,3,4,5], k = 2
// 输出：[4,5,1,2,3]
// 示例 2：

// 输入：head = [0,1,2], k = 4
// 输出：[2,0,1]

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (!head)
            return nullptr;
        int i = 0;
        ListNode *temp;
        ListNode *head2 = head;
        while (head)
        {
            temp = head;
            head = head->next;
            ++i;
        }
        temp->next = head2;

        for (int j = 0; j < i - k % i; ++j)
        {
            temp = head2;
            head2 = head2->next;
        }
        temp->next = nullptr;
        return head2;
    }
};