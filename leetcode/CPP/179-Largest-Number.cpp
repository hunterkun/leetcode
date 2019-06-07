/*
179. Largest Number
给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数
*/
bool comp(int num1, int num2)
{
    string s1 = to_string(num1) + to_string(num2);
    string s2 = to_string(num2) + to_string(num1);
    return s1 > s2;
}
string smallestNumber(vector<int> &nums)
{
    sort(nums.begin(), nums.end(), comp);
    if (!nums.empty() && nums[0] == 0)
        return "0";
    string res = "";

    for (int num : nums)
        res = res + to_string(num);
    return res;
}