class Solution:
    def lexicographicallySmallestArray(self, nums, limit):
        n = len(nums)
        arr = sorted((x, i) for i, x in enumerate(nums))
        
        groups = []
        current = []
        
        for i in range(n):
            if i == 0 or arr[i][0] - arr[i - 1][0] <= limit:
                current.append(arr[i])
            else:
                groups.append(current)
                current = [arr[i]]
        
        groups.append(current)
        
        ans = [0] * n
        
        for group in groups:
            values = sorted(x for x, _ in group)
            indices = sorted(i for _, i in group)
            
            for i in range(len(group)):
                ans[indices[i]] = values[i]
        
        return ans