#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;

// Resource Structure
struct Resource {
    int id;
    int priority;
    bool isAllocated;
    Resource* next;
};

// --- 1. ARRAY-BASED DESIGN (Mark-and-Sweep) ---
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
        if (size < capacity) arr[size++] = { id, p, false, nullptr };
    }
    void allocate() {
        for (int i = 0; i < size; i++) {
            if (!arr[i].isAllocated) {
                arr[i].isAllocated = true; // Mark
                return;
            }
        }
        size = 0; // Sweep/Cleanup (Causes Latency Spike)
    }
};

// --- 2. LINKED LIST-BASED DESIGN (Free-List) ---
class LinkedListPool {
    Resource* head;
public:
    LinkedListPool() { head = nullptr; }
    void addResource(int id, int p) {
        Resource* newNode = new Resource{ id, p, false, head };
        head = newNode;
    }
    void allocate() {
        if (head != nullptr) {
            Resource* temp = head;
            head = head->next; // O(1) Allocation
            delete temp;
        }
    }
};

// --- 3. HEAP-BASED DESIGN (Min-Binary Heap) ---
class MinHeapPool {
    Resource* heap;
    int heapSize;
    void heapify(int i) {
        int smallest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < heapSize && heap[l].priority < heap[smallest].priority) smallest = l;
        if (r < heapSize && heap[r].priority < heap[smallest].priority) smallest = r;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
public:
    MinHeapPool(int cap) {
        heap = new Resource[cap];
        heapSize = 0;
    }
    void addResource(int id, int p) {
        heapSize++;
        int i = heapSize - 1;
        heap[i] = { id, p, false, nullptr };
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
    int iterations = 1000;
    ArrayPool aPool(iterations + 1);
    LinkedListPool lPool;
    MinHeapPool hPool(iterations + 1);

    ofstream csvFile("latency_comparison.csv");
    csvFile << "Iteration,Array_ns,LinkedList_ns,Heap_ns\n";

    for (int i = 1; i <= iterations; i++) {
        // Array Timing
        auto s1 = high_resolution_clock::now();
        aPool.addResource(i, i % 10);
        aPool.allocate();
        if (i % 100 == 0) aPool.allocate(); // Cleanup spike
        auto e1 = high_resolution_clock::now();

        // Linked List Timing
        auto s2 = high_resolution_clock::now();
        lPool.addResource(i, i % 10);
        lPool.allocate();
        auto e2 = high_resolution_clock::now();

        // Heap Timing
        auto s3 = high_resolution_clock::now();
        hPool.addResource(i, i % 10);
        hPool.allocate();
        auto e3 = high_resolution_clock::now();

        csvFile << i << ","
            << duration_cast<nanoseconds>(e1 - s1).count() << ","
            << duration_cast<nanoseconds>(e2 - s2).count() << ","
            << duration_cast<nanoseconds>(e3 - s3).count() << "\n";
    }

    csvFile.close();
    cout << "Comparison complete. Data saved to 'latency_comparison.csv'." << endl;
    return 0;
}