       
'''
14. Longest Common Prefix
Input: ["flower","flow","flight"]
Output: "fl"
'''
# Horizon Scanning
def longestCommonPrefix(strs):
    if len(strs)==0:
        return ""
    res = strs[0]
    for i in range(1, len(strs)):
        for j in range(len(res)):
            if j >= len(strs[i]) or res[j] != strs[i][j]:
                res = res[0:j]
                break
    return res

# Vertical Scanning
def longestCommonPrefix2(strs):
    if len(strs) == 0:
        return ""
    res=""
    for i in range(len(strs[0])):
        for j in range(1, len(strs)):
            if i >= len(strs[j]) or strs[0][i]!=strs[j][i]:
                return res
        res += strs[0][i]
    return res