#include <iostream>

using namespace std;

//如果找到target,返回相应的索引index
//如果没有找到target,返回-1

template <class T>
int binarySearch(T arr[], int n, T target)
{
    //在arr[l...r]中寻找target
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return -1;
}

//递归实现
template <class T>
int __binarySearch(T arr[], int l, int r, T target)
{
    if (l > r)
        return -1;
    int mid = l + (r - l) / 2;
    if (arr[mid] == target)
        return mid;

    else if (arr[mid] > target)
    {
        __binarySearch(arr, l, mid - 1, target);
    }
    else
    {
        __binarySearch(arr, mid + 1, r, target);
    }
}

template <class T>
int binarySearch(T arr[], int n, T target)
{
    return __binarySearch(arr, 0, n - 1, target);
}

//实现floor和ceil方法
template <class T>
int floor(T arr[], int n, T target)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            l = mid + 1;
        else
        {
            r = mid - 1;
        }
    }
    return -1;
}

