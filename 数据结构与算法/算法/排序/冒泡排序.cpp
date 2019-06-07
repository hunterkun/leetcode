#include <iostream>

using namespace std;

/*
基本思想：两两比较，如果前面的比后面的大则进行交换，每一轮将最大的值交换到最后。
每一趟Bubble Sort都将最大的元素放在了最后的位置，所以下一次排序最后的元素可以不再考虑
*/

template <class T>
void bubbleSort(T arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            if (arr[j] < arr[j - 1])
                swap(arr[j - 1], arr[j]);
        }
    }
}
/*
优化方法：
1.如果哪一轮没有任何交换操作，说明已经排好序了，直接退出即可。 

*/

template <class T>
void bubbleSort2(T arr[], int n)
{
    bool swapped;
    for (int i = 0; i < n; i++)
    {
        swapped = false;
        for (int j = 1; j < n - i; j++)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j - 1], arr[j]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}

/*
2.可以记录最后一次的交换位置，在此之后的元素在下一轮扫描中均不考虑。
同时如果这个值没有改变，相当于这次循环没有进行交换操作，也可以直接退出了。
*/

template <class T>
void bubbleSort3(T arr[], int n)
{
    int index;
    do
    {
        index = 0;
        for (int j = 1; j < n; j++)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j - 1], arr[j]);
                index = j;
            }
        }
        n = index;

    } while (n > 0);
}