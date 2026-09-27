#include<iostream>
using namespace std;
//task 1;
//int searchlinear(int arr[], int size,  int target) {
//	int count = 0;
//	for (int i = 0; i <= size; i++) {
//		if (arr[i] == target) {
//			count += 1;
//		}
//	} return count;
//
//
//}
//int main() {
//	int arr[] = { 4,7,4,2,9,4 };
//	int a = 4;
//	int result = searchlinear(arr, 6, a);
//	cout << "the no" << a << "comes " << result << "times";
//}



//task 2;
//int searchlinear(char arr[], int size, char target) {
//	int i ;
//	for ( i = 0; i <= size; i++) {
//		if (arr[i] == target) {
//			return i;
//		}
//	
//			
//	} return -1;
//
//
//}
//int main() {
//	char arr[] = { 'a' ,'e','i','o','u'} ;
//	char a = 'o';
//	int result = searchlinear(arr, 5, a);
//	if (result != -1) {
//		cout << "the charactor " << a << "comes  at" << result;
//	}
//	else { cout << " result not found"; }
//}
// task 3;
//int searchlinear(string arr[], int size, string target) {
//	int i;
//	for (i = 0; i <= size; i++) {
//		if (arr[i] == target) {
//			return i;
//		}
//
//
//	} return -1;
//
//
//}
//int main() {
//	string arr[] = { "Ali", "Sara", "Omar", "Ayesha" };
//	string s = "Sara";
//	int result = searchlinear(arr, 5, s);
//	if (result != -1) {
//		cout << "the charactor " << s << "comes  at" << result;
//	}
//	else { cout << " result not found"; }
//}

//task 4;

//int *searchlinear(int arr[], int size, int target, int &count) {
//	int *index=new int[size];
//	
//	for (int i = 0; i < size; i++) {
//		if (arr[i] == target) {
//			index[count] = i;
//			count++;
//		}
//		if (count == 0) {
//			delete[] index;
//			return nullptr;
//		}  
//		
//
//	}return index;
//}
//int main() {
//	int arr[] = { 4,7,4,2,9,4 };
//	int a = 4;
//	int count = 0;
//	int* result = searchlinear(arr, 6, a, count);
//	cout << "the charactor " << a << "comes  at";
//	for (int b = 0; b < count; b++) {
//
//		
//
//		if (result) {
//			cout  << result[b] << ",";
//			
//		}
//		else
//			cout << " result not found"; 
//	}
//	}
	/*cout << "the no" << a << "comes " << result << "times";*/

//task 4 2d array searching
//int searchlinear(int arr[][3], int size, int target, int& count1, int &count2) {
////	/*int** index = new int*[size];
//	for (int i = 0; i < size; i++)
//		index[i] = new int[3];*/
//	count1 = 0;
//	count2 = 0;
//	for (int i = 0; i < size; i++){
//	for (int j = 0; j < 3; j++) 
//	 {
//		if (arr[i][j] == target) {
//			count1 = i;
//			count2 = j;
//		}
//		/*if (count == 0) {
//			delete[] index;
//			return nullptr;
//		}*/
//		
//
//	}
//    }return 1;
//}
//
//int main() {
//	int arr[3][3] = { {1, 2, 3 }, {4, 5, 6},{7, 8, 9} };
//	int a = 4;
//	int count1 ;
//	int count2;
//
//	int result = searchlinear(arr, 3, a, count1, count2);
//	/*cout << "the charactor " << a << "comes  at";*/
//
//		if (result) {
//			cout << " the no" << a << "found at row = " << count1 << "ent col = " << count2;;
//
//		}
//		else
//			cout << " result not found";
//
//}



// 1st and last occurance 


//int searchlinear1(char arr[], int size, char target) {
//	int i ;
//	for ( i = 0; i <= size; i++) {
//		if (arr[i] == target) {
//			return i;
//		}
//	
//			
//	} return -1;
//
//
//}
//int searchlinear2(char arr[], int size, char target) {
//	int i;
//	for (i = size; i > 0; i--) {
//		if (arr[i] == target) {
//			return i;
//		}
//
//
//	} return -1;
//
//
//}
//int main() {
//	int b = 7;
//	char arr[] = { 'a' ,'e','a','i','o','a','u'};
//	char a = 'a';
//	int result1 = searchlinear1(arr, b, a);
//	int result2 = searchlinear2(arr, b, a);
//	if (result1!= -1) {
//		cout << "the charactor " << a << " first comes  at" << result1 << endl;;
//	}
//	if (result2 != -1) {
//		cout << "the charactor " << a << " last comes  at" << result2;
//	}
//	else { cout << " result not found"; }
//}