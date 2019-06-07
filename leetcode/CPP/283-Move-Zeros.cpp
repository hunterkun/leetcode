#include <iostream>
#include <vector>

using namespace std;

/*
283. Move Zeroes
Given an array nums, write a function to move all 0's to the end of it 
while maintaining the relative order of the non-zero elements.
*/

//遍历数组，将所有非零元素复制一份，再将其赋给原数组，剩下的元素为0
void moveZeroes(vector<int> &nums)
{
    vector<int> NonZeronums;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != 0)
        {
            NonZeronums.push_back(nums[i]);
        }
    }
    for (int i = 0; i < NonZeronums.size(); i++)
    {
        nums[i] = NonZeronums[i];
    }
    for (int i = NonZeronums.size(); i < nums.size(); i++)
        nums[i] = 0;
}

//遍历数组，用索引来表示当前遍历过的非0元素个数，碰到新的非零元素，直接赋值到那个位置
//剩下元素直接赋值为0
void moveZeroes2(vector<int> &nums)
{
    int k = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i])
        {
            nums[k] = nums[i];
            k++;
        }
    }
    for (int i = k; i < nums.size(); i++)
    {
        nums[i] = 0;
    }
}

//使用交换操作，省下后面迭代赋值为0操作
void moveZeroes3(vector<int> &nums)
{
    int k = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i])
        {
            if (i != k)
                swap(nums[i], nums[k++]);
            else
                k++;
        }
    }
}

int main()
{
    int arr[] = {0, 1, 0, 3, 12};
    vector<int> vec(arr, arr + sizeof(arr) / sizeof(int));
    moveZeroes(vec);
    for (auto i : vec)
        cout << i << " ";
    return 0;
}

//TO DO练习题：27,26,80