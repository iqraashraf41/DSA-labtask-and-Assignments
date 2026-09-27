#include<iostream>
using namespace std;



//class Stack {
//private:
//    int top;
//    int arr[100];
//public:
//    Stack() {
//        top = -1;
//    }
//
//    void push(int x) {
//        if (top == 99) {
//            cout << "Stack Overflow\n";
//            return;
//        }
//        arr[++top] = x;
//    }
//
//    int pop() {
//        if (top == -1) {
//            cout << "Stack Underflow\n";
//            return -1;
//        }
//        return arr[top--];
//    }
//
//    bool isEmpty() {
//        return top == -1;
//    }
//};


//class GeneralQueue {
//    private:
//        int front, rear, size;
//        int arr[100];   
//    
//    public:
//        GeneralQueue() {
//            front = 0;
//            rear = -1;
//            size = 0;
//        }
//    
//        void enqueue(int id) {
//            if (size == 100) {
//                cout << "Queue full! Cannot enqueue.\n";
//                return;
//            }
//            arr[++rear] = id;
//            size++;
//        }
//    
//        int dequeue() {
//            if (size == 0)
//                return -1;
//    
//            int id = arr[front++];
//            size--;
//            return id;
//        }
//    
//        bool isEmpty() {
//            return size == 0;
//        }
//    
//        void show() {
//            cout << "GeneralQueue: ";
//            for (int i = front; i <= rear; i++)
//                cout << arr[i] << " ";
//            cout << "\n";
//        }
//    };
//
//class patientrouting {
//public:
//    Stack emergencyStack;
//    GeneralQueue generalQueue;
//    void arrivePatient(int id,string condition) {
//		string conditions=condition;
//		bool isCritical = (conditions == "critical");
//        if (isCritical) {
//            emergencyStack.push(id);
//        } else {
//            generalQueue.enqueue(id);
//        }
//    }
//    int attendPatient() {
//        if (!emergencyStack.isEmpty()) {
//            return emergencyStack.pop();
//        } else if (!generalQueue.isEmpty()) {
//            return generalQueue.dequeue();
//        } else {
//            return -1; // No patients to attend
//        }
//	}
//};
//int main() {
//    patientrouting pr;
//    pr.arrivePatient(101, "normal");
//    pr.arrivePatient(102, "normal");
//    pr.arrivePatient(103, "critical");
//    pr.arrivePatient(104, "normal");
//	pr.arrivePatient(105, "critical");
//
//    cout << "Attending Patient ID: " << pr.attendPatient() << "\n"; 
//    cout << "Attending Patient ID: " << pr.attendPatient() << "\n"; 
//    cout << "Attending Patient ID: " << pr.attendPatient() << "\n"; 
//    cout << "Attending Patient ID: " << pr.attendPatient() << "\n"; 
//    cout << "Attending Patient ID: " << pr.attendPatient() << "\n"; 
//    return 0;
//}


//#include <iostream>
//#include <string>
//using namespace std;
//
//// Node of Doubly Linked List
//class Node {
//public:
//    string title;
//    Node* next;
//    Node* prev;
//
//    Node(string t) {
//        title = t;
//        next = nullptr;
//        prev = nullptr;
//    }
//};
//
//// Playlist Class
//class Playlist {
//private:
//    Node* head;
//    Node* tail;
//    Node* current;
//
//public:
//    Playlist() {
//        head = tail = current = nullptr;
//    }
//
//    // Add song at end
//    void addSong(string title) {
//        Node* newSong = new Node(title);
//
//        if (head == nullptr) {       // first song
//            head = tail = current = newSong;
//        }
//        else {
//            tail->next = newSong;
//            newSong->prev = tail;
//            tail = newSong;
//        }
//
//        cout << "Added: " << title << endl;
//    }
//
//    // Move to next song
//    void nextSong() {
//        if (current == nullptr) {
//            cout << "Playlist is empty!\n";
//            return;
//        }
//
//        if (current->next != nullptr) {
//            current = current->next;
//            cout << "Now Playing: " << current->title << endl;
//        }
//        else {
//            cout << "You are already at the last song.\n";
//        }
//    }
//
//    // Move to previous song
//    void prevSong() {
//        if (current == nullptr) {
//            cout << "Playlist is empty!\n";
//            return;
//        }
//
//        if (current->prev != nullptr) {
//            current = current->prev;
//            cout << "Now Playing: " << current->title << endl;
//        }
//        else {
//            cout << "You are already at the first song.\n";
//        }
//    }
//
//    // Delete the current song
//    void deleteCurrentSong() {
//        if (current == nullptr) {
//            cout << "Playlist is empty!\n";
//            return;
//        }
//
//        cout << "Deleted: " << current->title << endl;
//
//        Node* toDelete = current;
//
//        // case 1: only one song
//        if (head == tail) {
//            head = tail = current = nullptr;
//        }
//
//        // case 2: deleting head
//        else if (current == head) {
//            head = head->next;
//            head->prev = nullptr;
//            current = head;
//        }
//
//        // case 3: deleting tail
//        else if (current == tail) {
//            tail = tail->prev;
//            tail->next = nullptr;
//            current = tail;
//        }
//
//        // case 4: deleting middle
//        else {
//            current->prev->next = current->next;
//            current->next->prev = current->prev;
//            current = current->next;   // move forward
//        }
//
//        delete toDelete;
//    }
//
//    // Show current song
//    void showCurrent() {
//        if (current == nullptr)
//            cout << "No song is playing.\n";
//        else
//            cout << "Now Playing: " << current->title << endl;
//    }
//};
//
//// MAIN (Example Usage)
//int main() {
//    Playlist p;
//
//    p.addSong("Song A");
//    p.addSong("Song B");
//    p.addSong("Song C");
//
//    cout << endl;
//    p.showCurrent();
//
//    p.nextSong();
//    p.nextSong();
//    p.prevSong();
//
//    cout << "\nDeleting Current...\n";
//    p.deleteCurrentSong();
//    p.showCurrent();
//
//    return 0;
//}



#include <iostream>
using namespace std;

//class CircularQueue {
//private:
//    string arr[4];
//    int front, rear, size, capacity;
//
//public:
//    CircularQueue() {
//        capacity = 4;
//        front = 0;
//        rear = -1;
//        size = 0;
//    }
//
//    // Insert flight
//    void enqueue(string flightID) {
//        if (size == capacity) {
//            cout << "Runway Full - Flight Delayed: " << flightID << endl;
//            return;
//        }
//        rear = (rear + 1) % capacity;
//        arr[rear] = flightID;
//        size++;
//
//        cout << "Added Flight: " << flightID << endl;
//    }
//
//    // Remove flight (takeoff)
//    string dequeue() {
//        if (size == 0) {
//            cout << "No flights waiting!\n";
//            return "";
//        }
//
//        string flight = arr[front];
//        front = (front + 1) % capacity;
//        size--;
//
//        cout << "Flight Took Off: " << flight << endl;
//        return flight;
//    }
//
//    // Display flights waiting
//    void display() {
//        if (size == 0) {
//            cout << "No flights in queue.\n";
//            return;
//        }
//
//        cout << "Flights Waiting: ";
//        int i = front;
//        for (int count = 0; count < size; count++) {
//            cout << arr[i] << " ";
//            i = (i + 1) % capacity;
//        }
//        cout << endl;
//    }
//};
//
//// SIMULATION
//int main() {
//    CircularQueue runway;
//
//    // Initial flights
//    runway.enqueue("F1");
//    runway.enqueue("F2");
//    runway.enqueue("F3");
//    runway.enqueue("F4");
//
//    // Queue is full ? F5 should be delayed
//    runway.enqueue("F5");
//
//    // Two takeoffs
//    runway.dequeue();
//    runway.dequeue();
//
//    // Add new flights
//    runway.enqueue("F6");
//    runway.enqueue("F7");
//
//    // Final Display
//    cout << "\nFinal Flight Queue:\n";
//    runway.display();
//
//    return 0;
//}




//#include <iostream>
//#include <string>
//using namespace std;
//
//// Node of Circular Linked List
//class Process {
//public:
//    string pid;
//    int burstTime;
//    Process* next;
//
//    Process(string id, int bt) {
//        pid = id;
//        burstTime = bt;
//        next = nullptr;
//    }
//};
//
//// CPU Scheduler Class
//class RoundRobinScheduler {
//private:
//    Process* head;
//    Process* tail;
//    Process* current;
//
//public:
//    RoundRobinScheduler() {
//        head = tail = current = nullptr;
//    }
//
//    // Add process to circular list
//    void addProcess(string pid, int burstTime) {
//        Process* newProc = new Process(pid, burstTime);
//
//        if (head == nullptr) {
//            head = tail = newProc;
//            newProc->next = head; // circular
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
//        cout << "Added Process: " << pid << " (Burst: " << burstTime << ")\n";
//    }
//
//    // Execute one time slice
//    void execute() {
//        if (current == nullptr) {
//            cout << "No processes to execute.\n";
//            return;
//        }
//
//        cout << "Executing Process: " << current->pid << " (Remaining Burst: " << current->burstTime << ")\n";
//        current->burstTime -= 1;
//
//        // Move to next process for next cycle
//        current = current->next;
//
//        removeCompleted(); // Remove completed processes after execution
//    }
//
//    // Remove processes with burstTime = 0
//    void removeCompleted() {
//        if (head == nullptr) return;
//
//        Process* temp = head;
//        Process* prev = tail;
//        bool looped = false;
//
//        do {
//            if (temp->burstTime <= 0) {
//                cout << "Process " << temp->pid << " completed and removed.\n";
//
//                if (temp == head && temp == tail) {
//                    // only one process
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
//    // Display the circular queue
//    void displayQueue() {
//        if (head == nullptr) {
//            cout << "No processes in queue.\n";
//            return;
//        }
//
//        cout << "Current Processes in Queue: ";
//        Process* temp = head;
//        do {
//            cout << temp->pid << "(" << temp->burstTime << ") ";
//            temp = temp->next;
//        } while (temp != head);
//        cout << endl;
//    }
//};
//
//// MAIN function
int main() {
    RoundRobinScheduler scheduler;

    // Add processes
    scheduler.addProcess("P1", 3);
    scheduler.addProcess("P2", 2);
    scheduler.addProcess("P3", 4);

    cout << endl;
    scheduler.displayQueue();
    cout << "\n--- Starting Round-Robin Execution ---\n";

    // Execute cycles until all processes are done
    while (true) {
        if (scheduler.head == nullptr) break;

        scheduler.execute();
        scheduler.displayQueue();
        cout << "-------------------------\n";
    }

    cout << "All processes completed.\n";

    return 0;
}




#include <iostream>
#include <string>
using namespace std;

// Node of Circular Linked List
class Song {
public:
    string name;
    int duration; // in minutes
    Song* next;

    Song(string n, int d) {
        name = n;
        duration = d;
        next = nullptr;
    }
};

// Jukebox Playlist Class
class Jukebox {
private:
    Song* head;
    Song* tail;
    Song* current; // Currently playing song

public:
    Jukebox() {
        head = tail = current = nullptr;
    }

    // Add song to playlist
    void addSong(string name, int duration) {
        Song* newSong = new Song(name, duration);

        if (head == nullptr) {
            head = tail = current = newSong;
            newSong->next = head; // circular link
        }
        else {
            tail->next = newSong;
            newSong->next = head;
            tail = newSong;
        }

        cout << "Added Song: " << name << " (" << duration << " min)" << endl;
    }

    // Play next song
    void playNext() {
        if (current == nullptr) {
            cout << "No songs in playlist!\n";
            return;
        }

        cout << "Now Playing: " << current->name << " (" << current->duration << " min)" << endl;
        current = current->next; // move to next song
    }

    // Remove a song by name
    void removeSong(string name) {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        Song* temp = head;
        Song* prev = tail;
        bool found = false;

        do {
            if (temp->name == name) {
                found = true;
                cout << "Removed Song: " << name << endl;

                // Only one song
                if (head == tail) {
                    delete temp;
                    head = tail = current = nullptr;
                }
                // Removing head
                else if (temp == head) {
                    head = head->next;
                    tail->next = head;
                    if (current == temp) current = head;
                    delete temp;
                }
                // Removing tail
                else if (temp == tail) {
                    tail = prev;
                    tail->next = head;
                    if (current == temp) current = head;
                    delete temp;
                }
                // Removing middle
                else {
                    prev->next = temp->next;
                    if (current == temp) current = temp->next;
                    delete temp;
                }

                return;
            }

            prev = temp;
            temp = temp->next;
        } while (temp != head);

        if (!found) cout << "Song " << name << " not found!\n";
    }

    // Display playlist
    void showPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "Playlist: ";
        Song* temp = head;
        do {
            cout << temp->name << "(" << temp->duration << " min) ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

// MAIN function (Simulation)
int main() {
    Jukebox jukebox;

    // Add songs
    jukebox.addSong("Song A", 3);
    jukebox.addSong("Song B", 4);
    jukebox.addSong("Song C", 2);

    cout << endl;
    jukebox.showPlaylist();
    cout << "\n--- Playing 5 songs ---\n";

    for (int i = 0; i < 5; i++) {
        jukebox.playNext();
    }

    cout << "\n--- Remove Song B ---\n";
    jukebox.removeSong("Song B");
    jukebox.showPlaylist();

    cout << "\n--- Play 3 more songs ---\n";
    for (int i = 0; i < 3; i++) {
        jukebox.playNext();
    }

    return 0;
}





//#include <iostream>
//#include <string>
//using namespace std;
//
//// Node of Circular Linked List
//class Intersection {
//public:
//    string name;
//    Intersection* next;
//
//    Intersection(string n) {
//        name = n;
//        next = nullptr;
//    }
//};
//
//// Traffic System Class
//class TrafficSystem {
//private:
//    Intersection* head;
//    Intersection* tail;
//    Intersection* green; // Intersection with green light
//
//public:
//    TrafficSystem() {
//        head = tail = green = nullptr;
//    }
//
//    // Add intersection
//    void addIntersection(string name) {
//        Intersection* newInter = new Intersection(name);
//
//        if (head == nullptr) {
//            head = tail = green = newInter;
//            newInter->next = head; // circular
//        }
//        else {
//            tail->next = newInter;
//            newInter->next = head;
//            tail = newInter;
//        }
//
//        cout << "Added Intersection: " << name << endl;
//    }
//
//    // Move green light to next intersection
//    void nextGreen() {
//        if (green == nullptr) {
//            cout << "No intersections in system!\n";
//            return;
//        }
//
//        cout << "Green Light at: " << green->name << endl;
//        green = green->next;
//    }
//
//    // Remove intersection by name
//    void removeIntersection(string name) {
//        if (head == nullptr) {
//            cout << "No intersections to remove!\n";
//            return;
//        }
//
//        Intersection* temp = head;
//        Intersection* prev = tail;
//        bool found = false;
//
//        do {
//            if (temp->name == name) {
//                found = true;
//                cout << "Removed Intersection: " << name << endl;
//
//                // Only one intersection
//                if (head == tail) {
//                    delete temp;
//                    head = tail = green = nullptr;
//                }
//                // Removing head
//                else if (temp == head) {
//                    head = head->next;
//                    tail->next = head;
//                    if (green == temp) green = head;
//                    delete temp;
//                }
//                // Removing tail
//                else if (temp == tail) {
//                    tail = prev;
//                    tail->next = head;
//                    if (green == temp) green = head;
//                    delete temp;
//                }
//                // Removing middle
//                else {
//                    prev->next = temp->next;
//                    if (green == temp) green = temp->next;
//                    delete temp;
//                }
//                return;
//            }
//
//            prev = temp;
//            temp = temp->next;
//        } while (temp != head);
//
//        if (!found) cout << "Intersection " << name << " not found!\n";
//    }
//
//    // Display cycle
//    void displayCycle() {
//        if (head == nullptr) {
//            cout << "No intersections in cycle!\n";
//            return;
//        }
//
//        cout << "Intersection Cycle: ";
//        Intersection* temp = head;
//        do {
//            cout << temp->name << " ";
//            temp = temp->next;
//        } while (temp != head);
//        cout << endl;
//    }
//};
//
//// MAIN function (Simulation)
//int main() {
//    TrafficSystem ts;
//
//    // Add intersections
//    ts.addIntersection("A");
//    ts.addIntersection("B");
//    ts.addIntersection("C");
//    ts.addIntersection("D");
//
//    cout << endl;
//    ts.displayCycle();
//
//    cout << "\n--- Green light moves 6 times ---\n";
//    for (int i = 0; i < 6; i++) {
//        ts.nextGreen();
//    }
//
//    cout << "\n--- Remove Intersection C ---\n";
//    ts.removeIntersection("C");
//    ts.displayCycle();
//
//    cout << "\n--- Green light moves 5 times ---\n";
//    for (int i = 0; i < 5; i++) {
//        ts.nextGreen();
//    }
//
//    return 0;
//}
