
'''
5. Longest Palindromic Substring
'''
# 暴力搜索(超时)
def longestPalindrome(self, s: str) -> str:
    res = ''
    best = 0
    for i in range(len(s)):
        for j in range(i, len(s)):
            if isPalindrome(s[i:j + 1]):
                if (best < j - i + 1):
                    best = j - i + 1
                    res = s[i:j + 1]
    return res


def isPalindrome(s):
    if len(s)==1:
        return True
    elif len(s) == 2:
        return s[0] == s[1]
    return s[0] == s[-1] and isPalindrome(s[1:-1])

# 动态规划
def longestPalindrome_dp(s):
    n = len(s)
    table = [[False] * n for i in range(n)]
    ans = ''
    maxlen = 0
    # 一字母回文
    for i in range(n):
        table[i][i] = True
        maxlen = 1
        ans = s[i]
    # 二字母回文
    for i in range(n-1):
        if s[i] == s[i + 1]:
            table[i][i + 1] = True
            maxlen = 2
            ans = s[i:i + 2]
    # 三字母，四字母....
    for j in range(2, n):
        for i in range(n - j):
            if table[i + 1][i + j - 1] and s[i] == s[i + j]:
                table[i][i + j] = True
                if maxlen < j+1:
                    maxlen = j+1
                    ans = s[i:i + j + 1]
    return ans