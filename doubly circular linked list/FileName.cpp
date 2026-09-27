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
class dllint {
public:
	snode* headptr;
	dllint() {
		headptr = NULL;
	}
	void insert(snode* newnode) {
		if (headptr == NULL) {
			headptr = newnode;
			headptr->prevnode = headptr;
			headptr->nextnode = headptr;
		}
		else {
			snode* rptr = headptr;
			while (rptr->nextnode != NULL) {
				rptr = rptr->nextnode;
			}
			rptr->nextnode = newnode;
			newnode->prevnode = rptr;
			newnode->nextnode = headptr;
			headptr->prevnode = newnode;

		}
	}
	int getSize(snode* head) {
		int count = 0;
		snode* current = headptr;
		while (current != nullptr) {
			count++;
			current = current->nextnode;
		}
		return count;
	}
	void display() {
		snode* rptr = headptr;
		while (rptr != NULL) {
			cout << rptr->data << "->" << rptr << endl;
			rptr = rptr->nextnode;
		}cout << "null" << endl;
	}

	void insert_at_start(snode* newnode) {
		if (headptr == NULL) {
			headptr = newnode;
			return;
		}
		if (headptr != NULL) {
			newnode->nextnode = headptr;
			headptr->prevnode = newnode;
			headptr = newnode;
		}

	}
	void insert_at_end(snode* newnode) {
		if (headptr == NULL) {
			headptr = newnode;
			return;
		}
		snode* rptr = headptr;

		while (rptr->nextnode != NULL) {
			rptr = rptr->nextnode;

		}
		rptr->nextnode = newnode;
		newnode->prevnode = rptr;
		newnode->nextnode = NULL;
	}

	void insert_at_anyposition(snode* newnode, int index) {


		int count = 1;
		snode* rptr = headptr;

		// Traverse to the node before the given position
		while (rptr->nextnode != NULL && count < index) {
			rptr = rptr->nextnode;
			count++;
		}if (count == 1) {
			insert_at_start(newnode);
			return;
		}if (rptr->nextnode == NULL) {
			insert_at_end(newnode);
			return;
		}

		// Insert the new node
		newnode->nextnode = rptr->nextnode;
		newnode->prevnode = rptr;
		rptr->nextnode->prevnode = newnode;
		rptr->nextnode = newnode;




	}

	void search(int x) {
		snode* rptr = headptr;
		while (rptr != NULL) {
			if (rptr->data == x) {
				cout << "the element found" << endl;
			}
			rptr = rptr->nextnode;
		}
		cout << "the element not found" << endl;
	}
	int searchindex(int x) {
		int count = 1;
		snode* rptr = headptr;
		while (rptr != NULL) {
			if (rptr->data == x) {
				return count;
			}
			rptr = rptr->nextnode;
			count++;
		}
		return NULL;
	}
	snode* delete_at_start() {
		snode* dptr = headptr;
		if (headptr != NULL) {

			headptr = headptr->nextnode;
			headptr->nextnode->prevnode = NULL;


		}return dptr;
	}
	snode* delete_at_end() {
		/*snode* dptr = headptr;*/
		snode* rptr = headptr;
		if (headptr != NULL) {

			while (rptr->nextnode->nextnode != NULL) {
				/*dptr = rptr;*/
				rptr = rptr->nextnode;
			}
			rptr->nextnode = NULL;
			/*	dptr->nextnode = NULL;*/


		}return rptr;
	}
	snode* delete_at_anyindex(int index) {
		int count = 1;
		snode* rptr = headptr;


		if (headptr != NULL) {
			while (rptr->nextnode != NULL && count < index) {


				rptr = rptr->nextnode;
				count++;
			}if (count == 1) {
				headptr = headptr->nextnode;
				headptr->prevnode = NULL;
				return rptr;
			}
			if (rptr->nextnode == NULL) {
				delete_at_end();
			}
			rptr->prevnode->nextnode = rptr->nextnode;
			rptr->nextnode->prevnode = rptr->prevnode;
			rptr->nextnode = NULL;
			rptr->prevnode = NULL;


		}return rptr;
	}
	void delete_with_data(int x) {

		snode* rptr = headptr;
		if (headptr != NULL) {

			while (rptr->nextnode != NULL && rptr->data != x) {


				rptr = rptr->nextnode;
			}if (rptr == headptr) {
				headptr = headptr->nextnode;
				headptr->prevnode = NULL;

			}
			if (rptr->nextnode == NULL) {
				delete_at_end();
			}
			rptr->prevnode->nextnode = rptr->nextnode;
			rptr->nextnode->prevnode = rptr->prevnode;
			rptr->nextnode = NULL;
			rptr->prevnode = NULL;

		}
	}
	void displayeven() {
		int count = 0;
		snode* rptr = headptr;
		while (rptr->nextnode != NULL) {
			if (count % 2 == 0) {
				cout << rptr->data << "->";
			}
			rptr = rptr->nextnode;
			count++;
		}cout << "null" << endl;
	}
	void displayskipnode(int n) {
		int count = 1;
		snode* rptr = headptr;
		while (rptr != NULL) {
			if (count % (n + 1) == 0) {
				cout << rptr->data << "->";
			}
			rptr = rptr->nextnode;
			count++;
		}
		cout << "null" << endl;
	}
	void displayreverse() {

		snode* temp = headptr;
		while (temp->nextnode != NULL) {

			temp = temp->nextnode;

		}cout << temp->data << "->";
		while (temp->prevnode != NULL)
		{
			cout << temp->prevnode->data << "->";
		}


		while (temp != headptr) {
			snode* rptr = headptr;
			while (rptr->nextnode != temp) {
				rptr = rptr->nextnode;

			}cout << rptr->data << "->";

			temp = rptr;

		}cout << "NULL" << endl;
	}
	void twopoint() {
		snode* optr = headptr;
		snode* tptr = headptr;
		cout << "one pointer is" << endl;
		while (optr != NULL) {
			cout << optr->data << "->";
			optr = optr->nextnode;
		}cout << "NULL" << endl;
		cout << "two pointer is" << endl;
		while (tptr != NULL) {
			cout << tptr->data << "->";
			tptr = tptr->nextnode->nextnode;
		}cout << "NULL" << endl;

		cout << "the middle is" << optr->data;
	}
	void printlist2(snode* p) {
		if (p != NULL) {
			cout << (p->data);
			printlist2(p->nextnode);
			cout << (p->data);
		}


	}
	int findMiddle() {
		if (!headptr) return -1;

		snode* slow = headptr;
		snode* fast = headptr;

		while (fast && fast->nextnode) {
			slow = slow->nextnode;
			fast = fast->nextnode->nextnode;
		}

		// 'slow' is now at the middle
		return slow->data;;
	}

	void moveLastToFront(snode*& headptr) {
		snode* rptr = headptr;
		while (rptr->nextnode != NULL) {
			rptr = rptr->nextnode;
		}
		headptr->prevnode = rptr;
		rptr->prevnode->nextnode = NULL;
		rptr->nextnode = headptr;
		headptr = rptr;
		snode* last = rptr;
	}
	void reverse(snode*& head) {
		snode* temp = NULL;
		snode* current = head;

		// Step 1: Swap prev and next for all nodes
		while (current != NULL) {
			temp = current->prevnode;
			current->prevnode = current->nextnode;
			current->nextnode = temp;
			current = current->prevnode;  // move to next node (which was previous before swapping)
		}

		// Step 2: Adjust head pointer
		if (temp != NULL)
			head = temp->prevnode;
	}


};

int main() {
	dllint list;

	// Insert few nodes
	list.insert(new snode(10));
	list.insert(new snode(20));
	list.insert(new snode(30));
	list.insert(new snode(40));
	list.insert(new snode(50));
	list.insert(new snode(60));
	list.insert(new snode(70));
	list.insert(new snode(80));
	list.insert(new snode(90));
	list.insert(new snode(100));
	list.insert(new snode(110));

	cout << "Initial list:\n";
	list.display();
	list.moveLastToFront(list.headptr);
	list.display();
	/*list.displayreverse();*/
	/*cout << "deletion at end is" << endl;
	list.delete_at_end();
	list.display();
	cout << "deletion atany index is" << endl;
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



	return 0;
}