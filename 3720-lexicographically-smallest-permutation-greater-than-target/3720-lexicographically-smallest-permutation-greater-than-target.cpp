class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        for (int i = n - 1; i >= 0; i--) {
            vector<int> cnt(26);

            for (char c : s)
                cnt[c - 'a']++;

            bool possible = true;

            for (int j = 0; j < i; j++) {
                int x = target[j] - 'a';
                if (cnt[x] == 0) {
                    possible = false;
                    break;
                }
                cnt[x]--;
            }

            if (!possible) continue;

            int cur = target[i] - 'a';

            for (int c = cur + 1; c < 26; c++) {
                if (cnt[c] == 0) continue;

                string ans = target.substr(0, i);
                ans += char('a' + c);
                cnt[c]--;

                for (int x = 0; x < 26; x++)
                    ans += string(cnt[x], char('a' + x));

                return ans;
            }
        }

        return "";
    }
};