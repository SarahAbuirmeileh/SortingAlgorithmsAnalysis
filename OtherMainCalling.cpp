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
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);

int main() {
    int const size = 100;

    int Rand[size];
    for (int i = 0; i < size; i++) {
        Rand[i] = rand() % 100;
    }

    {
        auto start = high_resolution_clock::now();
        quick_sort(Rand, 0, size - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Time taken for Quick sort: " << duration.count() << " nanoseconds" << endl;
    }

    {
        auto start = high_resolution_clock::now();
        bubbleSort(Rand, size);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Time taken for Bubble sort: " << duration.count() << " nanoseconds" << endl;
    }

    {
        auto start = high_resolution_clock::now();
        insertion_sort(Rand, size);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Time taken for Insertion sort: " << duration.count() << " nanoseconds" << endl;
    }

    {
        auto start = high_resolution_clock::now();
        selectionSort(Rand, size);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Time taken for Selection sort: " << duration.count() << " nanoseconds" << endl;
    }

    {
        auto start = high_resolution_clock::now();
        merge_sort(Rand, 0, size - 1);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        cout << "Time taken for Merge sort: " << duration.count() << " nanoseconds" << endl;
    }

    return 0;
}

void quick_sort(int A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quick_sort(A, low, pi - 1);
        quick_sort(A, pi + 1, high);
    }
}

int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (A[j] < pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);

    return (i + 1);
}

void insertion_sort(int A[], int N) {
    for (int i = 0; i < N; ++i) {
        int cur = A[i];
        int j = i - 1;

        while (cur < A[j] && j >= 0)
            A[j + 1] = A[j], j--;

        A[j + 1] = cur;
    }
}

void count_sort(int A[], int N) {
    int *freq = new int[N + 1]{0};
    for (int i = 0; i < N; i++)
        freq[A[i]]++;

    int i = 0;
    for (int val = 0; val <= N; val++)
        while (freq[val]--)
            A[i++] = val;

    delete[] freq;
}

void merge_sort(int A[], int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    merge_sort(A, left, mid);
    merge_sort(A, mid + 1, right);

    merge(A, left, mid, right);
}

void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
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

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_index = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // Swap arr[i] and arr[min_index]
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}
