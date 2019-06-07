#include <iostream>

using namespace std;

/*
基本思想：对当前元素i，寻找它之后[i+1,n)区间的最小值并于它交换
*/
template <class T>
void selectionSort(T arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        //寻找[i,n)区间的的最小值
        int min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        swap(arr[i], arr[min_index]);
    }
}

int main()
{
    float a[10] = {10., 9., 8., 4.4, 6, 5, 4, 3, 2, 1};
    selectionSort(a, 10);
    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
