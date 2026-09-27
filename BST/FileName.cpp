#include<iostream>
using namespace std;

class bnode {
public:
	int data;
	bnode* leftchild;
	bnode* rightchild;
	bnode() { data = 0; leftchild = nullptr; rightchild = nullptr; }
	bnode(int data) { this->data = data; rightchild = nullptr; leftchild = nullptr; }
	~bnode() { rightchild = nullptr; leftchild = nullptr; }
};
class BST {
public:
	bnode* root;
	BST() { root = nullptr; }


	void Insertion(bnode* newnode) {
		if (root == nullptr) {
			root = newnode;
		}
		else {
			bnode* bptr = root;
			bnode* rptr = nullptr;
			while (bptr != NULL) {
				rptr = bptr;
				if (newnode->data == bptr->data) {
					delete newnode;
					return;
				}
				if (newnode->data < bptr->data) {
					bptr = bptr->leftchild;
				}
				else {
					bptr = bptr->rightchild;
				}
			}
			if (newnode->data < rptr->data) {
				rptr->leftchild = newnode;
			}
			else {
				rptr->rightchild = newnode;
			}
		}
	}
	bool search(int key) {
		if (root == nullptr) {
			return false;
		}
		else {
			bnode* rptr = root;
			while (rptr != nullptr) {
				if (rptr->data == key) {
					return true;
				}
				else if (rptr->data > key) {
					rptr = rptr->leftchild;
				}
				else if (rptr->data < key) {
					rptr = rptr->rightchild;
				}
			}
			return false;
		}
	}
	void deletion(int key) {
		bnode* rptr = root;
		bnode* parent = nullptr;
		while (rptr != nullptr && rptr->data != key) {
			parent = rptr;
			if (rptr->data < key) {
				rptr = rptr->rightchild;
			}
			else if (rptr->data > key) {
				rptr = rptr->leftchild;
			}
		}
		if (rptr == nullptr) {
			cout << key << " not found" << endl;
			return;
		}
		//case 1: No child
		if (rptr->leftchild == nullptr && rptr->rightchild == nullptr) {
			if (parent == nullptr) {
				root = nullptr;
			}
			else if (parent->leftchild == rptr) {
				parent->leftchild = nullptr;
			}
			else if (parent->rightchild == rptr) {
				parent->rightchild = nullptr;
			}
			delete rptr;
		}
		//case 2: One child
		if (rptr->leftchild == nullptr || rptr->rightchild == nullptr) {
			bnode* child;
			if (rptr->leftchild != nullptr) { child = rptr->leftchild; }
			else { child = rptr->rightchild; }
			if (parent == nullptr) { root = child; }
			else if (parent->leftchild == rptr) {
				parent->leftchild = child;
			}
			else if (parent->rightchild == rptr) {
				parent->rightchild = child;
			}
			delete rptr;
		}
		//case 3: two children
		if (rptr->leftchild != nullptr && rptr->rightchild != nullptr) {
			bnode* succParent = rptr;
			bnode* succ = rptr->rightchild;
			while (succ->leftchild != nullptr) {
				succParent = succ;
				succ = succ->leftchild;
			}
			rptr->data = succ->data;
			bnode* child;
			if (succ->leftchild != nullptr) { child = succ->leftchild; }
			else { child = succ->rightchild; }
			if (succParent->leftchild == succ)
				succParent->leftchild = child;
			else
				succParent->rightchild = child;
			delete succ;
		}
	}
	int height(bnode* root) {
		if (root == nullptr) return 0;
		bnode* stack[100];
		int depth[100];
		int top = -1;
		stack[++top] = root;
		depth[top] = 1;
		int maxHeight = 0;
		while (top != -1) {
			bnode* curr = stack[top];
			int currDepth = depth[top];
			top--;
			if (currDepth > maxHeight) { maxHeight = currDepth; }
			if (curr->rightchild != nullptr) {
				stack[++top] = curr->rightchild;
				depth[top] = currDepth + 1;
			}
			if (curr->leftchild != nullptr) {
				stack[++top] = curr->leftchild;
				depth[top] = currDepth + 1;
			}
		}

		return maxHeight;
	}
	int balancefactor(bnode* Root) {
		int left = height(Root->leftchild);
		int right = height(Root->rightchild);
		int balance = right - left;
		return balance;
	}
	void InorderTraversal(bnode* node) {
		if (node != nullptr) {
			InorderTraversal(node->leftchild);
			cout << node->data << " ";
			InorderTraversal(node->rightchild);
		}
	}
	void PrintInorder() {
		InorderTraversal(root);
		cout << std::endl;
	}
}; 
int main() {
	BST bst;
	int n;
	cout << "How many nodes you want to enter? "; cin >> n;
	for (int i = 0; i < n; i++) {
		int data;
		cout << "Enter data: "; cin >> data;
		bnode* N = new bnode(data);
		bst.Insertion(N);
	}
	cout << "the hieght of the tree is: " << bst.height(bst.root) << endl;	
	cout << "Inorder Traversal: ";
	bst.PrintInorder();
	int b = bst.balancefactor(bst.root);
	if (b == 1 || b == 0 || b == -1) {
		cout << "Balance factor is " << b;
		cout << "\n Tree is balanced" << endl;
	}
	else {
		cout << "Balance factor is " << b;
		cout << "\nTree is not balanced" << endl;
	}
	bst.deletion(6);

	cout << "Inorder Traversal: ";
	bst.PrintInorder();

	return 0;
}