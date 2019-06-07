#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//322. 零钱兑换
//给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的
//最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1
int FindChange(int change, vector<int> &coinValueList)
{
    int nums = change;
    int tmp;
    auto it = find(coinValueList.begin(), coinValueList.end(), change);
    if (it != coinValueList.end())
        return 1;
    for (auto i : coinValueList)
    {
        if (i < change)
        {
            tmp = FindChange(change - i, coinValueList) + 1;
            nums = min(tmp, nums);
        }
    }
    return nums;
}

int FindChange2(int change, vector<int> &coinValueList, vector<int> &table)
{
    int nums = change;
    int tmp;
    auto it = find(coinValueList.begin(), coinValueList.end(), change);
    if (it != coinValueList.end())
    {
        table[change] = 1;
        return 1;
    }
    auto it2 = find(table.begin(), table.end(), change);
    if (it2 != table.end())
    {
        return table[change];
    }
    for (auto i : coinValueList)
    {
        if (i < change)
        {
            tmp = FindChange2(change - i, coinValueList, table) + 1;
            nums = min(tmp, nums);
            table[change] = nums;
        }
    }
    return nums;
}

int FindChange3(int change, vector<int> &coinValueList, vector<int> &table)
{
    int tmp;
    for (int coin = 0; coin < change + 1; coin++)
    {
        tmp = coin;
        for (auto i : coinValueList)
        {
            if (i <= coin)
            {
                if (table[coin - i] + 1 < tmp)
                {
                    tmp = table[coin - i] + 1;
                }
            }
        }
        table[coin] = tmp;
    }
    return table[change];
}

int main(int argc, char const *argv[])
{
    vector<int> coins{2, 5, 8};
    int ans = FindChange(20, coins);
    cout << ans << endl;

    return 0;
}
