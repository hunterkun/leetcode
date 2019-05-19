#include <iostream>

using namespace std;

//基本思想：选定当前数组的某个元素，将其挪到正确的位置，使得左边的子
//数组小于它，右边的子数组大于它。

//对数组arr[l,r)进行分组使得arr[l...p)<arr[p], arr[p+1...r)>arr[j]

template <class T>
int __partition(T arr[], int l, int r)
{
    //为了避免每次选择的第一个元素太小，使得左右分区长度相差太大，可以使用随机方法保证
    //从统计角度看是进行了二分。
    swap(arr[l], arr[rand() % (r - l) + l]);
    T v = arr[l];
    int j = l;
    //arr[l+1...j]<v;arr[j+1...i)>=v
    for (int i = l + 1; i < r; i++)
    {
        if (arr[i] < v)
        {
            swap(arr[i], arr[j + 1]);
            j++;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

template <class T>
void __quickSort(T arr[], int l, int r)
{
    if (r - l <= 1)
        return;
    int p = __partition(arr, l, r);
    __quickSort(arr, l, p);
    __quickSort(arr, p + 1, r);
}

template <class T>
void quickSort(T arr[], int n)
{
    srand(time(NULL));
    __quickSort(arr, 0, n);
}

//arr[l...p)<v arr[p...r]>=v
//arr[l+1...j]<v arr[j+1...i)>=v arr[i]
int partition(int arr[], int l, int r)
{
    swap(arr[l], arr[rand() % (r - l) + l]);
    int v = arr[l];
    int j = l;
    for (int i = l + 1; i <= r; i++)
    {
        if (arr[i] < v)
            swap(arr[++j], arr[i]);
    }
    swap(arr[j], arr[l]);
    return j;
}

//针对大量重复元素的缺点，无论是哪种情况(<=v;>v/<v;>=v)都会造成两边长度极不平衡。
//双路快速排序：将它分成<=v和>=v，这样就可以保证两边长度差不太多。
template <class T>
int __partition2(T arr[], int l, int r)
{
    swap(arr[l], arr[rand() % (r - l) + l]);
    T v = arr[l];
    int i = l + 1, j = r - 1;
    //arr[l+1...i)<=v; arr(j...r)>=v
    //一定要记清楚i,j代表什么，才能正确判断索引的位置
    while (true)
    {
        while (i < r && arr[i] < v)
            i++;
        while (j > l && arr[j] > v)
            j--;
        if (i >= j)
            break;
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    swap(arr[l], arr[j]);
    return j;
}

//3路快速排序：对数组arr[l,r]进行重新分配，分成三部分，arr[l...lt-1]<v, arr[lt...gt-1]=v, arr[gt..r]>v
template <class T>
void __quickSort3Way(T arr[], int l, int r)
{
    if (r <= l)
        return;
    //partition部分要返回多个返回值，就不要写成函数了
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T e = arr[l];
    //arr[l+1...lt)<v; arr[lt...i)=v; arr(gt...r]>v
    //还是要注意这三个索引值根据你赋予的实际意义去写相应的边界处理。
    int lt = l + 1;
    int i = l + 1;
    int gt = r;

    while (i <= gt)
    {
        if (arr[i] == e)
            i++;
        else if (arr[i] < e)
        {
            swap(arr[i], arr[lt]);
            lt++;
            i++;
        }
        else
        {
            swap(arr[gt], arr[i]);
            gt--;
        }
    }
    swap(arr[l], arr[lt - 1]);

    __quickSort3Way(arr, l, lt - 2);
    __quickSort3Way(arr, gt + 1, r);
}

template <class T>
void quickSort3Way(T arr[], int n)
{
    srand(time(NULL));
    __quickSort3Way(arr, 0, n - 1);
}

//arr[l+1...j]<v, arr[j+1...i)=v, arr[k+1...r]>v
void __quickSort3(int arr[], int l, int r)
{
    int v = arr[l];
    int i = l + 1, j = l, k = r;
    while (i <= k)
    {
        if (arr[i] == v)
            i++;
        else if (arr[i] < v)
        {
            swap(arr[i], arr[++j]);
            i++;
        }
        else
            swap(arr[k--], arr[i]);
    }
    swap(arr[l], arr[j]); //arr[j...k]=v, arr[l...j-1]<v
    __quickSort3(arr, l, j - 1);
    __quickSort3(arr, k + 1, r);
}

//利用快速排序的思想求解数组中第k大的元素
int selection(int arr[], int n, int k)
{
    assert(k >= 0 && k < n);
    srand(time(NULL));
    return __selection(arr, 0, n - 1, k);
}

//arr[l+1...j]<v, arr[j+1...i)>=v
int __selection(int arr[], int l, int r, int k)
{
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    int v = arr[l];
    int j = l;
    for (int i = l + 1; i <= v; i++)
    {
        if (arr[i] < v)
            swap(arr[++j], arr[i]);
    }
    swap(arr[l], arr[j]);
    if (j == k)
        return arr[j];
    else if (j < k)
        return __selection(arr, j + 1, r, k);
    else
    {
        return __selection(arr, l, j - 1, k);
    }
}

//找到k个最小数
int __selection(int arr[], int l, int r, int k)
{
    int p = __partition(arr, l, r);
    int res[k];
    while (p != k - 1)
    {
        if (p < k - 1)
            p = __patition(arr, p + 1, r);
        if (p > k - 1)
            p = __patition(arr, l, p - 1);
    }
    for (int i = 0; i < p; i++)
        res[i] = arr[i];
}