#include<iostream>
using namespace std;
//task 3

int searchlinear(int arr[], int size, int target, int &Ccount) {
	
	for (int i = 0; i <= size; i++) {
		if (arr[i] == target) {
			
			return i;
		}Ccount += 1;
	} 
	return -1;
}
int main() {
	const int n = 13;
	int scount = 0;
	int Ccount = 0;
	int marks[n] = { 76,89,45,97,23,40,56,30,85,47,67,90,93 };
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (marks[j] > marks[j + 1])
				swap(marks[j], marks[j + 1]);
			scount++;
		}
	}
	cout << "the sortd marks arrya is"<<"  " << endl;
	for (int i = 0; i < n - 1; i++) {
		cout << marks[i]<<",";
	} cout << endl;

	cout << "the no of swaps are" <<"=" << scount << endl;
	int tn;
	cout << "the array is sorted now you can enter a no to search" << endl;
	cin >> tn;
	int result = searchlinear(marks, n, tn,Ccount);
	if (result != -1) {
		cout << " the serached no is at position" << " " << result << endl;

	}
	cout << "the total no of camparision are" << "=" << Ccount << endl;
}