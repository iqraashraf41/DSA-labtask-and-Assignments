//Task 1
#include<iostream>
using namespace std;
int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}
//int main() {
//    int n;
//    cout << "Enter number to calculate factorial: "; cin >> n;
//    int result = factorial(n);
//    cout << "Factorial of " << n << " is: " << result << endl;
//    return 0;
//}

//Task 2
#include<iostream>
using namespace std;
int num = 0;
int fib(int n) {
    if (n == 2) num++;
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
//int main() {
//    fib(5);
//    cout << "fib(2) called " << num << " times." << endl;
//    return 0;
//}

//Task 3
#include <iostream>
using namespace std;

// Merge function
//void merge(int arr[], int l, int m, int r) {
//    int n1 = m - l + 1;
//    int n2 = r - m;
//
//    int* left = new int[n1];
//    int* right = new int[n2];
//
//    for (int i = 0; i < n1; i++)
//        left[i] = arr[l + i];
//    for (int j = 0; j < n2; j++)
//        right[j] = arr[m + 1 + j];
//
//    int i = 0, j = 0, k = l;
//
//    while (i < n1 && j < n2) {
//        if (left[i] <= right[j]) {
//            arr[k] = left[i];
//            i++;
//        }
//        else {
//            arr[k] = right[j];
//            j++;
//        }
//        k++;
//    }
//
//    while (i < n1) {
//        arr[k++] = left[i++];
//    }
//
//    while (j < n2) {
//        arr[k++] = right[j++];
//    }
//
//    // Print merge step
//    cout << "Merged: ";
//    for (int x = l; x <= r; x++)
//        cout << arr[x] << " ";
//    cout << endl;
//
//    delete[] left;
//    delete[] right;
//}
//
//// Merge Sort function
//void mergeSort(int arr[], int l, int r) {
//    if (l < r) {
//        int m = l + (r - l) / 2;
//
//        // Print split step
//        cout << "Split: ";
//        for (int x = l; x <= r; x++)
//            cout << arr[x] << " ";
//        cout << endl;
//
//        mergeSort(arr, l, m);
//        mergeSort(arr, m + 1, r);
//        merge(arr, l, m, r);
//    }
//}
//
//int main() {
//    int arr[] = { 5, 2, 9, 1, 5, 6 };
//    int n = sizeof(arr) / sizeof(arr[0]);
//
//    cout << "Original array: ";
//    for (int i = 0; i < n; i++)
//        cout << arr[i] << " ";
//    cout << endl << endl;
//
//    mergeSort(arr, 0, n - 1);
//
//    cout << "\nSorted array: ";
//    for (int i = 0; i < n; i++)
//        cout << arr[i] << " ";
//    cout << endl;
//
//    return 0;
//}


////Task 4
#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int partition(int arr[], int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high];
    cout << "Pivot: " << pivot << endl;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
int main() {
    srand(time(0));
    int arr[] = { 5, 2, 9, 1, 5, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "Original array: ";
    printArray(arr, size);
    quickSort(arr, 0, size - 1);
    cout << "Sorted array: ";
    printArray(arr, size);
    return 0;
}

