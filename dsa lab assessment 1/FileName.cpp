#include<iostream>
using namespace std;
  



  //task 4
int main() {
	
	int *cost =new int[8];
	cout << "enter the cost of items";

	for (int i = 0; i < 8; i++) {
		cin >> cost[i];

	} 
	for (int i = 1; i < 8; i++) {
		int key = cost[i];
		int j = i - 1;
		while (j >= 0 && cost[j] > key) {
			cost[j + 1] = cost[j];
			j--;
		}
		cost[j + 1] = key;
	}
	cout << "the 2 cheapest items are  " << cost[0] << "\n" << cost[1] << endl;
	cout << "the 2 expensive items are  " << cost[7] << "\n" << cost[6] << endl;
}

