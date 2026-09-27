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


//task 2


#include <iostream>
using namespace std;

// ==========================================
//            DOUBLY LINKED LIST NODE
// ==========================================
class Tab {
public:
    string url;
    Tab* next;
    Tab* prev;

    Tab(string u) {
        url = u;
        next = NULL;
        prev = NULL;
    }
};

// ==========================================
//          TAB MANAGER CLASS (DLL)
// ==========================================
class TabManager {
private:
    Tab* head;     // oldest tab
    Tab* tail;     // newest tab
    Tab* current;  // active tab
    int count;
    const int MAX = 5;

public:
    TabManager() {
        head = tail = current = NULL;
        count = 0;
    }

    // ------------------------------------------
    // Close the oldest tab (head)
    // ------------------------------------------
    void removeHead() {
        if (head == NULL) return;

        Tab* temp = head;

        // Only one tab
        if (head == tail) {
            head = tail = current = NULL;
        }
        else {
            head = head->next;
            head->prev = NULL;

            // If current was removed
            if (current == temp)
                current = head;
        }

        delete temp;
        count--;
    }

    // ------------------------------------------
    // 1. OPEN A NEW TAB
    // ------------------------------------------
    void openTab(string url) {
        cout << "Opening: " << url << endl;

        // If memory full ? remove oldest
        if (count == MAX) {
            cout << "Limit reached ? Closing oldest: " << head->url << endl;
            removeHead();
        }

        Tab* newTab = new Tab(url);

        if (head == NULL) {
            head = tail = current = newTab;
        }
        else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
            current = newTab; // new tab becomes active
        }

        count++;
    }

    // ------------------------------------------
    // 2. CLOSE CURRENT TAB
    // ------------------------------------------
    void closeCurrent() {
        if (current == NULL) {
            cout << "No tabs to close.\n";
            return;
        }

        cout << "Closing current: " << current->url << endl;

        Tab* temp = current;

        // Case 1: Only one tab
        if (head == tail) {
            head = tail = current = NULL;
        }
        // Case 2: current is head
        else if (current == head) {
            head = head->next;
            head->prev = NULL;
            current = head;        // move to next
        }
        // Case 3: current is tail
        else if (current == tail) {
            tail = tail->prev;
            tail->next = NULL;
            current = tail;        // move to previous
        }
        // Case 4: current is in middle
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;

            current = temp->next;  // move to next tab
        }

        delete temp;
        count--;
    }

  
    void switchNext() {
        if (current == NULL || current->next == NULL) {
            cout << "No next tab.\n";
            return;
        }
        current = current->next;
        cout << "Switched to: " << current->url << endl;
    }

  
    void switchPrev() {
        if (current == NULL || current->prev == NULL) {
            cout << "No previous tab.\n";
            return;
        }
        current = current->prev;
        cout << "Switched to: " << current->url << endl;
    }

   
    void showTabs() {
        cout << "\nTabs: ";
        Tab* temp = head;
        while (temp != NULL) {
            if (temp == current)
                cout << "[" << temp->url << "]  ";
            else
                cout << temp->url << "  ";

            temp = temp->next;
        }
        cout << "\n";
    }
};


int main() {
    TabManager tm;

    tm.openTab("google.com");
    tm.openTab("youtube.com");
    tm.openTab("facebook.com");
    tm.openTab("github.com");
    tm.openTab("chatgpt.com");

    tm.showTabs();

    tm.openTab("stackoverflow.com"); 
    tm.showTabs();

    tm.switchPrev();
    tm.switchPrev();
    tm.showTabs();

    tm.closeCurrent();
    tm.showTabs();

    return 0;
}
