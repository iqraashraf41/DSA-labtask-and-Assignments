#include<iostream>
using namespace std;

class node {
public:
	node* next;
	node* prev;
	node * child;
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
		if (head == NULL) {
			head = newnode;
		}
		else {
			node* rptr = head;
			while (rptr->next != NULL) {
				rptr = rptr->next;
			}
			rptr->next = newnode;
			newnode->prev = rptr;
			newnode->next = NULL;

		}
	}

	void flatten() {
		node* temp = head;
		while (temp != NULL) {
			if (temp->child != NULL) {
				node* childhead = temp->child;
				node* nextnode = temp->next;
				temp->next = childhead;
				childhead->prev = temp;
				temp->child = NULL;
				node* ctemp = childhead;
				while (ctemp->next != NULL) {
					ctemp = ctemp->next;
				}
				ctemp->next = nextnode;
				if (nextnode != NULL) {
					nextnode->prev = ctemp;
				}
			}
			temp = temp->next;
		}
	}	
	
	void display() {
		node* temp = head;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}cout << endl;	
	}




};
int main() {
	mldll list;
	node* n1 = new node(1);
	node* n2 = new node(2);
	node* n3 = new node(3);
	node* n4 = new node(4);
	node* n5 = new node(5);
	node* n6 = new node(6);
	list. insertion(n1);
	list.insertion(n2);
	list.insertion(n3);
	list.insertion(n4);
	list.insertion(n5);
	list.insertion(n6);
	cout << "initial list is : ";
	list.display();

	
	mldll childlist1;
	
	node* c1 = new node(7);
	node* c2 = new node(8);
	node* c3 = new node(9);
	node* c4 = new node(10);
	childlist1.insertion(c1);
	childlist1.insertion(c2);
	childlist1.insertion(c3);
	childlist1.insertion(c4);
	n3->child = childlist1.head;
	cout << "childe list 1 is" << endl;
	childlist1.display();
	mldll childlist2;
	node* cc1 = new node(11);
	node* cc2 = new node(12);
	
	childlist2.insertion(cc1);
	childlist2.insertion(cc2);
	c2->child = childlist2.head;
	cout << "childe list 2 is" << endl;
	childlist2.display();
	list.flatten();
	list.display();


}