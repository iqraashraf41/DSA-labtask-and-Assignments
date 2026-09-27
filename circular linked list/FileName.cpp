#include<iostream>
using namespace std;	



class snode {
public:
	int data;
	snode* prevnode;
	snode* nextnode;
	snode() { data = 0; }
	snode(int data) {
		this->data = data;
		nextnode = NULL;
		prevnode = NULL;
	}

};
class dcllint {
public:
	snode* tailptr;
	dcllint() {
		tailptr = NULL;
	}
	void insert(snode* newnode) {
		if (tailptr == NULL) {
			tailptr = newnode;
			tailptr->prevnode = tailptr;
			tailptr->nextnode = tailptr;

		}
		else {
			newnode->prevnode = tailptr;
			newnode->nextnode = tailptr->nextnode;
			tailptr->nextnode->prevnode = newnode;
			tailptr->nextnode = newnode;
			tailptr = newnode;
			

		

		}
	}
	
	void display() {
		snode* rptr =tailptr->nextnode;
		cout << " data     " << "prev   "<<"                    current" << "                   next" << endl;
		do {
			
			cout << rptr->data << "->     " << rptr->prevnode <<"     "<<rptr<<"        " <<rptr->nextnode << endl;
			rptr = rptr->nextnode;
		} while (rptr!= tailptr->nextnode);
	}

	void insert_at_start(snode* newnode) {
		if (tailptr == NULL) {
			tailptr = newnode;
			tailptr->prevnode = newnode;
			tailptr->nextnode = newnode;

		}
		else {
			newnode->prevnode = tailptr;
			newnode->nextnode = tailptr->nextnode;
			tailptr->nextnode->prevnode = newnode;
			tailptr->nextnode = newnode;

		}

	}
	void insert_at_end(snode* newnode) {
		if (tailptr == NULL) {
			tailptr = newnode;
			tailptr->prevnode = tailptr;
			tailptr->nextnode = tailptr;

		}
		else {
			newnode->nextnode = tailptr->nextnode;
			tailptr->nextnode = newnode;
			newnode->prevnode = tailptr;
			
			tailptr->nextnode->prevnode = newnode;
			tailptr = newnode;

		}
	}

	void insert_at_anyposition(snode* newnode, int index) {
		if (index==1) {
				insert_at_start(newnode);
				return;
			}

			int count = 1;
			snode* rptr = tailptr->nextnode;
			while (count<index-1&&rptr!=tailptr) {
				rptr = rptr->nextnode;
				count++;
			}
			
			if (rptr==tailptr ){
				insert_at_end(newnode);
				return;
			}

			// Insert the new node
			newnode->nextnode = rptr->nextnode;
			newnode->prevnode = rptr;
			rptr->nextnode->prevnode = newnode;
			rptr->nextnode = newnode;




	}
	int getsize() {
		int count = 0;
		snode* rptr = tailptr->nextnode;
		do {
			count++;
			rptr = rptr->nextnode;
		} while (rptr != tailptr->nextnode);
		return count;
	}
		void search(int x){
			
			snode* rptr = tailptr->nextnode;
			while (rptr != tailptr) {
				if (rptr->data == x) {
					cout << "the element found" << endl;
				}
				rptr = rptr->nextnode;
			}
			cout << "the element not found" << endl;
		}
	//
	//int searchindex(int x) {
	//	int count = 1;
	//	snode* rptr = headptr;
	//	while (rptr != NULL) {
	//		if (rptr->data == x) {
	//			return count;
	//		}
	//		rptr = rptr->nextnode;
	//		count++;
	//	}
	//	return NULL;
	//}
	snode* delete_at_start() {
		tailptr->nextnode = tailptr->nextnode->nextnode;
		tailptr->nextnode->prevnode = tailptr;	
		return tailptr->nextnode;

		
	}
	//snode* delete_at_end() {
	//	/*snode* dptr = headptr;*/
	//	snode* rptr = headptr;
	//	if (headptr != NULL) {

	//		while (rptr->nextnode->nextnode != NULL) {
	//			/*dptr = rptr;*/
	//			rptr = rptr->nextnode;
	//		}
	//		rptr->nextnode = NULL;
	//		/*	dptr->nextnode = NULL;*/


	//	}return rptr;
	//}
	//snode* delete_at_anyindex(int index) {
	//	int count = 1;
	//	snode* rptr = headptr;


	//	if (headptr != NULL) {
	//		while (rptr->nextnode != NULL && count < index) {


	//			rptr = rptr->nextnode;
	//			count++;
	//		}if (count == 1) {
	//			headptr = headptr->nextnode;
	//			headptr->prevnode = NULL;
	//			return rptr;
	//		}
	//		if (rptr->nextnode == NULL) {
	//			delete_at_end();
	//		}
	//		rptr->prevnode->nextnode = rptr->nextnode;
	//		rptr->nextnode->prevnode = rptr->prevnode;
	//		rptr->nextnode = NULL;
	//		rptr->prevnode = NULL;


	//	}return rptr;
	//}
	//void delete_with_data(int x) {

	//	snode* rptr = headptr;
	//	if (headptr != NULL) {

	//		while (rptr->nextnode != NULL && rptr->data != x) {


	//			rptr = rptr->nextnode;
	//		}if (rptr == headptr) {
	//			headptr = headptr->nextnode;
	//			headptr->prevnode = NULL;

	//		}
	//		if (rptr->nextnode == NULL) {
	//			delete_at_end();
	//		}
	//		rptr->prevnode->nextnode = rptr->nextnode;
	//		rptr->nextnode->prevnode = rptr->prevnode;
	//		rptr->nextnode = NULL;
	//		rptr->prevnode = NULL;

	//	}
	//}
	//void displayeven() {
	//	int count = 0;
	//	snode* rptr = headptr;
	//	while (rptr->nextnode != NULL) {
	//		if (count % 2 == 0) {
	//			cout << rptr->data << "->";
	//		}
	//		rptr = rptr->nextnode;
	//		count++;
	//	}cout << "null" << endl;
	//}
	//void displayskipnode(int n) {
	//	int count = 1;
	//	snode* rptr = headptr;
	//	while (rptr != NULL) {
	//		if (count % (n + 1) == 0) {
	//			cout << rptr->data << "->";
	//		}
	//		rptr = rptr->nextnode;
	//		count++;
	//	}
	//	cout << "null" << endl;
	//}
	//void displayreverse() {

	//	snode* temp = headptr;
	//	while (temp->nextnode != NULL) {

	//	temp = temp->nextnode;

	//	}cout << temp->data << "->";
	//	while (temp->prevnode != NULL)
	//	{
	//		cout << temp->prevnode->data << "->";
	//		temp = temp->prevnode;
	//	}
	//	cout << endl;

	//while (temp != headptr) {
	//		snode* rptr = headptr;
	//		while (rptr->nextnode != temp) {
	//			rptr = rptr->nextnode;

	//		}cout << rptr->data << "->";

	//	temp = rptr;

	//	}cout << "NULL" << endl;*/
	//}
	//void twopoint() {
	//	snode* optr = headptr;
	//	snode* tptr = headptr;
	//	cout << "one pointer is" << endl;
	//	while (optr != NULL) {
	//		cout << optr->data << "->";
	//		optr = optr->nextnode;
	//	}cout << "NULL" << endl;
	//	cout << "two pointer is" << endl;
	//	while (tptr != NULL) {
	//		cout << tptr->data << "->";
	//		tptr = tptr->nextnode->nextnode;
	//	}cout << "NULL" << endl;

	//	cout << "the middle is" << optr->data;
	//}
	//void printlist2(snode* p) {
	//	if (p != NULL) {
	//		cout << (p->data);
	//		printlist2(p->nextnode);
	//		cout << (p->data);
	//	}


	//}
	//int findMiddle() {
	//	if (!headptr) return -1;

	//	snode* slow = headptr;
	//	snode* fast = headptr;

	//	while (fast && fast->nextnode) {
	//		slow = slow->nextnode;
	//		fast = fast->nextnode->nextnode;
	//	}

	//	// 'slow' is now at the middle
	//	return slow->data;;
	//}

	//void moveLastToFront(snode*& headptr) {
	//	snode* rptr = headptr;
	//	while (rptr->nextnode != NULL) {
	//		rptr = rptr->nextnode;
	//	}
	//	headptr->prevnode = rptr;
	//	rptr->prevnode->nextnode = NULL;
	//	rptr->nextnode = headptr;
	//	headptr = rptr;
	//	snode* last = rptr;
	//}
	//void reverse(snode*& head) {
	//	snode* temp = NULL;
	//	snode* current = head;

	//	
	//	while (current != NULL) {
	//		temp = current->prevnode;
	//		current->prevnode = current->nextnode;
	//		current->nextnode = temp;
	//		current = current->prevnode; 
	//	}

	//
	//	if (temp != NULL)
	//		head = temp->prevnode;
	//}


};

int main() {
	dcllint list;
	snode* n1 = new snode(10);
	snode* n2 = new snode(20); 
	snode* n3 = new snode(30); 
	snode* n4 = new snode(40);
	snode* n5 = new snode(50);
	snode* n6 = new snode(60);
	snode* n7 = new snode(70);
	snode* n8 = new snode(80);
	snode* n9 = new snode(90);
	snode* n10 = new snode(100);
	snode* n11 = new snode(110);

	// Insert few nodes
	list.insert(n1);
	list.insert(n2);
	list.insert(n3);
	list.insert(n4);
	list.insert(n5);
	list.insert(n6);
	list.insert(n7);
	list.insert(n8);
	list.insert(n9);
	list.insert(n10);
	list.insert(n11);


	cout << "Initial list:\n";
	list.display();
	cout << "insertion at start is" << endl;
	list.insert_at_start(new snode(5));
	list.display();
	list.insert_at_end(new snode(120));
	cout << "insertion at end is" << endl;
	list.display();
	cout<<"insertion at any positin is"<<endl;	
	list.insert_at_anyposition(new snode(55), 6);
	list.display();
	cout << "delete at start is" << endl;	
	list.delete_at_start();
	list.display();
	/*cout << "reverse list is" << endl;
	list.displayreverse();
	cout << "deletion at end is" << endl;
	list.delete_at_end();
	list.display();*/
	/*cout << "deletion atany index is" << endl;
	list.delete_at_anyindex(4);
	list.display();*/

	/*cout << "the even nodes are" << endl;
	list.displayeven();
	cout << "the skip nodes list are" << endl;
	list.displayskipnode(4);
	list.displayreverse();
	list.twopoint();
	int now = list.findMiddle();
	cout << "the middle node is " << now << endl;*/
	/*list.moveLastToFront(list.headptr);
	list.display();*/


	return 0;
}
