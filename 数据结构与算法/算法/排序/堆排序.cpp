#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

/*
完全二叉树：最下面那层节点必须要从左到右。
*/
template <typename Item>
class MaxHeap
{
  private:
    Item *data;
    int count;
    int capacity;
    void shiftUp(int k)
    {
        while (k > 1 && data[k] > data[k / 2])
        {
            swap(data[k], data[k / 2]);
            k = k / 2;
        }
    }
    void shiftDown(int k)
    {
        while (2 * k <= count)
        {
            int j = 2 * k;
            if (j + 1 <= count && data[j] < data[j + 1])
                j += 1;
            if (data[k] >= data[j])
                break;
            swap(data[k], data[j]);
            k = j;
        }
    }

  public:
    MaxHeap(int capacity)
    {
        data = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }
    ~MaxHeap()
    {
        delete[] data;
    }
    MaxHeap(Item arr[], int n)
    {
        data = new Item[n + 1];
        capacity = n;
        for (int i = 0; i < n; i++)
        {
            data[i + 1] = arr[i];
        }
        count = n;
        for (int i = count / 2; i > 0; i--)
        {
            shiftDown(i);
        }
    }
    int size()
    {
        return count;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    void insert(Item item)
    {
        assert(count + 1 <= capacity);
        data[count + 1] = item;
        count++;
        shiftUp(count);
    }
    Item extractMax()
    {
        Item item = data[1];
        swap(data[1], data[count]);
        count--;
        shiftDown(1);
        return item;
    }
};

//上面实现了堆这种数据结构，那么现在利用它来实现排序
template <class T>
void heapSort(T arr[], int n)
{
    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++)
        maxheap.insert(arr[i]);
    for (int i = n - 1; i >= 0; i--)
        arr[i] = maxheap.extractMax();
}

//heapify作为新的构造方法
//不使用insert方法一个个插入，而是直接将整个数组直接变为堆

template <class T>
void heapSort2(T arr[], int n)
{
    MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
    for (int i = n - 1; i >= 0; i--)
        arr[i] = maxheap.extractMax();
}

//不使用额外的空间，直接在原地进行堆排序
//先使用heapify操作，然后交替使用shiftDown操作和首位元素与末尾元素交换操作
//直接在原数组上改，所以这次从0开始索引

template <class T>
void shiftDown2(T arr[], int n, int k)
{
    while (2 * k + 1 < n)
    {
        int j = 2 * k + 1;
        if (j + 1 < n && arr[j] < arr[j + 1])
            j += 1;
        if (arr[k] > arr[j])
            break;
        swap(arr[k], arr[j]);
        k = j;
    }
}
template <class T>
void heapSort(T arr[], int n)
{

    for (int i = (n - 1) / 2; i >= 0; i--)
        shiftDown2(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        shiftDown2(arr, i, 0);
    }
}

int main()
{
    float a[10] = {10., 9., 8., 4.4, 6, 5, 4, 3, 2, 1};

    heapSort2(a, 10);
    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
