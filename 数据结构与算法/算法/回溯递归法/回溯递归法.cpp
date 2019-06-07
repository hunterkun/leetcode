//递归回溯算法（暴力解法）
//17. Letter Combinations of a Phone number

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
  public:
    vector<string> lettercombination(string digits)
    {
        res.clear();
        if (digits == "")
            return res;
        findcombination(digits, 0, "");
        return res;
    }

  private:
    void findcombination(const string digits, int index, string s)
    {
        if (index = digits.size())
        {
            res.push_back(s);
            return;
        }
        char c = digits[index];
        assert(c >= '0' && c <= '9' && c != '1');

        string a = table[c - '0'];
        for (int i = 0; i < a.size(); i++)
            findcombination(digits, index + 1, s + a[i]);

        return;
    }
    vector<string> res;
    const string table[10] = {
        " ", "", "abc", 'def', 'ghi', 'jkl', 'mno', 'pqrs', 'tuv', 'wxyz'};
}
