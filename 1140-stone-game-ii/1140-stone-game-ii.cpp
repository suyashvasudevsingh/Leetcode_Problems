class Solution {
public:
    int n;
    vector<int> piles;
    int dp[105][105];

    int solve(int i, int m) {
        if (i >= n) return 0;

        if (dp[i][m] != -1)
            return dp[i][m];

        int sum = 0;
        int ans = INT_MIN;

        for (int x = 1; x <= 2 * m && i + x <= n; x++) {
            sum += piles[i + x - 1];
            ans = max(ans, sum - solve(i + x, max(m, x)));
        }

        return dp[i][m] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        this->piles = piles;
        n = piles.size();

        memset(dp, -1, sizeof(dp));

        int total = accumulate(piles.begin(), piles.end(), 0);
        int diff = solve(0, 1);

        return (total + diff) / 2;
    }
};