#include <iostream>

using namespace std;

/*
基本思想：从第二个元素开始考察，对当前元素i，与它前面的元素做比较，找到它插入的合适位置。
这有两种方式：
1.一步一步通过交换来实现
2.一种先复制一份当前元素，如果它小于前面那个元素，就把前面元素往后挪一位，再考察
前前面的元素。如果终于找到一个位置，它前面的元素小于这个当前元素，这就是它应该插入的地方，
把它赋值给这个位置的元素*/

template <class T>
void insertSort(T arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (arr[j] < arr[j - 1])
                swap(arr[j], arr[j - 1]);
            else
                break;
        }
    }
}

template <class T>
void insertSort2(T arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        //寻找arr[i]的插入位置
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
            swap(arr[j], arr[j - 1]);
    }
}

template <class T>
void insertSort3(T arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        //寻找arr[i]的插入位置
        int j;
        T tmp = arr[i];
        for (j = i; j > 0 && tmp < arr[j - 1]; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }
}