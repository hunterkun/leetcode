/*4. Median of Two Sorted Arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively.
*/
float findMedianSortedArrays2(int A[], int m, int B[], int n)
{
    vector<int> res;
    int i, j;
    int mid = (m + n) / 2 + 1;
    for (i = 0, j = 0; i < m && j < n;)
    {
        if (A[i] > B[j])
        {
            res.push_back(B[j++]);
        }
        else
        {
            res.push_back(A[i++]);
        }
        if (res.size() == mid)
            break;
    }
    while (res.size() != mid)
    {
        if (i < m)
            res.push_back(A[i++]);
        if (j < n)
            res.push_back(B[j++]);
    }
    if ((m + n) % 2 == 0)
        return (res[res.size() - 1] + res[res.size() - 2]) / 2.;
    return *(res.end() - 1);
}