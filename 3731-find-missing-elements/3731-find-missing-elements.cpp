class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mn = INT_MAX, mx = INT_MIN;
        unordered_set<int> st;

        for (int x : nums) {
            mn = min(mn, x);
            mx = max(mx, x);
            st.insert(x);
        }

        vector<int> ans;
        for (int i = mn + 1; i < mx; i++) {
            if (!st.count(i))
                ans.push_back(i);
        }

        return ans;
    }
};