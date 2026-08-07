#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    // Factor counts contributed by each digit from 0 to 9
    const int f2[10] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
    const int f3[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
    const int f5[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    const int f7[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};

    // Helper to calculate minimum number of digits needed for required prime factors
    int minDigits(long long c2, long long c3, long long c5, long long c7) {
        c2 = max(0LL, c2);
        c3 = max(0LL, c3);
        c5 = max(0LL, c5);
        c7 = max(0LL, c7);

        int count = c7 + c5 + c3 / 2 + c2 / 3;
        int rem3 = c3 % 2;
        int rem2 = c2 % 3;

        if (rem3 == 1 && rem2 == 1) {
            count += 1; // '6'
        } else if (rem3 == 1 && rem2 == 2) {
            count += 2; // e.g., '2' and '6' or '3' and '4'
        } else if (rem3 == 1 && rem2 == 0) {
            count += 1; // '3'
        } else if (rem3 == 0 && rem2 == 2) {
            count += 1; // '4'
        } else if (rem3 == 0 && rem2 == 1) {
            count += 1; // '2'
        }
        return count;
    }

public:
    string smallestNumber(string num, long long t) {
        // Step 1: Prime factorize t
        long long c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        while (t % 2 == 0) { c2++; t /= 2; }
        while (t % 3 == 0) { c3++; t /= 3; }
        while (t % 5 == 0) { c5++; t /= 5; }
        while (t % 7 == 0) { c7++; t /= 7; }

        // If t has prime factors > 7, it's impossible
        if (t > 1) return "-1";

        int n = num.size();

        // Find the index of the first '0' if any
        int limit = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                limit = i;
                break;
            }
        }

        // Precompute remaining required factor counts along the prefix of num
        vector<long long> req2(limit + 1), req3(limit + 1), req5(limit + 1), req7(limit + 1);
        req2[0] = c2; req3[0] = c3; req5[0] = c5; req7[0] = c7;

        for (int i = 0; i < limit; ++i) {
            int d = num[i] - '0';
            req2[i + 1] = max(0LL, req2[i] - f2[d]);
            req3[i + 1] = max(0LL, req3[i] - f3[d]);
            req5[i + 1] = max(0LL, req5[i] - f5[d]);
            req7[i + 1] = max(0LL, req7[i] - f7[d]);
        }

        // Check if `num` itself is valid
        if (limit == n && req2[n] == 0 && req3[n] == 0 && req5[n] == 0 && req7[n] == 0) {
            return num;
        }

        // Step 2: Search for the longest valid prefix of length n
        int start_i = min(limit, n - 1);
        for (int i = start_i; i >= 0; --i) {
            int start_d = (i < limit) ? (num[i] - '0' + 1) : 1;
            for (int d = start_d; d <= 9; ++d) {
                long long rem_c2 = max(0LL, req2[i] - f2[d]);
                long long rem_c3 = max(0LL, req3[i] - f3[d]);
                long long rem_c5 = max(0LL, req5[i] - f5[d]);
                long long rem_c7 = max(0LL, req7[i] - f7[d]);

                int rem_len = n - 1 - i;
                if (minDigits(rem_c2, rem_c3, rem_c5, rem_c7) <= rem_len) {
                    // Valid configuration found! Construct string of length n
                    string res = num.substr(0, i);
                    res += to_string(d);

                    // Greedily fill remaining suffix
                    for (int pos = i + 1; pos < n; ++pos) {
                        for (int cand = 1; cand <= 9; ++cand) {
                            long long next_c2 = max(0LL, rem_c2 - f2[cand]);
                            long long next_c3 = max(0LL, rem_c3 - f3[cand]);
                            long long next_c5 = max(0LL, rem_c5 - f5[cand]);
                            long long next_c7 = max(0LL, rem_c7 - f7[cand]);

                            if (minDigits(next_c2, next_c3, next_c5, next_c7) <= n - 1 - pos) {
                                res += to_string(cand);
                                rem_c2 = next_c2;
                                rem_c3 = next_c3;
                                rem_c5 = next_c5;
                                rem_c7 = next_c7;
                                break;
                            }
                        }
                    }
                    return res;
                }
            }
        }

        // Step 3: No valid number of length n, construct for length L > n
        int target_len = max((long long)n + 1, (long long)minDigits(c2, c3, c5, c7));
        string res = "";
        long long rem_c2 = c2, rem_c3 = c3, rem_c5 = c5, rem_c7 = c7;

        for (int pos = 0; pos < target_len; ++pos) {
            for (int cand = 1; cand <= 9; ++cand) {
                long long next_c2 = max(0LL, rem_c2 - f2[cand]);
                long long next_c3 = max(0LL, rem_c3 - f3[cand]);
                long long next_c5 = max(0LL, rem_c5 - f5[cand]);
                long long next_c7 = max(0LL, rem_c7 - f7[cand]);

                if (minDigits(next_c2, next_c3, next_c5, next_c7) <= target_len - 1 - pos) {
                    res += to_string(cand);
                    rem_c2 = next_c2;
                    rem_c3 = next_c3;
                    rem_c5 = next_c5;
                    rem_c7 = next_c7;
                    break;
                }
            }
        }

        return res;
    }
};