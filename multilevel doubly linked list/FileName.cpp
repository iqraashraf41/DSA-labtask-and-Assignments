#include<iostream>
using namespace std;

class node {
public:
	node* next;
	node* prev:
	node* child:
     int data;	
	node(int val) 
	{
		next = NULL;
		prev = NULL;
		child = NULL;
		data = val;
	}
};
class mldll
{
public:
	node* head;
	mldll()
	{
		head = NULL;
	}	
	void insertion(node* newnode) {
		if (head==NULL) {
			head = newnode;
			head->prev = head;
			head->next = head;
			return;
		}
		node* temp = head;
		while (temp != NULL) {
			temp->next = newnode;
			newnode->prev = temp;
			newnode = > next = NULL;
			return;



			temp = temp ->next;

		}
	}
	void display() {
		node* temp = head;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}




};
int main() {
	mldll list;
	node* n1 = new node(1);
	node* n2 = new node(2);
	node* n3 = new node(3);
	list.insertion(n1);
	list.insertion(n2);
	list.insertion(n3);
	cout << "initial list is : ";	
	list.display();
	
}