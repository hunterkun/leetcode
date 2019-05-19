#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//二维情形下子矩阵的最大和

//方法1：暴力解法，遍历所有的子矩阵。对于求和部分，则采用部分和方法。
#define N 2
#define M 4

int PS[N + 1][M + 1];
void Get(int A[N][M])
{
    for (int i = 0; i < N + 1; i++)
        PS[i][0] = 0;
    for (int j = 0; j < M + 1; j++)
        PS[0][j] = 0;
    for (int i = 1; i < N + 1; i++)
        for (int j = 1; j < M + 1; j++)
            PS[i][j] = PS[i - 1][j] + PS[i][j - 1] - PS[i - 1][j - 1] + A[i - 1][j - 1];
}

inline int matrix_sum2(int matrix[N][M], int i_min, int i_max, int j_min, int j_max)
{
    return PS[i_max + 1][j_max + 1] - PS[i_max + 1][j_min] - PS[i_min][j_max + 1] + PS[i_min][j_min];
}

int matrix_sum(int matrix[N][M], int imin, int imax, int jmin, int jmax)
{
    int sum = 0;
    for (int i = imin; i <= imax; i++)
        for (int j = jmin; j <= jmax; j++)
        {
            sum += matrix[i][j];
        }
    return sum;
}

int MaxSum1(int A[N][M])
{
    int best = INT16_MIN;
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            for (int k = 0; k < M; k++)
            {
                for (int l = k; l < M; l++)
                {
                    best = max(best, matrix_sum2(A, i, j, k, l));
                }
            }
        }
    }
    return best;
}

//解法2：将问题转化为1维
int MaxSum1d(vector<int> &nums)
{
    int n = nums.size();
    vector<int> ans(n);
    vector<int> tmp(n);
    int tmpp = nums[n - 1], anss = nums[n - 1];
    ans[n - 1] = nums[n - 1];
    tmp[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        // tmp[i] = max(tmp[i + 1] + nums[i], nums[i]);
        // ans[i] = max(ans[i + 1], tmp[i]);
        // 不用数组也行
        // tmpp = max(tmpp + nums[i], nums[i]);
        // anss = max(tmpp, anss);
        // 等价写法
        if (tmpp < 0)
            tmpp = 0;
        tmpp += nums[i];
        if (anss < tmpp)
            anss = tmpp;
    }
    return anss;
}

int MaxSum2(int A[N][M])
{
    int best = INT16_MIN;
    vector<int> s;
    int tmp;
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            for (int k = 0; k < M; k++)
            {
                tmp = PS[j + 1][k + 1] - PS[i][k + 1] - PS[j + 1][k] + PS[i][k];
                s.push_back(tmp);
            }
            best = max(best, MaxSum1d(s));
            s.clear();
        }
    }
    return best;
}

int main()
{
    int B[N][M] = {{1, -2, -10, 4}, {6, 7, -18, 9}};
    int maxsum;
    Get(B);
    for (int i = 0; i < N + 1; i++)
    {
        for (int j = 0; j < M + 1; j++)
            cout << PS[i][j] << " ";
        cout << endl;
    }
    maxsum = MaxSum2(B);

    cout << maxsum << endl;
    return 0;
}
