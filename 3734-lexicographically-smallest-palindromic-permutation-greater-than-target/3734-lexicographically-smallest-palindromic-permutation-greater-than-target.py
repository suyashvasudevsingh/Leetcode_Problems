class Solution:
    def lexPalindromicPermutation(self, s, target):
        n = len(s)
        cnt = [0] * 26

        for ch in s:
            cnt[ord(ch) - 97] += 1

        mid = ""

        for i in range(26):
            if cnt[i] % 2:
                if mid:
                    return ""
                mid = chr(i + 97)

        half = n // 2
        left = [0] * 26

        for i in range(26):
            left[i] = cnt[i] // 2

        prefix = []

        def possible():
            temp = prefix[:]

            for i in range(25, -1, -1):
                temp += [chr(i + 97)] * left[i]

            x = ''.join(temp)
            p = x + mid + x[::-1]

            return p > target

        for i in range(half):
            found = False

            for c in range(26):
                if left[c] == 0:
                    continue

                left[c] -= 1
                prefix.append(chr(c + 97))

                if possible():
                    found = True
                    break

                prefix.pop()
                left[c] += 1

            if not found:
                return ""

        x = ''.join(prefix)
        ans = x + mid + x[::-1]

        if ans > target:
            return ans

        return ""