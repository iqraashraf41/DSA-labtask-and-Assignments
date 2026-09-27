#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;
using namespace std::chrono;

// Global array to handle large input sizes without stack overflow 
int globalArr[500000];

// --- UTILITY FUNCTIONS ---

// New helper function to save the current state of globalArr to a text file
void saveArrayToFile(string filename, int n) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; i++) {
            file << globalArr[i] << (i == n - 1 ? "" : " "); // Space separated
        }
        file.close();
    }
}

void generateData(int n, string type) {
    if (type == "random") {
        for (int i = 0; i < n; i++) globalArr[i] = rand() % 100000;
    }
    else if (type == "reverse") {
        for (int i = 0; i < n; i++) globalArr[i] = n - i;
    }
    else if (type == "sorted") {
        for (int i = 0; i < n; i++) globalArr[i] = i;
    }
}

// --- SORTING ALGORITHMS ---

void bubbleSort(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (globalArr[j] > globalArr[j + 1]) swap(globalArr[j], globalArr[j + 1]);
        }
    }
}

void selectionSort(int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (globalArr[j] < globalArr[min_idx]) min_idx = j;
        }
        swap(globalArr[min_idx], globalArr[i]);
    }
}

void insertionSort(int n) {
    for (int i = 1; i < n; i++) {
        int key = globalArr[i], j = i - 1;
        while (j >= 0 && globalArr[j] > key) {
            globalArr[j + 1] = globalArr[j];
            j--;
        }
        globalArr[j + 1] = key;
    }
}

void merge(int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* left = new int[n1]; int* right = new int[n2];
    for (int i = 0; i < n1; i++) left[i] = globalArr[l + i];
    for (int j = 0; j < n2; j++) right[j] = globalArr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) globalArr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < n1) globalArr[k++] = left[i++];
    while (j < n2) globalArr[k++] = right[j++];
    delete[] left; delete[] right;
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

int partition(int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(globalArr[random], globalArr[high]);
    int pivot = globalArr[high], i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (globalArr[j] < pivot) swap(globalArr[++i], globalArr[j]);
    }
    swap(globalArr[i + 1], globalArr[high]);
    return (i + 1);
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void heapify(int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && globalArr[l] > globalArr[largest]) largest = l;
    if (r < n && globalArr[r] > globalArr[largest]) largest = r;
    if (largest != i) { swap(globalArr[i], globalArr[largest]); heapify(n, largest); }
}

void heapSort(int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(n, i);
    for (int i = n - 1; i > 0; i--) { swap(globalArr[0], globalArr[i]); heapify(i, 0); }
}

// --- PERFORMANCE TESTING ---
void runTest(string algName, int n, string dataType, ofstream& csvFile) {
    generateData(n, dataType);

    // REQUIREMENT: Save input to text file
    saveArrayToFile("input.txt", n);

    auto start = high_resolution_clock::now();

    if (algName == "Bubble") bubbleSort(n);
    else if (algName == "Selection") selectionSort(n);
    else if (algName == "Insertion") insertionSort(n);
    else if (algName == "Merge") mergeSort(0, n - 1);
    else if (algName == "Quick") quickSort(0, n - 1);
    else if (algName == "Heap") heapSort(n);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    // REQUIREMENT: Save sorted output to text file
    saveArrayToFile("output.txt", n);

    cout << algName << " (" << dataType << ") Size " << n << ": " << duration.count() << " ms" << endl;
    csvFile << algName << "," << n << "," << dataType << "," << duration.count() << "\n";
}

int main() {
    ofstream csvFile("sorting_results.csv", ios::app);
    if (csvFile.tellp() == 0) csvFile << "Algorithm,InputSize,DataType,TimeMS\n";

    int sizes[] = { 1000, 2000, 3000, 4000, 5000, 10000, 20000, 40000, 80000, 160000, 250000, 500000 };
    string algorithms[] = { "Bubble", "Selection", "Insertion", "Merge", "Quick", "Heap" };
    string dataTypes[] = { "sorted", "random", "reverse" };

    for (string dataType : dataTypes) {
        cout << "\n--- Testing Data Type: " << dataType << " ---" << endl;
        for (string alg : algorithms) {
            for (int n : sizes) {
                // Skip slow algorithms for massive sizes to avoid freezing
                if ((alg == "Bubble" || alg == "Selection" || alg == "Insertion") && n > 40000) continue;
                runTest(alg, n, dataType, csvFile);
            }
        }
    }

    csvFile.close();
    cout << "\nTesting Complete. Files generated: sorting_results.csv, input.txt, output.txt" << endl;
    return 0;
}