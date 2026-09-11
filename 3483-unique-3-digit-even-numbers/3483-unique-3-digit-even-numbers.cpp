class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int ans = 0;

        for (int a = 1; a <= 9; a++) {
            for (int b = 0; b <= 9; b++) {
                for (int c = 0; c <= 8; c += 2) {
                    vector<int> need = {a, b, c};
                    vector<int> cnt(10, 0), have(10, 0);

                    for (int d : digits) cnt[d]++;
                    for (int d : need) have[d]++;

                    bool ok = true;
                    for (int d = 0; d <= 9; d++) {
                        if (have[d] > cnt[d]) {
                            ok = false;
                            break;
                        }
                    }

                    if (ok) ans++;
                }
            }
        }

        return ans;
    }
};