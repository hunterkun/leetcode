//438.Given a string s and a non-empty string p,
//find all the start indices of p's anagrams in s.
//Strings consists of lowercase English letters only and
//the length of both strings s and p will not be larger than 20100.

bool isAnagram(string s, string t)
{
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    return s == t;
}

vector<int> findAnagrams(string s, string p)
{
    vector<int> res;
    for (int i = 0; i + p.size() < s.size(); i++)
    {
        string ss(s.begin() + i, s.begin() + i + p.size());
        if (isAnagram(p, ss))
            res.push_back(i);
    }
    return res;
}