class Solution {
public:
    vector<string> ans;

    void dfs(string s, int start, int lrem, int rrem) {
        if (lrem == 0 && rrem == 0) {
            int bal = 0;
            for (char c : s) {
                if (c == '(') bal++;
                else if (c == ')') {
                    if (--bal < 0) return;
                }
            }
            if (bal == 0) ans.push_back(s);
            return;
        }

        for (int i = start; i < s.size(); i++) {
            if (i > start && s[i] == s[i - 1]) continue;

            if (lrem + rrem > s.size() - i) return;

            if (lrem > 0 && s[i] == '(') {
                dfs(s.substr(0, i) + s.substr(i + 1), i, lrem - 1, rrem);
            }

            if (rrem > 0 && s[i] == ')') {
                dfs(s.substr(0, i) + s.substr(i + 1), i, lrem, rrem - 1);
            }
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        int lrem = 0, rrem = 0;

        for (char c : s) {
            if (c == '(') {
                lrem++;
            } else if (c == ')') {
                if (lrem > 0)
                    lrem--;
                else
                    rrem++;
            }
        }

        dfs(s, 0, lrem, rrem);
        return ans;
    }
};