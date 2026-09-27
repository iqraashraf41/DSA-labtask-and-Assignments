
#include<iostream>
using namespace std;
//task 1
int searchlinear(string arr[], int size, string target, int& count) {
	int i;
	for (i = 0; i <= size; i++) {
		if (arr[i] == target) {
			return i;
		}
		count++;


	} return -1;
}

int main() {
	const int n = 5;
	int count = 0;
	string titles[n] = { "moonsoon","jawani","rangi","billo","ankhy" };
	string a;
	cout << "these are the titles which one you wanted to get" << endl;
	for (int i = 0; i < n; i++) {
		cout << titles[i]<<",";
	} 
	cin >> a;

	

	int result = searchlinear(titles, n, a ,count);
	if (result != -1) {
		cout << "the title found at position =" << result << endl;
	} cout << "the total no of comparisions are  " << count << endl;

}