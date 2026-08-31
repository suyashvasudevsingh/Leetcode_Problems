class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};
        int first = -1, last = -1, prev = -1;
        int pos = 1;

        while (head && head->next && head->next->next) {
            int a = head->val;
            int b = head->next->val;
            int c = head->next->next->val;

            if ((b > a && b > c) || (b < a && b < c)) {
                if (first == -1) {
                    first = pos;
                } else {
                    if (ans[0] == -1)
                        ans[0] = pos - last;
                    else
                        ans[0] = min(ans[0], pos - last);
                }
                last = pos;
            }

            head = head->next;
            pos++;
        }

        if (first != -1 && first != last)
            ans[1] = last - first;

        return ans;
    }
};