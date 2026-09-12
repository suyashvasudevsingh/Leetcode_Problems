class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<int> id(n);
        iota(id.begin(), id.end(), 0);

        sort(id.begin(), id.end(), [&](int a, int b) {
            return intervals[a][0] < intervals[b][0];
        });

        vector<int> start(n);
        for (int i = 0; i < n; i++)
            start[i] = intervals[id[i]][0];

        vector<vector<pair<long long, vector<int>>>> dp(n + 1,
            vector<pair<long long, vector<int>>>(5));

        for (int i = n - 1; i >= 0; i--) {
            int idx = id[i];
            int r = intervals[idx][1];
            long long w = intervals[idx][2];

            int nxt = upper_bound(start.begin(), start.end(), r) - start.begin();

            for (int k = 1; k <= 4; k++) {
                dp[i][k] = dp[i + 1][k];

                long long score = w + dp[nxt][k - 1].first;
                vector<int> cur = dp[nxt][k - 1].second;
                cur.push_back(idx);
                sort(cur.begin(), cur.end());

                if (score > dp[i][k].first ||
                    (score == dp[i][k].first && cur < dp[i][k].second)) {
                    dp[i][k] = {score, cur};
                }
            }
        }

        return dp[0][4].second;
    }
};