#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    static bool min_heap_comp(ListNode *l1, ListNode *l2) {
        return l1->val > l2->val;
    }
    
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode head(0), *ptr = &head;
        priority_queue<ListNode*, vector<ListNode*>, function<bool(ListNode*, ListNode*)>> min_heap(min_heap_comp);
        for  (auto list : lists) {
            if (list) {
                min_heap.push(list);
            }
        }
        while (!min_heap.empty()) {
            ListNode *min = min_heap.top();
            min_heap.pop();
            ptr->next = min;
            ptr = ptr->next;
            if (min->next) {
                min_heap.push(min->next);
            }
            min->next = nullptr;
        }
        return head.next;
    }
};

int main(int argc, char **argv)
{
	vector<ListNode*> lists;
  ListNode l1(1), l2(2), l3(3);
  l1.next = new ListNode(4); l1.next->next = new ListNode(7);
  l2.next = new ListNode(5); l2.next->next = new ListNode(8);
  l3.next = new ListNode(6); l3.next->next = new ListNode(9);
  lists.push_back(&l1);
  lists.push_back(&l2);
  lists.push_back(&l3);
  Solution s;
  ListNode *result = s.mergeKLists(lists);
  while (result) {
    cout << result->val << endl;
    result = result->next;
  }
  return 0;
}
