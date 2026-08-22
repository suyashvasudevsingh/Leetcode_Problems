class Solution {
public:
    long long gcdll(long long a, long long b) {
        return b ? gcdll(b, a % b) : a;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        vector<pair<long long, int>> subsets;

        for (int mask = 1; mask < (1 << n); mask++) {
            long long l = 1;
            bool ok = true;

            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    long long g = gcdll(l, coins[i]);
                    long long nxt = l / g * coins[i];
                    if (nxt > 4e18) {
                        ok = false;
                        break;
                    }
                    l = nxt;
                }
            }

            if (ok) {
                int bits = __builtin_popcount(mask);
                subsets.push_back({l, bits & 1 ? 1 : -1});
            }
        }

        auto count = [&](long long x) {
            long long res = 0;
            for (auto& [lcm, sign] : subsets) {
                res += sign * (x / lcm);
            }
            return res;
        };

        long long lo = 1, hi = 1e18;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (count(mid) >= k) hi = mid;
            else lo = mid + 1;
        }

        return lo;
    }
};