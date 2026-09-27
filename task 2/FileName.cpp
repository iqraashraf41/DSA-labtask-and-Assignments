#include<iostream>
using namespace std;
//task 2
//int binarySearch(int arr[], int n, int target) {
//		int low = 0, high = n - 1;
//		while (low <= high) {
//			int mid = (low + high) / 2;
//			
//			if (arr[mid] == target) return mid;
//			else if (arr[mid] > target) high = mid - 1;
//			else low = mid + 1;
//		}
//		return -1;
//	}
//int main(){
//	const int n = 10;
//	int flights[n] = { 1,2,3,4,5,6,7,8,9 };
//	int fn;
//	cout << "enter a no of flight you wanted book" << endl;
//	cin >> fn;
//	int result = binarySearch(flights, n, fn);
//	if (result != -1) {
//		cout << "the flight is booked";
//	}
//	else
//		cout << "the flight not found";
//	return 0;
//
//}  

int main() {

	int* cost[] = new int[8];
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
