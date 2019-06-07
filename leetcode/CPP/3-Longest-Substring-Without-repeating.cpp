/*3 Longest Substring without repeating characters
Given a string, find the length of the longest substring 
without repeating characters.
*/
int lengthOfLongestSubstring(string s)
{
    int res = 0;
    int i = 0, j = -1;
    int freq[256] = {0};
    while (i < s.size())
    {
        if (freq[s[j + 1]] == 0 && j + 1 < s.size())
        {
            freq[s[++j]]++;
        }
        else
        {
            freq[s[i++]]--;
        }
        res = max((j - i + 1), res);
    }
    return res;
}

//最长的无重复子串abcba
int lengthOfLongestSubstring2(string str)
{
    unordered_map<char, int> map;
    int i, left = 0, maxlen = 0;
    if (str.length() == 0)
        return 0;
    for (i = 0; i < str.size(); i++)
    {
        if (map.find(str[i]) != map.end())
            left = max(map[str[i]] + 1, left);
        maxlen = max(maxlen, i - left + 1);
        map[str[i]] = i;
    }
    return maxlen;
}