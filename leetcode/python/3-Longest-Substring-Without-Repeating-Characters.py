
'''
3. Longest Substring Without Repeating Characters
substring是连续的
e.g. pwwkew=>wke
'''
def lengthOfLongestSubstring(s):
    if len(s)==0:
        return 0
    l,r = 0,1
    res = 1
    while r < len(s):
        if s[r] in s[l:r]:
            while s[l] != s[r]:
                l += 1
            l += 1
        else:
            res = max(res, r - l + 1)
        r += 1
    return res

def lengthOfLongSubstring(s):
    l, r = 0, -1 #sliding window s[l...r]
    last = {}
    res = 0
    while r + 1 < len(s):
        r += 1
        if s[r] in last:
            l = max(l, last[s[r]]) #这一步很关键
        res = max(res, r - l + 1)
        last[s[r]] = r
    return res
