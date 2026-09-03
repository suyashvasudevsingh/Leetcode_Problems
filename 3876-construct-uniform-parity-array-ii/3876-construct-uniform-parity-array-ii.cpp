class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        bool hasOdd = false;
        bool hasEven = false;
        int mn = *min_element(nums1.begin(), nums1.end());

        for (int x : nums1) {
            if (x % 2 == 0)
                hasEven = true;
            else
                hasOdd = true;
        }

        // All elements already have the same parity
        if (!hasOdd || !hasEven)
            return true;

        // Mixed parity: possible only if minimum is odd
        return mn % 2 == 1;
    }
};