#include<iostream>
using namespace std;
  
//#include <iostream>
//using namespace std;
//
//// ======================================================
////              Platinum Priority List (SLL)
//// ======================================================
//class PlatinumNode {
//public:
//    int id;
//    int urgency;
//    PlatinumNode* next;
//
//    PlatinumNode(int i, int u) {
//        id = i;
//        urgency = u;
//        next = NULL;
//    }
//};
//
//class PlatinumList {
//private:
//    PlatinumNode* head;
//
//public:
//    PlatinumList() {
//        head = NULL;
//    }
//
//    // Insert in descending order of urgency
//    void insertPlatinum(int id, int urgency) {
//        PlatinumNode* node = new PlatinumNode(id, urgency);
//
//        // Case 1: Empty list OR highest urgency
//        if (head == NULL || urgency > head->urgency) {
//            node->next = head;
//            head = node;
//            return;
//        }
//
//        // Case 2: Insert somewhere in middle or end
//        PlatinumNode* temp = head;
//        while (temp->next != NULL && temp->next->urgency >= urgency) {
//            temp = temp->next;
//        }
//
//        node->next = temp->next;
//        temp->next = node;
//    }
//
//
//    int removePlatinum() {
//        if (head == NULL)
//            return -1;
//
//        PlatinumNode* temp = head;
//        int id = temp->id;
//
//        head = head->next;
//        delete temp;
//        return id;
//    }
//
//    bool isEmpty() {
//        return head == NULL;
//    }
//
//    void show() {
//        cout << "PlatinumList: ";
//        PlatinumNode* temp = head;
//        while (temp != NULL) {
//            cout << "(" << temp->id << ", U:" << temp->urgency << ") -> ";
//            temp = temp->next;
//        }
//        cout << "NULL\n";
//    }
//};
//
//class GeneralQueue {
//private:
//    int front, rear, size;
//    int arr[100];   
//
//public:
//    GeneralQueue() {
//        front = 0;
//        rear = -1;
//        size = 0;
//    }
//
//    void enqueue(int id) {
//        if (size == 100) {
//            cout << "Queue full! Cannot enqueue.\n";
//            return;
//        }
//        arr[++rear] = id;
//        size++;
//    }
//
//    int dequeue() {
//        if (size == 0)
//            return -1;
//
//        int id = arr[front++];
//        size--;
//        return id;
//    }
//
//    bool isEmpty() {
//        return size == 0;
//    }
//
//    void show() {
//        cout << "GeneralQueue: ";
//        for (int i = front; i <= rear; i++)
//            cout << arr[i] << " ";
//        cout << "\n";
//    }
//};
//
//
//class SupportCenter {
//private:
//    GeneralQueue generalQ;
//    PlatinumList platinumL;
//
//public:
//    void join(int id, string type, int urgency = 0) {
//
//        if (type == "Normal") {
//            cout << "Normal User " << id << " joined General Queue.\n";
//            generalQ.enqueue(id);
//        }
//        else if (type == "Platinum") {
//            cout << "Platinum User " << id << " joined with urgency: " << urgency << endl;
//            platinumL.insertPlatinum(id, urgency);
//        }
//    }
//
//    
//    void assignAgent() {
//        cout << "\nAssigning Agent...\n";
//
//        int id;
//
//        if (!platinumL.isEmpty()) {
//            id = platinumL.removePlatinum();
//            cout << "Agent assigned to PLATINUM customer: " << id << endl;
//        }
//        else if (!generalQ.isEmpty()) {
//            id = generalQ.dequeue();
//            cout << "Agent assigned to NORMAL customer: " << id << endl;
//        }
//        else {
//            cout << "No customers waiting.\n";
//        }
//    }
//
//    void showSystem() {
//        platinumL.show();
//        generalQ.show();
//    }
//};
//
//
//int main() {
//    SupportCenter sc;
//
//    sc.join(101, "Normal");
//    sc.join(102, "Normal");
//    sc.join(201, "Platinum", 5);
//    sc.join(202, "Platinum", 10);   // highest urgency
//    sc.join(203, "Platinum", 3);
//
//    sc.showSystem();
//
//    sc.assignAgent();
//    sc.assignAgent();
//    sc.assignAgent();
//    sc.assignAgent();
//    sc.assignAgent();
//
//    sc.showSystem();
//
//    return 0;
//}
   


//task 2
#include <iostream>
using namespace std;

//================ STACK =================
class Stack {
private:
    int top;
    int arr[100];
public:
    Stack() {
        top = -1;
    }

    void push(int x) {
        if (top == 99) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }

    int pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

//================ NODE =================
class Node {
public:
    int id;
    string type;
    Node* next;

    Node(string t, int i) {
        id = i;
        type = t;
        next = NULL;
    }
};

//================ SINGLY LINKED LIST =================
class SLL {
private:
    Node* head;
    Node* tail;

public:
    Stack st;

    SLL() {
        head = NULL;
        tail = NULL;
    }

    // Insert at end
    void insert(string t, int i) {
        Node* n = new Node(t, i);

        if (head == NULL) {
            head = tail = n;
        }
        else {
            tail->next = n;
            tail = n;
        }
    }

    // Move Forward & Push IDs to stack
    void moveForward() {
        Node* temp = head;
        while (temp != NULL) {
            cout << "Visiting Checkpoint: " << temp->id << endl;
            st.push(temp->id);
            temp = temp->next;
        }
    }

    // Delete a node by ID
    void deleteNode(int id) {
        if (head == NULL) return;

        // If head is the node to delete
        if (head->id == id) {
            Node* d = head;
            head = head->next;
            delete d;
            return;
        }

        Node* temp = head;
        while (temp->next != NULL) {
            if (temp->next->id == id) {
                Node* d = temp->next;
                temp->next = temp->next->next;

                // If tail deleted
                if (d == tail) tail = temp;

                delete d;
                return;
            }
            temp = temp->next;
        }
    }

    // Storm Backtracking
    void encounterStorm(int steps) {
        cout << "\n--- Sandstorm Detected ---\n";

        while (steps-- && !st.isEmpty()) {
            int backID = st.pop();
            cout << "Retreating to Checkpoint " << backID << "...\n";

            // Delete that checkpoint from original path
            deleteNode(backID);
        }
    }

    // Print remaining path after storm
    void printPath() {
        cout << "\nRemaining Path After Storm:\n";
        Node* temp = head;

        if (!temp) {
            cout << "No Checkpoints Remaining.\n";
            return;
        }

        while (temp != NULL) {
            cout << temp->id << " (" << temp->type << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

//================ MAIN =================
int main() {
    SLL rover;

    // Initialize path A ? B ? C ? D ? E
    rover.insert("Rocky", 1);
    rover.insert("Sandy", 2);
    rover.insert("Soft", 3);
    rover.insert("Dusty", 4);
    rover.insert("Mountain", 5);

    // Move forward
    rover.moveForward();

    // Storm hits ? backtrack last 3 steps
    rover.encounterStorm(3);

    // Print updated path
    rover.printPath();

    return 0;
}
