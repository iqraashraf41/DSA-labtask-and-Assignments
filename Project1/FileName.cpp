#include<iostream>
using namespace std;
int binarySearch(int arr[], int n, int target) {
	int low = 0, high = n - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (arr[mid] == target) return mid;
		else if (arr[mid] > target) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}
	int main(){

		/*char a ;
		cout << "enter a charactor ";
		cin >> a;

		if ( a >= 65  && a <= 90) {
			cout << " the letter is upper case letter";

		}
		else cout << " the letter ius lower case letter";*/
		/*int a = 23;
		cout << (a >= 0 ? "positive" : "negative") << endl;*/
		/*int n;
		cout << "enter a no";
		cin >> n;
		int sum=0;
		for (int i = 1; i <= n; i++) {
			if (i % 2 != 0) {
				sum += i;

			}

		} cout << sum;*/
		int aar[] = { 1,2,3,4,5,6,7,8,9,10 };

		int a =2;
		
		int result = binarySearch(aar, 10, a);
			if (result !=-1) {
				cout << "the target is found at index" << result << endl;

			}
			else cout << " the no not found" << endl;
		

}

		