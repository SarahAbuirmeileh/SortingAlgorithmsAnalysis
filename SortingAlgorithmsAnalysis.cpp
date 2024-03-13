#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void merge_sort(int A[], int left, int right);
void merge(int A[], int left, int mid, int right);
void insertion_sort(int A[], int N);
void count_sort(int A[], int N);
int partition(int A[], int low, int high);
void quick_sort(int A[], int low, int high);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int N;
    cin >> N;
    int *v = new int[N];
    for (int i = 0; i < N; ++i)
        v[i] = i;

    cout << "Input size : " << N << endl;

    // Merge sort
    random_shuffle(v, v + N);
    auto start = high_resolution_clock::now();
    merge_sort(v, 0, N - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function merge sort : "
         << duration.count() << " microseconds" << endl;

    // Insertion sort
    random_shuffle(v, v + N);
    start = high_resolution_clock::now();
    insertion_sort(v, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function insertions sort : "
         << duration.count() << " microseconds" << endl;

    // Counting sort
    random_shuffle(v, v + N);
    start = high_resolution_clock::now();
    count_sort(v, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function counting sort : "
         << duration.count() << " microseconds" << endl;

    // Quick sort
    random_shuffle(v, v + N);
    start = high_resolution_clock::now();
    quick_sort(v, 0, N - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function quick sort : "
         << duration.count() << " microseconds" << endl;

    delete[] v;

    return 0;
}

void quick_sort(int A[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(A, low, high);
        quick_sort(A, low, pi - 1);
        quick_sort(A, pi + 1, high);
    }
}

int partition(int A[], int low, int high)
{
    int pivot = A[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);

    return (i + 1);
}

void insertion_sort(int A[], int N)
{
    for (int i = 0; i < N; ++i)
    {
        int cur = A[i];
        int j = i - 1;

        while (cur < A[j] && j >= 0)
            A[j + 1] = A[j], j--;

        A[j + 1] = cur;
    }
}

void count_sort(int A[], int N)
{
    int *freq = new int[N + 1]{0};
    for (int i = 0; i < N; i++)
        freq[A[i]]++;

    int i = 0;
    for (int val = 0; val <= N; val++)
        while (freq[val]--)
            A[i++] = val;

    delete[] freq;
}

void merge_sort(int A[], int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    merge_sort(A, left, mid);
    merge_sort(A, mid + 1, right);

    merge(A, left, mid, right);
}

void merge(int A[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }

    while (i < n1)
        A[k++] = L[i++];
    while (j < n2)
        A[k++] = R[j++];

    delete[] L;
    delete[] R;
}
