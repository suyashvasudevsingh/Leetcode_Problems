class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        vector<int> best(n, INF);
        unordered_map<int, int> mp;
        mp[0] = -1;

        int sum = 0, ans = INF, minLen = INF;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (mp.count(sum - target)) {
                int j = mp[sum - target];
                int len = i - j;

                if (j >= 0 && best[j] != INF)
                    ans = min(ans, len + best[j]);

                minLen = min(minLen, len);
            }

            best[i] = minLen;
            mp[sum] = i;
        }

        return ans == INF ? -1 : ans;
    }
};