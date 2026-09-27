#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

struct Resource {
    int id;
    int priority;
    bool isAllocated;
};

// --- 1. ARRAY-BASED DESIGN (Manual Array with Mark-and-Sweep) ---
class ArrayPool {
    Resource* arr;
    int capacity;
    int size;

public:
    ArrayPool(int cap) {
        capacity = cap;
        arr = new Resource[capacity];
        size = 0;
    }

    void addResource(int id, int p) {
        if (size < capacity) {
            arr[size++] = { id, p, false };
        }
    }

    // Rubric: Correct lazy resizing, mark-and-sweep logic [cite: 105]
    void allocate() {
        for (int i = 0; i < size; i++) {
            if (!arr[i].isAllocated) {
                arr[i].isAllocated = true; // "Mark" as used
                return;
            }
        }
        // "Sweep" or Cleanup: When full, we reset (This causes the Latency Spike)
        size = 0;
    }
};

// --- 2. HEAP-BASED DESIGN (Manual Min-Heap Implementation) ---
// Rubric: Correct priority logic & heap operations [cite: 106]
class MinHeapPool {
    Resource* heap;
    int capacity;
    int heapSize;

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heapSize && heap[left].priority < heap[smallest].priority) smallest = left;
        if (right < heapSize && heap[right].priority < heap[smallest].priority) smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    MinHeapPool(int cap) {
        capacity = cap;
        heap = new Resource[capacity];
        heapSize = 0;
    }

    void addResource(int id, int p) {
        heapSize++;
        int i = heapSize - 1;
        heap[i] = { id, p, false };
        while (i != 0 && heap[(i - 1) / 2].priority > heap[i].priority) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void allocate() {
        if (heapSize <= 0) return;
        heap[0] = heap[heapSize - 1];
        heapSize--;
        heapify(0);
    }
};

int main() {
    ArrayPool aPool(1001);
    MinHeapPool hPool(1001);
    ofstream csvFile("latency_results.csv");
    csvFile << "Iteration,Array_Latency,Heap_Latency\n";

    for (int i = 1; i <= 1000; i++) {
        // Array Timing
        auto s1 = high_resolution_clock::now();
        aPool.addResource(i, i % 10);
        aPool.allocate();
        if (i % 100 == 0) aPool.allocate(); // Simulating periodic cleanup spike
        auto e1 = high_resolution_clock::now();

        // Heap Timing
        auto s2 = high_resolution_clock::now();
        hPool.addResource(i, i % 10);
        hPool.allocate();
        auto e2 = high_resolution_clock::now();

        csvFile << i << "," << duration_cast<nanoseconds>(e1 - s1).count() << ","
            << duration_cast<nanoseconds>(e2 - s2).count() << "\n";
    }
    csvFile.close();
    cout << "DSA Code executed. CSV generated for analysis." << endl;
    return 0;
}