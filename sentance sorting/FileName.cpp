#include <iostream>
using namespace std;
//gramatically  

//int main() {
//    const int MAX_WORDS = 50;
//    const int MAX_LENGTH = 20;
//
//    char sentence[] = "Ali goes to school and Sara goes to market";
//    char words[MAX_WORDS][MAX_LENGTH];
//
//    int wordCount = 0, charIndex = 0;
//
//    // Step 1: Split sentence into words
//    for (int i = 0; sentence[i] != '\0'; i++) {
//        if (sentence[i] != ' ') {
//            words[wordCount][charIndex++] = sentence[i];
//        }
//        else {
//            words[wordCount][charIndex] = '\0'; // End current word
//            wordCount++;
//            charIndex = 0;
//        }
//    }
//    // Add last word
//    words[wordCount][charIndex] = '\0';
//    wordCount++;
//
//    // Step 2: Sort words alphabetically (Bubble Sort)
//    for (int i = 0; i < wordCount - 1; i++) {
//        for (int j = i + 1; j < wordCount; j++) {
//            int k = 0;
//            // Compare character by character
//            while (words[i][k] == words[j][k] && words[i][k] != '\0') {
//                k++;
//            }
//            if (words[i][k] > words[j][k]) {
//                // Swap words[i] and words[j]
//                char temp[MAX_LENGTH];
//                for (int t = 0; t < MAX_LENGTH; t++) {
//                    temp[t] = words[i][t];
//                    words[i][t] = words[j][t];
//                    words[j][t] = temp[t];
//                }
//            }
//        }
//    }
//
//    // Step 3: Print sorted words
//    for (int i = 0; i < wordCount; i++) {
//        cout << words[i] << " ";
//    }
//
//    cout << endl;
//    return 0;
//}



//alphabatically
#include <iostream>
using namespace std;

// Convert a character to lowercase manually
char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + 32;
    }
    return ch;
}

int main() {
    const int MAX_WORDS = 50;
    const int MAX_LENGTH = 20;

    char sentence[] = "Ali goes to school and Sara goes to market";
    char words[MAX_WORDS][MAX_LENGTH];

    int wordCount = 0, charIndex = 0;

    // Step 1: Split sentence into words
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] != ' ') {
            words[wordCount][charIndex++] = sentence[i];
        }
        else {
            words[wordCount][charIndex] = '\0'; // end current word
            wordCount++;
            charIndex = 0;
        }
    }
    // Add last word
    words[wordCount][charIndex] = '\0';
    wordCount++;

    // Step 2: Sort words alphabetically (case-insensitive)
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            int k = 0;
            while (toLower(words[i][k]) == toLower(words[j][k]) && words[i][k] != '\0') {
                k++;
            }
            if (toLower(words[i][k]) > toLower(words[j][k])) {
                // Swap
                char temp[MAX_LENGTH];
                for (int t = 0; t < MAX_LENGTH; t++) {
                    temp[t] = words[i][t];
                    words[i][t] = words[j][t];
                    words[j][t] = temp[t];
                }
            }
        }
    }

    // Step 3: Print sorted words
    for (int i = 0; i < wordCount; i++) {
        cout << words[i] << " ";
    }

    cout << endl;
    return 0;
}




#include <iostream>

void bubbleSort2D(int arr[][2], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j][0] > arr[j + 1][0]) {
                // Swap rows
                int temp[2] = { arr[j][0], arr[j][1] };
                arr[j][0] = arr[j + 1][0];
                arr[j][1] = arr[j + 1][1];
                arr[j + 1][0] = temp[0];
                arr[j + 1][1] = temp[1];
            }
        }
    }
}

void printArray(int arr[][2], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "[" << arr[i][0] << ", " << arr[i][1] << "]" << std::endl;
    }
}

int main() {
    int arr[][2] = { {5, 2}, {3, 4}, {1, 6}, {4, 1} };
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array:" << std::endl;
    printArray(arr, n);

    bubbleSort2D(arr, n);

    std::cout << "Sorted array:" << std::endl;
    printArray(arr, n);

    return 0;
}




#include <iostream>

void selectionSort2D(int arr[][2], int n) {
    for (int i = 0; i < n; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j][0] < arr[min_idx][0]) {
                min_idx = j;
            }
        }
        // Swap rows
        int temp[2];
        temp[0] = arr[i][0];
        temp[1] = arr[i][1];
        arr[i][0] = arr[min_idx][0];
        arr[i][1] = arr[min_idx][1];
        arr[min_idx][0] = temp[0];
        arr[min_idx][1] = temp[1];
    }
}

void printArray(int arr[][2], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "[" << arr[i][0] << ", " << arr[i][1] << "]" << std::endl;
    }
}

int main() {
    int arr[][2] = { {5, 2}, {3, 4}, {1, 6}, {4, 1} };
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Original array:" << std::endl;
    printArray(arr, n);
    selectionSort2D(arr, n);
    std::cout << "Sorted array:" << std::endl;
    printArray(arr, n);
    return 0;
}



#include <iostream>

void insertionSort2D(int arr[][2], int n) {
    for (int i = 1; i < n; i++) {
        int key[2] = { arr[i][0], arr[i][1] };
        int j = i - 1;
        while (j >= 0 && arr[j][0] > key[0]) {
            arr[j + 1][0] = arr[j][0];
            arr[j + 1][1] = arr[j][1];
            j--;
        }
        arr[j + 1][0] = key[0];
        arr[j + 1][1] = key[1];
    }
}

void printArray(int arr[][2], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "[" << arr[i][0] << ", " << arr[i][1] << "]" << std::endl;
    }
}

int main() {
    int arr[][2] = { {5, 2}, {3, 4}, {1, 6}, {4, 1} };
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Original array:" << std::endl;
    printArray(arr, n);
    insertionSort2D(arr, n);
    std::cout << "Sorted array:" << std::endl;
    printArray(arr, n);
    return 0;
}