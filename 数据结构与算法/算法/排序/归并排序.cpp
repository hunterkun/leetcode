#include <iostream>

using namespace std;
/*
基本思想：使用递归进行排序，将待排序数组每次对半分，当数组长度小于等于1时停止。
再使用merge操作对两个排好序的子数组合并成排好序的大数组。
长度<=1结束是因为本身就是排好序的。
*/

// 对arr[l,mid)和arr[mid, r)进行归并操作
//注意索引的统一，arr[0,r-1]和arr[0,r)是不一样的。用哪个就对应哪个索引的
template <class T>
void __merge(T arr[], int l, int mid, int r)
{
    T arr2[r - l];
    for (int i = l; i < r; i++)
    {
        arr2[i - l] = arr[i];
    }
    int i = l, j = mid;
    for (int k = l; k < r; k++)
    {
        if (i >= mid)
        {
            arr[k] = arr2[j - l];
            j++;
        }
        else if (j >= r)
        {
            arr[k] = arr2[i - l];
            i++;
        }
        else if (arr2[i - l] > arr2[j - l])
        {
            arr[k] = arr2[j - l];
            j++;
        }
        else
        {
            arr[k] = arr2[i - l];
            i++;
        }
    }
}

// 递归使用归并排序，对arr[left...right)范围进行排序
template <class T>
void __mergeSort(T arr[], int l, int r)
{
    if (r - l <= 1)
        return;
    int mid = l + (r - l) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid, r);
    __merge(arr, l, mid, r);
}

//如果要归并的后一个有序数组的第一个元素大于前一个有序数组的最后一个元素，则不需要归并过程了。
template <class T>
void __mergeSort(T arr[], int l, int r)
{
    if (r - l <= 1)
        return;
    int mid = l + (r - l) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid, r);
    if (arr[mid] < arr[mid - 1])
        __merge(arr, l, mid, r);
}
//对于小数组，可以使用插入排序，而不用递归到1个元素。
template <class T>
void insertSort(T arr[], int l, int r)
{
    for (int i = l + 1; i < r; i++)
    {
        int j;
        T tmp = arr[i];
        for (j = i; j > l && arr[j - 1] > tmp; j--)
            arr[j] = arr[j - 1];
        arr[j] = tmp;
    }
}

template <class T>
void __mergeSort(T arr[], int l, int r)
{
    if (r - l <= 15)
    {
        insertSort(arr, l, r);
        return;
    }

    int mid = l + (r - l) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid, r);
    if (arr[mid] < arr[mid - 1])
        __merge(arr, l, mid, r);
}

template <class T>
void mergeSort(T arr[], int n)
{
    __mergeSort(arr, 0, n);
}

//自底向上的归并排序
/*
基本思想：通过变量size,从小到大，对arr[i,i+size)和arr[i+size,i+2*size)数组进行归并
*/
template <class T>
void mergeSortBU(T arr, int n)
{
    for (int sz = 1; sz < n; sz *= 2)
    {
        for (int i = 0; i + sz < n; i += sz * 2)
        {
            //对arr[i,i+size)和arr[i+size, i+2size)进行合并操作
            //边界问题：如果后面的数组不存在，就不需要合并操作了(i+size<n)
            //后面数组存在但超过了n，则要进行限制。
            __merge(arr, i, i + sz, min(i + sz + sz, n));
        }
    }
}

//注意到没有用到数组索引，因而可以将这种方法扩展到链表。
template <class T>
void mergeSortBU2(T arr, int n)
{
    for (int sz = 1; sz < n; sz *= 2)
    {
        for (int i = 0; i + sz < n && arr[i + sz] < arr[i + sz - 1]; i += sz * 2)
        {
            //对arr[i,i+size)和arr[i+size, i+2size)进行合并操作
            //边界问题：如果后面的数组不存在，就不需要合并操作了(i+size<n)
            //后面数组存在但超过了n，则要进行限制。
            __merge(arr, i, i + sz, min(i + sz + sz, n));
        }
    }
}

//扩展：利用归并排序的思想求数组中逆序对数量
//基本思想:不用一对一对的考虑，而是利用归并排序过程中的merge操作，一次可以比较
//出一组数据的逆序数量。
// arr[l....mid], arr[mid+1....r]

template <class T>
long long inversioncount(T arr[], int n)
{
    return __inversioncount(arr, 0, n - 1);
}

template <class T>
long long __inversioncount(T arr[], int l, int r)
{
    if (l >= r)
        return 0;
    int mid = l + (r - l) / 2;
    long long res1 = __inversioncount(arr, l, mid);
    long long res2 = __inversioncount(arr, mid + 1, r);
    return res1 + res2 + mergecount(arr, l, mid, r);
}

//merge函数求出在arr[l...mid]和arr[mid+1...r]有序的基础上,
//求出arr[l...r]的逆序数对个数
template <class T>
long long mergecount(T arr[], int l, int mid, int r)
{
    int i = l, j = mid + 1;
    long long count = 0;
    T *aux = new T[r - l + 1];
    for (int k = l; k <= r; k++)
    {
        if (i > mid)
        {
            arr[k] = aux[j - l];
            j++;
        }
        else if (j > r)
        {
            arr[k] = aux[i - l];
            i++;
        }
        if (aux[i - l] > aux[j - l])
        {
            arr[k] = aux[j - l];
            j++;
            count += mid - i + 1;
        }
        else
        {
            arr[k] = aux[i - l];
            i++;
        }
    }
    delete[] aux;
    return count;
}