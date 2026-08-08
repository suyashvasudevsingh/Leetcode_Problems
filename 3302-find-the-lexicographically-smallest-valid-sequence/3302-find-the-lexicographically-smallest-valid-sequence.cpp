class Solution {
public:
    vector<int> validSequence(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<int> ans(m);

        // last[i] = position in word1 from where
        // word2[i...] can be matched
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // Find latest possible matching positions
        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        // One mismatch is allowed
        bool usedMismatch = false;

        j = 0;

        for (i = 0; i < n && j < m; i++) {

            // Normal matching character
            if (word1[i] == word2[j]) {
                ans[j] = i;
                j++;
            }

            // Use our one allowed mismatch
            else if (!usedMismatch &&
                     (j == m - 1 || i < last[j + 1])) {

                ans[j] = i;
                j++;
                usedMismatch = true;
            }
        }

        // Could not match all characters
        if (j != m)
            return {};

        return ans;
    }
};