#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r) {

    int n1 = m - l + 1;
    int n2 = r - m;

    // Dynamic arrays (because VS does NOT support variable length arrays)
    int* left = new int[n1];
    int* right = new int[n2];

    // Copy data to left[]
    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];

    // Copy data to right[]
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // Merge the arrays
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy leftover of left[]
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy leftover of right[]
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }

    // Free memory
    delete[] left;
    delete[] right;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

//int main() {
//
//    int arr[] = { 5, 2, 9, 1, 6, 3 };
//    int n = sizeof(arr) / sizeof(arr[0]);
//
//    mergeSort(arr, 0, n - 1);
//
//    cout << "Sorted Array: ";
//    for (int i = 0; i < n; i++)
//        cout << arr[i] << " ";
//
//    return 0;
//}


