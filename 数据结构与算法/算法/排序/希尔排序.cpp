#include <iostream>

using namespace std;

/*
基本思想：不像插入排序以步长1排序，也就是每次都和前面一个元素比较，这个算法
将步长递减，先排步长5的，再排步长3的，最后再排步长1的。每次都采用插入的思想，只是步长不一样。
因为插入排序对近乎有序的数组复杂度很低。
*/
template <class T>
void shellSort(T arr[], int n)
{
    int s = 1;
    while (s < n)
        s = 3 * s + 1;
    while (s >= 1)
    {
        for (int i = s; i < n; i++)
        {
            int j;
            T tmp = arr[i];
            for (j = i; j >= s && tmp < arr[j - s]; j -= s)
                arr[j] = arr[j - s];
            arr[j] = tmp;
        }
        s /= 3;
    }
}