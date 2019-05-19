//动态规划（自底向上，从简单开始，后面一步需要用到前面求解的答案）
//定义：将原问题拆解成若干个子问题，同时保存子问题的答案，使得每个子问题只被求解一次，
//最终获得原问题的答案。
// 递归（自顶向下，从原问题出发，分解成若干个子问题，分析方便，但会发生重复求解）
// 记忆化搜索（通过记录之前求解的子问题答案，不会重复求解）
#include <iostream>
#include <vector>
using namespace std;

//爬楼梯的方法，可以跨一步或跨两步
//基本思路：第n个阶梯可以由n-1个阶梯或n-2个阶梯到达
//简单递归O(2^n)
int climb(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    return climb(n - 1) + climb(n - 2);
}
//记忆化搜索
vector<int> memo;
int climb(int n)
{
    memo = vector<int>(n + 1, -1);
    _climb2(n);
}
int _climb2(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    if (memo[n] == -1)
        memo[n] = _climb2(n - 1) + _climb2(n - 2);
    return memo[n];
}
//动态规划
int climb(int n)
{

    vector<int> memo(n + 1, 0);
    memo[1] = 1;
    memo[2] = 2;
    for (int i = 3; i <= n; i++)
    {
        memo[i] = memo[i - 1] + memo[i - 2];
    }
    return memo[n];
}

/*120. Triangle (med)
Given a triangle, find the minimum path sum from top to bottom. 
Each step you may move to adjacent numbers on the row below.
For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]    
*/
//基本思路：当前层的值来源于上一层的两个值中的最小值，两个端点只能来自于上一层的端点。

//动态规划，从第一层开始慢慢往下算出结果
//vector中求最小值的min_element max_element，返回相应的迭代器
vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}};
int minimumTotal(vector<vector<int>> &triangle)
{
    int n = triangle.size();

    for (int i = 1; i < n; i++)
    {
        triangle[i][0] += triangle[i - 1][0];
        triangle[i][i] += triangle[i - 1][i - 1];
        if (int j = 1; j < i; j++)
            triangle[i][j] += min(triangle[i - 1][j], triangle[i - 1][j - 1]);
    }

    return *min_element(triangle[n - 1].begin(), triangle[n - 1].end())
}

//记忆化搜索
int minimumTotal(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    //需要另外一个二维数组存储答案
    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++)
        //go函数从最后一层递归填充这个dp,从第一列开始
        go(triangle, n - 1, i, dp);

    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}

int go(const vector<vector<int>> triangle, int i, int j, vector<vector<int>> dp)
{
    if (dp[i][j] != -1)
        return dp[i][j];
    if (i == 0)
        return dp[i][j] = triangle[i][j];
    if (j == 0)
        return dp[i][j] = triangle[i][j] + go(triangle, i - 1, 0, dp);
    if (j == i)
        return dp[i][j] = triangle[i][j] + go(triangle, i - 1, i - 1, dp);
    return dp[i][j] = triangle[i][j] + min(go(triangle, i - 1, j, dp), go(triangle, i - 1, j - 1, dp));
}

/*343 Integer Break
Given a positive integer n, break it into the sum of at least two positive
integers and maximize the product of those integers. Return the maximum product.
*/
//简单递归
int max3(int i, int j, int k)
{
    return max(i, max(j, k));
}
int integerBreak(int n) //至少会分成两个数，所以还要计算只有1个数的情况
{
    int res = 0;
    if (n == 1)
        return 1;
    for (int i = 1; i < n; i++)
        res = max3(res, i * integerBreak(n - i), i * (n - i));

    return res;
}
//记忆化搜索
vector<int> memo;
int intergerBreak(int n)
{
    vector<int> memo(n + 1, -1);
    return __intergerBreak(n);
}
int __intergerBreak(int n)
{
    int res = 0;
    if (n == 1)
        return 1;

    if (memo[n] != -1)
        return memo[n];

    for (int i = 1; i < n; i++)
        res = max3(res, i * integerBreak(n - i), i * (n - i));

    return memo[n] = res;
}

//动态规划
int intergerBreak(int n)
{
    //memo[i]表示把数字i至少分割成两部分后得到的最大乘积
    vector<int> memo(n + 1, -1);
    memo[1] = 1;
    for (int i = 2; i <= n; i++)
        //求解memo[i]
        for (int j = 1; j < i; j++) //j+(i-j)
            memo[i] = max3(memo[i], j * memo[i - j], j * (i - j));
    return memo[n];
}

//寻找最少的平方数，使得和为n
vector<int> memo;
int numSquares(int n)
{
    memo = vector<int>(n + 1, -1);
    return __numSquare(n);
}
int __numSquare(int n)
{
    int res = __INT_MAX__;
    if (n == 0)
        return 0;
    if (memo[n] != -1)
        return memo[n];
    for (int i = 1; i * i <= n; i++)
        res = min(res, 1 + __numSquare(n - i * i));
    return memo[n] = res;
}

int numSquare(int n)
{
    vector<int> memo(n + 1, __INT_MAX__);
    memo[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; i >= j * j; j++)
            memo[i] = min(memo[i], 1 + memo[i - j * j]);
    }
    return memo[n];
}

/*198. House Robber (Easy)
You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed, the only constraint 
stopping you from robbing each of them is that adjacent houses have security 
system connected and it will automatically contact the police if two adjacent 
houses were broken into on the same night. Given a list of non-negative 
integers representing the amount of money of each house, determine the 
maximum amount of money you can rob tonight without alerting the police.
*/

//状态的定义：考虑偷取[x...n-1]范围的房子(这里考虑偷取的意思是并不一定会偷取x或者n-1的房子)
//注意这点细微差别
//转移方程：f(0)=max(x[0]+f(2), x[1]+f(3), x[2]+f(4), ...)
int tryrob(vector<int> &nums, int x)
{
    int n = nums.size();
    if (x >= n)
        return 0;
    int s = 0;
    for (int i = x; i < n; i++)
        s = max(s, nums[i] + tryrob(nums, i + 2));
    return s;
}

vector<int> memo;
int rob(vector<int> &nums)
{
    memo = vector<int>(nums.size(), -1);
    return tryrob(nums, 0);
}

int tryrob2(vector<int> &nums, int x)
{
    int n = nums.size();

    if (x >= n)
        return 0;
    int s = 0;
    if (memo[x] != -1)
        return memo[x];
    for (int i = x; i < nums.size(); i++)
        s = max(s, nums[i] + tryrob(nums, i + 2));
    memo[x] = s;
    return s;
}

int rob(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    vector<int> memo(n, -1);
    memo[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
        for (int j = i; j < n; j++)
            memo[i] = max(memo[i], j + 2 < n ? memo[j + 2] + nums[j] : nums[j]);
    return memo[0];
}

//状态定义：考虑偷取[0...x]范围的房子
//状态转移： f(n-1)=max(x[n-1], x[n-2], x[n-3]+f(n-1),....)

//House Robber2 街道为环形，最后一个和第一个房子相邻。

/*背包问题
容量为C,n种不同的物品，每件物品重wi,价值为vi
问不超过容量C的前提下，所放物体的最大价值
*/
//状态函数：F(n,C), 考虑[0...n-1]范围内的物品, 参数个数取决于问题的限制条件
//转移方程：F(i,c)=max(F(i-1, c)， F(i-1,c-Wi)+vi)

//用[0...index]的物体中来填充
int _knapsack01(const vector<int> &w, const vector<int> &v, int index, int c)
{
    if (index < 0 || c <= 0)
        return 0;

    if (memo[index][c] != -1)
        return memo[index][c];
    int res = _knapsack01(w, v, index - 1, c);
    if (c >= w[index])
        res = max(res, _knapsack01(w, v, index - 1, c - w[index]) + v[index]);
    return memo[index][c] = res;
}

vector<vector<int>> memo;
int knapsack01(const vector<int> &w, const vector<int> &v, int C)
{
    int n = v.size();
    memo = vector<vector<int>>(n, vector<int>(C + 1, -1));
    return _knapsack01(w, v, n - 1, C);
}

//动态规划
int dp_knapsack01(const vector<int> &w, const vector<int> &v, int C)
{
    assert(w.size() == v.size());
    int n = w.size();
    vector<vector<int>> memo(n, vector<int>(C + 1), -1);
    for (int i = 0; i <= C; i++)
        memo[0][i] = w[0] <= i ? v[0] : 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < C; j++)
        {
            memo[i][j] = memo[i - 1][j];
            if (w[i] <= j)
                memo[i][j] = max(memo[i][j], v[i] + memo[i - 1][j - w[i]]);
        }
    return memo[n - 1][C];
}
//优化动态规划
int dp_kanpsack01(const vector<int> &w, const vector<int> &v, int C)
{
    int n = w.size();
    vector<vector<int>> memo(2, vector<int>(C + 1, -1));
    for (int i = 0; i <= C; i++)
        memo[0][i] = w[0] <= i ? v[0] : 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j <= C; j++)
        {
            memo[i % 2][j] = memo[(i - 1) % 2][j];
            if (w[i] <= j)
                memo[i % 2][j] = max(memo[i % 2][j], memo[(i - 1) % 2][j - w[i]] + v[i]);
        }

    return memo[(n - 1) % 2][C];
}

int dp_kanpsack01(const vector<int> &w, const vector<int> &v, int C)
{
    int n = w.size();
    vector<int> memo(C + 1, -1);
    for (int i = 0; i <= C; i++)
        memo[i] = w[0] <= i ? v[0] : 0;
    for (int i = 1; i < n; i++)
        for (int j = C; j >= w[i]; j--)
            memo[j] = max(memo[j], memo[j - w[i]] + v[i]);

    return memo[C];
}

//最长上升子序列
//记忆化搜索
vector<int> memo;
int lengthOfLIS(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    int r = 0;
    memo = vector<int>(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++)
        r = max(r, _lengthOfLIS(nums, i));
    return r;
}
//LIS(i)=max(LIS(j)+1)  对所有的(j<i) 表示以i结尾的最长子序列的长度，一定包括nums[i]
int _lengthOfLIS(vector<int> &nums, int i)
{
    if (memo[i] != 0)
        return memo[i];
    int r = 1;
    for (int j = i - 1; j >= 0; j--)
        if (nums[j] < nums[i]) //一定要以nums[i]结尾
            r = max(r, 1 + _lengthOfLIS(nums, j));
    return memo[i] = r;
}

int lengthOfLIS(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    vector<int> memo(nums.size(), 1);
    for (int i = 0; i < nums.size(); i++)
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i])
                memo[i] = max(memo[i], memo[j] + 1);
    return *max_element(memo.begin(), memo.end());
}

//最长公共子序列
//状态：LCS(m, n)表示S1[0...m]，S2[0...n]的最长公共子序列的长度
//转移方程：LCS(m,n)=LCS(m-1,n-1)+1  S1[m]=S2[n]
//         LCS(m,n)=max(LCS(m-1,n),LCS(m,n-1)) S1[m]!=S2[n]

int LCS(string s1, string s2)
{
    int m = s1.size(), n = s2.size();
    vector<vector<int>> memo(m, vector<int>(n, 0));
    int k = s2.find(s1[0]);
    if (k != -1)
        for (int i = k; i < n; i++)
            memo[0][i] = 1;
    int p = s1.find(s2[0]);
    if (p != -1)
        for (int i = p; i < m; i++)
            memo[i][0] = 1;

    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            if (s1[m] == s2[n])
                memo[m][n] = memo[m - 1][n - 1] + 1;
            else
                memo[m][n] = max(memo[m - 1][n], memo[m][n - 1]);
}

//416 给定一个非空数组，问是否可以将该数组元素分成两部分,使得每部分的数字和相等.
//转化为背包问题，等价于从n个数中选几个填满容量为sum/2的背包
//F(i,c)=F(i-1,c)||F(i-1,c-w[i])

bool canPartition(vector<int> nums)
{
    if (nums.size() <= 1)
        return false;
    int sum = 0;
    for (auto num : nums)
        sum += num;
    if (sum % 2 == 1)
        return false;
    int n = nums.size();
    return __canPatition(nums, n - 1, sum / 2);
}
//用[0...i]的数去填充容量为c的包
bool __canPatition(vector<int> nums, int i, int c)
{
    if (c == 0)
        return true;
    if (c < 0 || i < 0)
        return false;
    return __canPatition(nums, i - 1, c) || __canPatition(nums, i - 1, c - nums[i]);
}

//找零问题
//转移方程

//记忆化搜索
vector<int> memo;
int max_amount;
int coinChange(vector<int> &coins, int amount)
{
    max_amount = amount + 1;
    memo = vector<int>(amount + 1, -1);
    int res = _coinChange(coins, amount);
    return res == max_amount ? -1 : res;
}

int _coinChange(vector<int> &coins, int amount)
{
    if (amount == 0)
        return 0;
    if (memo[amount] != -1)
        return memo[amount];

    int result = max_amount;
    for (int coin : coins)
    {
        if (amount - coin >= 0)
            result = min(result, coinChange(coins, amount - coin) + 1);
    }

    return memo[amount] = result;
}
//动态规划
int coinChange(vector<int> &coins, int amount)
{
    vector<int> memo(amount + 1, amount + 1);
    memo[0] = 0;
    for (int coin : coins)
        for (int i = coin; i <= amount; i++)
            memo[i] = min(memo[i], memo[i - coin] + 1);

    return memo[amount] == amount + 1 ? -1 : memo[amount];
}
