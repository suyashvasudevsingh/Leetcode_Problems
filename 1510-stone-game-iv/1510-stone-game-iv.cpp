class Solution {
public:
    int dp[100005];

    bool solve(int n) {
        if (n == 0) return false;
        if (dp[n] != -1) return dp[n];

        for (int i = 1; i * i <= n; i++) {
            if (!solve(n - i * i))
                return dp[n] = true;
        }

        return dp[n] = false;
    }

    bool winnerSquareGame(int n) {
        memset(dp, -1, sizeof(dp));
        return solve(n);
    }
};