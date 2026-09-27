#include<iostream>

using namespace std;
//task 1 bubble sort
 
 
 
//int main() {
//	const int n = 5; 
//    int count = 0;
//	int arr[n] = { 12, 5,7,6,4 };
//	for (int i = 0; i < n - 1; i++) {
//		for (int j = 0; j < n - i - 1; j++) {
//			if (arr[j] > arr[j + 1])
//				swap(arr[j], arr[j + 1]);
//            count++;
//            /*break;*/
//			/*int temp = arr[j];
//		arr[j] = arr[j + 1];*/
//           
//		}
//        cout << arr[i];
//	}	 cout << endl;
//    
//    
//    /*cout << "the sorted array is";
//    for (int i = 0; i < n; i++) {
//        cout << arr[i];
//    } cout << endl;
//    cout << "the no of swaps are" << count << endl;*/
//}
 
 




//task 2 removal of duplicate values  by buuble sort
//int main() {
//	const int n = 7;
//	int arr[n] = { 4, 2, 7, 2, 4, 9, 1 };
//	for (int i = 0; i < n - 1; i++) {
//		for (int j = 0; j < n - i - 1; j++) {
//		if (arr[j] > arr[j + 1])
//				swap(arr[j], arr[j + 1]);
//			/*int temp = arr[j];
//		arr[j] = arr[j + 1];*/
//
//		}
//	}	 
//	int news = 0;
//
//	
//	for (int i = 0; i < n ; i++) {
//		bool isdoplicate = false;
//		for (int j = 0; j < news; j++) {
//			if (arr[i] == arr[j]) {
//				isdoplicate = true;
//				break;
//			}
//
//		}
//		if (!isdoplicate) {
//			arr[news] = arr[i];
//			news++;
//		}
//
//
//
//	}
//	cout << "the sorted array is";
//	for (int i = 0; i < news; i++) {
//		cout << arr[i];
//	}
//}

//task 3  desending selection sort

//int main() {
//		const int n = 8;
//		int arr[n] = { 18, 25, 15, 30, 22, 40, 10, 28 };
//		for (int i = 0; i < n - 1; i++) {
//			int minindex = i;
//			for (int j = i+1; j < n; j++) {
//				if (arr[j] > arr[minindex])
//					
//				minindex = j;;
//
//				/*int temp = arr[j];
//			arr[j] = arr[j + 1];*/
//
//			}
//			swap(arr[i], arr[minindex]);
//		}
//		cout << "the sorted array is";
//			for (int i = 0; i < n; i++) {
//				cout << arr[i];
//			}
//}



//task 4 
//int main() {
//	const int n = 7;
//	int salaries[7] = { 35000, 50000, 25000, 40000, 60000, 30000, 45000 };
//	for (int i = 0; i < n - 1; i++) {
//		int minindex = i;
//		for (int j = i + 1; j < n; j++) {
//			if (salaries[j] > salaries[minindex])
//
//				minindex = j;;
//
//			/*int temp = arr[j];
//		arr[j] = arr[j + 1];*/
//
//		}
//		swap(salaries[i], salaries[minindex]);
//	}
//	cout << "the sorted array is";
//	for (int i = 0; i < n; i++) {
//		cout << salaries[i];
//	} 
//	cout << endl;
//	cout << "the  2nd highest salary is " << salaries[1];
//}
		

//task 5  
// insertion sort

//int main() {
//    
//    int arr[7] = { 12, 4, 7, 9, 2, 15, 10 };;
//    int n = 7;
//    for (int i = 1; i < n; i++) {
//        int key = arr[i];
//        int j = i - 1;
//        while (j >= 0 && arr[j] > key) {
//            arr[j + 1] = arr[j];
//            j--;
//        }
//        arr[j + 1] = key;
//    }
//    
//
//    cout << "Sorted Array: ";
//    for (int i = 0; i < n; i++)
//        cout << arr[i] << " ";
//    cout << "the middle value is " << arr[n / 2];
//}


//descending 
// 
//int main() {
//    
//int arr[7] = { 12, 4, 7, 9, 2, 15, 10 };;
//int n = 7;
//for (int i = 1; i < n; i++) {
//    int key = arr[i];
//    int j = i - 1;
//    while (j >= 0 && arr[j] < key) {
//        arr[j + 1] = arr[j];
//        j--;
//    }
//    arr[j + 1] = key;
//}
//
//
//cout << "Sorted Array: ";
//for (int i = 0; i < n; i++)
//    cout << arr[i] << " ";
//cout << "the middle value is " << arr[n / 2];
//}
//task 6
//sorted two arrays of different data types at atime
//int main() {
//    		const int n = 5;
//    		int marks[n] = { 85, 92, 75, 90 };
//            string names[5] = { "ali","sara","omer"," hassan" };
//    		for (int i = 0; i < n - 1; i++) {
//    			int minindex = i;
//    			for (int j = i+1; j < n; j++) {
//    				if (marks[j] > marks[minindex])
//    					
//    				minindex = j;;
//    
//    				/*int temp = arr[j];
//    			arr[j] = arr[j + 1];*/
//    
//    			}
//    			swap(marks[i], marks[minindex]);
//                swap(names[i], names[minindex]);
//    		}
//    		cout << "the sorted array is"<<endl;
//    			for (int i = 0; i < n-1; i++) {
//                    cout << marks[i] << "  " << names[i] << endl;;
//    			}
//    }
 //task 7   

//#include <iostream>
//#include <cstring>
//using namespace std;
//
//int main() {
//    char input[] = "Ali goes to school and Sara goes to market";
//    char words[50][20];  // max 50 words, each up to 20 chars
//    int n = 0, i = 0, j = 0;
//
//    // Split manually by spaces
//    for (int k = 0; input[k] != '\0'; k++) {
//        if (input[k] != ' ') {
//            words[n][j++] = input[k];
//        }
//        else {
//            words[n][j] = '\0'; // end of word
//            n++;
//            j = 0;
//        }
//    }
//    words[n][j] = '\0'; // last word
//    n++;
//
//    // Bubble sort
//    char temp[20];
//    for (i = 0; i < n - 1; i++) {
//        for (j = 0; j < n - i - 1; j++) {
//            if (strcmp(words[j], words[j + 1]) > 0) {
//                strcpy(temp, words[j]);
//                strcpy(words[j], words[j + 1]);
//                strcpy(words[j + 1], temp);
//            }
//        }
//    }
//
//    // Print sorted words
//    for (i = 0; i < n; i++) {
//        cout << words[i] << " ";
//    }
//
//    
//}
    //binary search
//int binarySearch(int arr[], int n, int target) {
//    int low = 0, high = n - 1;
//    while (low <= high) {
//        int mid = (low + high) / 2;
//        if (arr[mid] == target) return mid;
//        else if (arr[mid] > target) high = mid - 1;
//        else low = mid + 1;
//    }
//    return -1;
//}
//int main() {
//    int ar[7] = { 1,2,3,4,5,6,7 };
//    int a = 2;
//    int result = binarySearch(ar, 7, a);
//    if (result != -1) {
//        cout << "the no" << a << "is at index" << result << endl;
//    }
//    else cout << "result not found";
//}
// 1st and last position binary search



//#include <iostream>
//using namespace std;
//
//// Function to find the first occurrence
//int findFirst(int arr[], int size, int target) {
//    int start = 0, end = size - 1, result = -1;
//
//    while (start <= end) {
//        int mid = (start + end) / 2;
//
//        if (arr[mid] == target) {
//            result = mid;
//            end = mid - 1;  // keep looking on the left
//        }
//        else if (arr[mid] < target) {
//            start = mid + 1;
//        }
//        else {
//            end = mid - 1;
//        }
//    }
//
//    return result;
//}
//
//// Function to find the last occurrence
//int findLast(int arr[], int size, int target) {
//    int start = 0, end = size - 1, result = -1;
//
//    while (start <= end) {
//        int mid = (start + end) / 2;
//
//        if (arr[mid] == target) {
//            result = mid;
//            start = mid + 1;  // keep looking on the right
//        }
//        else if (arr[mid] < target) {
//            start = mid + 1;
//        }
//        else {
//            end = mid - 1;
//        }
//    }
//
//    return result;
//}
//
//int main() {
//    int arr[] = { 1, 2, 2, 2, 3, 4, 5 };
//    int size = sizeof(arr) / sizeof(arr[0]);
//    int target = 2;
//
//    int first = findFirst(arr, size, target);
//    int last = findLast(arr, size, target);
//
//    cout << "First Occurrence: " << first << endl;
//    cout << "Last Occurrence: " << last << endl;
//
//    return 0;
//}
// how many times a no appers

//#include <iostream>
//using namespace std;
//
//// Function to find the first occurrence
// 
// 
// 
//int findFirst(int arr[], int size, int target) {
//    int start = 0, end = size - 1, result = -1;
//
//    while (start <= end) {
//        int mid = (start + end) / 2;
//
//        if (arr[mid] == target) {
//            result = mid;
//            end = mid - 1;  // keep looking on the left
//        }
//        else if (arr[mid] < target) {
//            start = mid + 1;
//        }
//        else {
//            end = mid - 1;
//        }
//    }
//
//    return result;
//}
//
//// Function to find the last occurrence
//int findLast(int arr[], int size, int target) {
//    int start = 0, end = size - 1, result = -1;
//
//    while (start <= end) {
//        int mid = (start + end) / 2;
//
//        if (arr[mid] == target) {
//            result = mid;
//            start = mid + 1;  // keep looking on the right
//        }
//        else if (arr[mid] < target) {
//            start = mid + 1;
//        }
//        else {
//            end = mid - 1;
//        }
//    }
//
//    return result;
//}
//
//
//int main() {
//    int arr[] = { 1, 2, 2, 2, 3, 4, 5 };
//    int size = sizeof(arr) / sizeof(arr[0]);
//    int target = 2;
//
//    int first = findFirst(arr, size, target);
//    int last = findLast(arr, size, target);
//    int occurance = (last - first) + 1;
//    cout << "First Occurrence: " << first << endl;
//    cout << "Last Occurrence: " << last << endl;
//    cout << "the no comes " << occurance << "times";
//
//    return 0;
//}
    // rotated sorted array

//#include <iostream>
//using namespace std;
//
//int searchInRotatedArray(int arr[], int size, int target) {
//    int start = 0, end = size - 1;
//
//    while (start <= end) {
//        int mid = (start + end) / 2;
//
//        if (arr[mid] == target) {
//            return mid;
//        }
//
//        // Check if the left half is sorted
//        if (arr[start] <= arr[mid]) {
//            if (target >= arr[start] && target < arr[mid]) {
//                end = mid - 1; // target in left half
//            }
//            else {
//                start = mid + 1; // target in right half
//            }
//        }
//        // Right half is sorted
//        else {
//            if (target > arr[mid] && target <= arr[end]) {
//                start = mid + 1; // target in right half
//            }
//            else {
//                end = mid - 1; // target in left half
//            }
//        }
//    }
//
//    return -1; // not found
//}
//
//int main() {
//    int arr[] = { 4, 5, 6, 7, 0, 1, 2 };
//    int size = sizeof(arr) / sizeof(arr[0]);
//    int target = 0;
//
//    int index = searchInRotatedArray(arr, size, target);
//
//    if (index != -1)
//        cout << "Target found at index: " << index << endl;
//    else
//        cout << "Target not found." << endl;
//
//    return 0;
//}

// print no of arrays during sorting 



void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void insertionSortDescending(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        // Shift smaller elements to the right
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;

        // ?? Print the array after this insertion step
        cout << "After inserting element " << key << ": ";
        printArray(arr, size);
    }
}

int main() {
    int arr[] = { 5, 2, 9, 1, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Initial array: ";
    printArray(arr, size);

    insertionSortDescending(arr, size);

    cout << "Final sorted array (descending): ";
    printArray(arr, size);

    return 0;
}
