#include<iostream>
#include<cstring>
using namespace std;

class Stackredo {
private:
    int top;
    string arr[8];
public:
    Stackredo() {
        top = -1;
    }

    void push(string x) {
        if (top == 7) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }

   string pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return NULL;
        }
        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
    /*   bool isFull() {
		   return top == 7;*/
};

class Stackundo {
private:
    int top;
   string arr[8];
public:
    Stackundo() {
        top = -1;
    }

    void push(string x) {
        if (top == 7) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }

   string pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return NULL;
        }
        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

};

class editorhistory {
	Stackredo redoStack;
	Stackundo undoStack;
public:
    void typeword(string word) {
        string action = word;
        undoStack.push(action);
       
        while (!redoStack.isEmpty()) {
            redoStack.pop();
        }
    }
    void undo() {
        if (!undoStack.isEmpty()) {
            string action = undoStack.pop();
            redoStack.push(action);
            cout << "Undid action: " <<action << endl;
        } else {
            cout << "No actions to undo\n";
        }
    }
    void redo() {
        if (!redoStack.isEmpty()) {
           string action= redoStack.pop();
            undoStack.push(action);
            cout << "Redid action: " <<action << endl;
        } else {
            cout << "No actions to redo\n";
        }
	}
};
int main(){

    editorhistory editor;
    editor.typeword("Hello");
    editor.typeword("World");
    editor.undo();
    editor.redo();
    editor.undo();
    editor.undo();
    editor.redo();
    editor.redo();
	return 0;
}


//TASK 2


//class Process {
//public:
//    string pid;
//    int executiontime;
//    Process* next;
//
//    Process(string id, int et) {
//        pid = id;
//        executiontime = et;
//        next = nullptr;
//    }
//};
//
//
//class RoundRobinScheduler {
//public:
//    Process* head;
//    Process* tail;
//    Process* current;
//
//
//    RoundRobinScheduler() {
//        head = tail = current = nullptr;
//    }
//
//    
//    void addProcess(string pid, int executiontime) {
//        Process* newProc = new Process(pid, executiontime);
//
//        if (head == nullptr) {
//            head = tail = newProc;
//            newProc->next = head; 
//        }
//        else {
//            tail->next = newProc;
//            newProc->next = head;
//            tail = newProc;
//        }
//
//        if (current == nullptr)
//            current = head;
//
//        cout << "Added Process: " << pid << " (executiontime: " << executiontime << ")\n";
//    }
//    void cycle(int quantumtime) {
//		current->executiontime = current->executiontime - quantumtime;
//    }
//
//    
//    void removeCompleted() {
//        if (head == nullptr) return;
//
//        Process* temp = head;
//        Process* prev = tail;
//        bool looped = false;
//
//        do {
//            if (temp->executiontime <= 0) {
//                cout << "Process " << temp->pid << " completed and removed.\n";
//
//                if (temp == head && temp == tail) {
//                   
//                    delete temp;
//                    head = tail = current = nullptr;
//                    return;
//                }
//                else if (temp == head) {
//                    head = head->next;
//                    tail->next = head;
//                    if (current == temp) current = head;
//                    Process* toDelete = temp;
//                    temp = head;
//                    delete toDelete;
//                }
//                else if (temp == tail) {
//                    tail = prev;
//                    tail->next = head;
//                    if (current == temp) current = head;
//                    delete temp;
//                    break;
//                }
//                else {
//                    prev->next = temp->next;
//                    if (current == temp) current = temp->next;
//                    Process* toDelete = temp;
//                    temp = temp->next;
//                    delete toDelete;
//                    continue;
//                }
//            }
//            prev = temp;
//            temp = temp->next;
//
//            if (temp == head) looped = true;
//
//        } while (!looped);
//    }
//
//    
//    void displaycricle() {
//        if (head == nullptr) {
//            cout << "No processes in circle.\n";
//            return;
//        }
//
//        cout << "Current Processes in circle: ";
//        Process* temp = head;
//        do {
//            cout << temp->pid << "(" << temp->executiontime << ") ";
//            temp = temp->next;
//        } while (temp != head);
//        cout << endl;
//    }
//};
//int main() {
//    RoundRobinScheduler scheduler;
//    scheduler.addProcess("P1", 10);
//    scheduler.addProcess("P2", 4);
//    scheduler.addProcess("P3", 6);
//    int quantumtime = 2;
//    while (true) {
//        scheduler.displaycricle();
//        if (scheduler.head == nullptr) break;
//        scheduler.cycle(quantumtime);
//        scheduler.removeCompleted();
//    }
//    return 0;
//}