#include <iostream>
using namespace std;

class CircularQueue {
private:
    int arr[5];
    int front, rear;
    int size;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
        size = 5;
    }

    bool isFull() {
        return (front == (rear + 1) % size);
    }

    bool isEmpty() {
        return (front == -1);
    }

    void enqueue(int packetID) {
        if (isFull()) {
            cout << "Buffer Overflow - Packet Dropped (" << packetID << ")\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        }
        else {
            rear = (rear + 1) % size;
        }
        arr[rear] = packetID;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Buffer Underflow\n";
            return -1;
        }
        int packet = arr[front];

        if (front == rear) {
            front = rear = -1;
        }
        else {
            front = (front + 1) % size;
        }

        return packet;
    }

    int removeLast() {
        if (isEmpty()) {
            cout << "Buffer Underflow\n";
            return -1;
        }

        int packet = arr[rear];

        if (front == rear) {
            front = rear = -1;
        }
        else {
            rear = (rear - 1 + size) % size;
        }

        return packet;
    }
};

class Stack {
private:
    int arr[10];
    int top;

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == 9;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }
};

int main() {

    CircularQueue buffer;
    Stack emergencyCache;

   
    cout << "Phase 1: Normal Operation - Enqueue 5 packets\n";
    buffer.enqueue(101);
    buffer.enqueue(102);
    buffer.enqueue(103);
    buffer.enqueue(104);
    buffer.enqueue(105);

   
    cout << "\nPhase 2: CPU Overheat - Move last 3 packets to Stack\n";
    for (int i = 0; i < 3; i++) {
        int pkt = buffer.removeLast();
        cout << "Moved to Stack: " << pkt << endl;
        emergencyCache.push(pkt);
    }

    cout << "\nPhase 3: Recovery - Processing from Stack (LIFO)\n";
    while (!emergencyCache.isEmpty()) {
        cout << "Processing Packet: " << emergencyCache.pop() << endl;
    }

   
    cout << "\nPhase 4: Resume - Processing remaining Queue packets\n";
    while (!buffer.isEmpty()) {
        cout << "Processing Packet: " << buffer.dequeue() << endl;
    }

    return 0;
}
