#include<iostream>
using namespace std;

//int factorial(int n) {
//	if (n <= 1) {return 1;}
//	else
//	return n * factorial(n - 1);
//
// }
//int main() {
//	int no;
//	cout << "enter the no: ";
//	cin >> no;
//	cout << "factorial of " << no << " is " << factorial(no) << endl;
//	return 0;
//}

//int fabonacci(int n) {
//	if (n <= 1) {return n;}
//	else
//	return fabonacci(n - 1) + fabonacci(n - 2);
//}
//int main() {
//	int no;
//	cout << "enter the no: ";
//	cin >> no;
//	cout << "fabonacci of " << no << " is " << fabonacci(no) << endl;
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//void towerOfHanoi(int n, char from, char to, char aux) {
//    if (n == 1) {
//        cout << "Move disk 1 from " << from << " to " << to << endl;
//        return;
//    }
//
//    towerOfHanoi(n - 1, from, aux, to);
//    cout << "Move disk " << n << " from " << from << " to " << to << endl;
//    towerOfHanoi(n - 1, aux, to, from);
//}
//
//int main() {
//    int n;
//	cout << "enter the no of disk you wanted to play with: ";   
//    cin >> n;
//    towerOfHanoi(n, 'A', 'C', 'B');
//    return 0;
//}
   


//int power( int x,int n) {
//    if (n ==0) { return 1; }
//    else
//        
//		return x * power(x,n - 1);
//
//}
//int main() {
//	int no;
//		int p;
//	cout << "enter the no: ";
//	cin >> no,
//		cout << "enter the power: ";
//	cin >>  p;
//	cout << "sum of " << no << " is " << power(no,p) << endl;
//	return 0;
//}


#include <iostream>
using namespace std;

int reverseNumber(int n, int rev) {
    if (n == 0)              // base case
        return rev;
    return reverseNumber(n / 10, rev * 10 + n % 10); // recursive call
}

int main() {
    int num;
    cout << "Enter number: ";
    cin >> num;

    cout << "Reversed number: " << reverseNumber(num, 0);
    return 0;
}
