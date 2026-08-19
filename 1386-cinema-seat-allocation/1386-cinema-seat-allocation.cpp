class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        for (auto &s : reservedSeats) {
            int row = s[0];
            int seat = s[1];

            if (seat >= 2 && seat <= 9) {
                mp[row] |= (1 << (seat - 2));
            }
        }

        int ans = (n - mp.size()) * 2;

        for (auto &[row, mask] : mp) {
            bool left = !(mask & 0b00001111);
            bool middle = !(mask & 0b00111100);
            bool right = !(mask & 0b11110000);

            if (left && right) ans += 2;
            else if (left || middle || right) ans += 1;
        }

        return ans;
    }
};