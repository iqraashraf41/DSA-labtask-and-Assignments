#include<iostream>
using namespace std;
class arraylist {
	 const int csize = 1000;
	int arr[1000];
	int usize;
	
public:
	
	arraylist() {
		usize = 0;
	}
	void insert(int x) {
		if (!isfull()) {
			arr[usize++] = x;
		}
		else {
			cout << "the array is full";
		}
	}
	int getsize() {
		return usize;
	}
	bool isfull() {
		if (usize == csize)
			return true;
	}
	void insertatindex(int x,int index) {
		if (isfull()) {
			cout << "the array is full";
			return;
		}
		if (index<0 || index>usize) {
			cout << "invalid index";
			return;

		}
		for (int i = usize; i > index;i--) {
			arr[i] = arr[i - 1];
		} 
		arr[index] = x;
			usize++; 
	}
	void display() {
		if (!isempty()) {
			cout << "array is empty";
			return;

		}
		cout << "array elements are" << endl;
		for (int i = 0; i < usize; i++) {
			cout << arr[i] << ",";
		} cout<< endl;
	}
	void deletelast() {
		if (!isempty())
		{
			usize--;
			
		}else cout << "the array is empty";
		return;
	 }
	
	bool search(int x) {
		for (int i = 0; i < usize; i++) {
			if(arr[i] = x)
			return i;
		}
			return 0;
	}
	void setvalue(int x, int index) {
		if (index >= 0 && index < usize)
			arr[index] = x;
		else 
			cout << "index is invalide";
	}
	bool isempty() {
		return usize == 0;
	}
	void cleardata() {
		usize = 0;
	}

 };
int main() {
	arraylist al;
	for (int i = 0; i < 5; i++) {
		al.insert(i + 10);
	}
	al.display();
	al.setvalue(3, 3);
	al.insertatindex(99, 5);
	al.display();
	cout << "size=" << al.getsize() << endl;
	if (al.search(99)) {
		cout << "99 is found";

	}
	else cout << "not found";
	al.deletelast();
	al.display();
	al.cleardata();
	al.display();
	return 0;
}