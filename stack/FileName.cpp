#include<iostream>
using namespace std;
class stack {
public:

	int capacity;
	int top;
	int* arr;
	stack(int cap) {
		capacity = cap;
		arr = new int[capacity];
		top = -1;

	}
	void push(int val) {
		if (!isfull()) {
			arr[++top] = val;
			/*display();*/
		}
		else
			cout << "Stack Overflow" << endl;

	}
	int pop() {
		if (!isempty()) {
			return arr[top--];
			/*cout << " after popping te stack is : " << endl;;
			display();*/
		}
		else
			return -1;
		
	}
		
	int peek() {
		return arr[top];
	}
	int getsize() {

		return top + 1;
	}
    bool isfull() {
		if (top == capacity - 1) {
			return true;
		}
		else return false;

	}
	bool isempty() {
		if (top == -1) {
			return true;
		}
		else return false;

	}
	void  display() {
		for (int i = top; i >= 0; i--) {
			cout << arr[i] << " " ;
		}cout<<endl;
		
	}


};
int main() {
	stack s(10);
	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);
	s.push(50);
	s.display();
	cout << "Top element is: " << s.peek() << endl;
	cout << "Stack size is: " << s.getsize() << endl;
	/*int arr[5]; 
	for (int i = 0; i < 5; i++) {
		arr[i] = s.pop();
	}
	cout << "the array is : ";	
	for (int i = 0; i < 5; i++) {
		cout<<arr[i] ;
	}*/
	/*s.pop();*/
	/*s.pop();
	s.pop();
	s.pop();*/
	/*cout << "Popped element is: " << s.pop() << s.pop() << s.pop() << s.pop() << s.pop() << endl;*/
	cout << "the pooping element is : ";	
	cout<< s.pop() << endl; 
	s.display();
	/*cout << s.pop() << endl;
	cout<< s.pop() << endl;
	cout << s.pop() << endl;*/
	return 0;
}


//class node {
//public:
//	node* next;
//	char data;
//	node( char val) {
//		next = NULL;
//		data = val;
//	}
//
// };
//class stack {
//public:
//	node* head;
//	stack() {
//		head = NULL;
//	}
//	void push(node* newnode) {
//		if (head == NULL) {
//			head = newnode;
//
//		}
//		else
//			newnode->next = head;
//		head = newnode;
//
//	}
//	char pop() {
//		if (head == NULL) {
//			return NULL;
//		}
//		else {
//			int val = head->data;
//			node* temp = head;
//			head = head->next;
//			delete temp;
//			return val;
//		
//		}
//	}
//	char peek() {
//		if (head == NULL) {
//			return -1;
//		}
//		else {
//			return head->data;
//		}
//	}
//	int getsize() {
//		int count = 0;	
//		node* rptr = head;
//		while (rptr != NULL)
//		{
//			rptr = rptr->next;
//			count++;
//		} 
//		return count;
//	}
//	
//	void display() {
//		node* rptr = head;	
//		while (rptr != NULL) {
//			cout << rptr->data << " ";
//			rptr = rptr->next;
//		}cout << endl;
//	}
//
//};
//int main() {
//	stack s;
//	node* n1 = new node('h');
//	node* n2 = new node('e');
//	node* n3 = new node('l');
//	node* n4= new node('l');
//	node* n5 = new node('o');
//	s.push(n1);
//	s.push(n2);
//	s.push(n3);
//	s.push(n4);
//	s.push(n5);
//	cout << "the size of  stack is : "<<s.getsize()<<endl;
//	s.display();
//	cout << "the top of the stack is : " << s.peek() << endl;
//	
//	cout << "the popping element is  :  "<<s.pop() << endl;
//	s.display();
//	return 0;
//}
