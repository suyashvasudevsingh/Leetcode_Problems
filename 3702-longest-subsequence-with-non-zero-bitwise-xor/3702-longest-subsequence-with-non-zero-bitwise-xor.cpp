class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int xr = 0, zero = 0;
        
        for (int x : nums) {
            xr ^= x;
            if (x == 0) zero++;
        }
        
        int n = nums.size();
        
        if (xr != 0) return n;
        if (zero == n) return 0;
        
        return n - 1;
    }
};