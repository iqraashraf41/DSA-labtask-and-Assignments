#include<iostream>

using namespace std;
int factorials(int n) {
	if (n <= 1) return 1;
	return n * factorials(n - 1);
}	
int main() {
	cout << "Factorial of 5 is " << factorials(5) << endl;
	return 0;

}