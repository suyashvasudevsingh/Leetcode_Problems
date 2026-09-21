class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k), ndp(k);

        for (int x : nums) {
            fill(ndp.begin(), ndp.end(), 0);

            int r = x % k;

            ndp[r]++;

            for (int j = 0; j < k; j++) {
                if (dp[j]) {
                    ndp[(j * 1LL * r) % k] += dp[j];
                }
            }

            for (int j = 0; j < k; j++) {
                ans[j] += ndp[j];
            }

            dp.swap(ndp);
        }

        return ans;
    }
};