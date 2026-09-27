#include <iostream> 
using namespace std;
/*class ArrayList {
private:
    int* data;
    int size;
    int capacity;

public:
    ArrayList(int cap = 5) {
        capacity = cap;
        size = 0;
        data = new int[capacity];
    }

    void add(int value) {
        if (size == capacity) {
            cout << "List is full, resizing...\n";
            resize();
        }
        data[size++] = value;
    }
    void insert(int index, int value) {
        if (index < 0 || index > size) {
            cout << "Invalid index!\n";
            return;
        }
        if (size == capacity) resize();

        for (int i = size; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        size++;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!\n";
            return;
        }
        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];
        size--;
    }

    int get(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!\n";
            return -1;
        }
        return data[index];
    }
    void print() {
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }
    void resize() {
        int newCap = capacity * 2;
        int* newData = new int[newCap];
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }
};
int main() {
    ArrayList list;
    list.add(10);
    list.add(20);
    list.add(30);
    list.print();
    list.insert(1, 15);
    list.print();
    list.remove(2);
    list.print();
    cout << "Element at index 1: " << list.get(1) << endl;
    return 0;
} */ 

//task 1

class arraylist1 {
private:
    int* data;
    int size;
    int capacity;
public:
    arraylist1(int cap = 5) {
        capacity = cap;
        size = 0;
        data = new int[capacity];
    }
    void add(int value) {
        if (size == capacity) {
            cout << "List is full, resizing...\n";
            resize();
        }
        data[size++] = value;
    }
    void print() {
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }
    bool isempty() {
        return size == 0;
    }
    void search(int x) {
        bool found = false;
        if (isempty()) {
            cout << "the array is empty";

        }
        for (int i = 0; i < size; i++) {
            if (data[i] == x) {
               
                found = true;
                cout << "found at index " << i << endl;
			} 
        }
        if (!found)
            cout << "not found"<< endl;;
        
       
        
    }
    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!\n";
            return;
        }
        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];
        size--;
    }
    void resize() {
        int newCap = capacity * 2;
        int* newData = new int[newCap];
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }
    void even_and_odd() {
       int countE = 0, countO = 0;
        if (isempty()) {
            cout << "the array is empty";

        }
        for (int i = 0; i < size; i++) {
            if (data[i] % 2 == 0) {
                countE++;

            }
            else
                countO++;
        }
        cout << "even no are" << countE << endl;
        cout << "ODD no are" << countO << endl;
    }

}; 
int main() {
    arraylist1 al;
    al.add(6);
    al.add(7);
    al.add(8);
    al.add(9);
    al.add(10);
    al.add(11);
    al.add(12);
    al.print();
    al.search(9);
    cout << "the updated list is" << endl;
    al.print();
    al.even_and_odd();
}