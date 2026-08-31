class Solution:
    def minimumDeletions(self, nums):
        n = len(nums)
        mn = nums.index(min(nums))
        mx = nums.index(max(nums))

        a = min(mn, mx)
        b = max(mn, mx)

        return min(b + 1, n - a, a + 1 + n - b)