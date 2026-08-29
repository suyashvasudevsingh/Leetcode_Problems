class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<pair<int, int>> a(n);

        for (int i = 0; i < n; ++i)
            a[i] = {nums[i], i};

        sort(a.begin(), a.end());

        vector<int> ans(n);

        int i = 0;
        while (i < n) {
            int j = i;

            while (j + 1 < n &&
                   (long long)a[j + 1].first - a[j].first <= limit) {
                ++j;
            }

            vector<int> indices;

            for (int k = i; k <= j; ++k)
                indices.push_back(a[k].second);

            sort(indices.begin(), indices.end());

            for (int k = 0; k < (int)indices.size(); ++k)
                ans[indices[k]] = a[i + k].first;

            i = j + 1;
        }

        return ans;
    }
};