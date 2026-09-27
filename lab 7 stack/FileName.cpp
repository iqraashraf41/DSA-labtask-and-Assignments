#include<iostream>
#include<cstring>
using namespace std;
//  
//class stack {
//public:
//
//	int cap = 100;
//	char arr[100];
//	int top;
//	stack() {
//		top = -1;
//	}
//	void push( char  ch) {
//		arr[++top] = ch;
//	}
//	char pop() {
//		return arr[top--];
//	}
//	bool isEmpty() {
//		return top == -1;
//	}
//	char peek() {
//		return arr[top];
//	}
//	bool isfull() {
//		return top == cap - 1;
//	}
//	void display(){
//		for(int i=top;i>=0;i--){
//			cout<<arr[i]<<" ";
//		}
//	}
//	int precednece(char ch) {
//	if(ch == '^')
//		return 3;
//	else if(ch == '*' || ch == '/')
//		return 2;
//	else if(ch == '+' || ch == '-')
//		return 1;
//	else
//		return -1;
//	
//	}
//	bool isoperator(char ch) {
//		if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
//			return true;
//		else
//			return false;
//	}
//	
//
//};
//string postfix(string infix) {
//	string postfix = "";
//	stack st;
//	for(int i=0;i<infix.length();i++) {
//		char ch = infix[i];
//		if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
//			postfix += ch;
//		}
//		else if(ch == '(') {
//			st.push(ch);
//		}
//		else if(ch == ')') {
//			while(!st.isEmpty() && st.peek() != '(') {
//				postfix += st.pop();
//			}
//			st.pop();
//		}
//		else if(st.isoperator(ch)) {
//			while(!st.isEmpty() && st.precednece(ch) <= st.precednece(st.peek())) {
//				postfix += st.pop();
//			}
//			st.push(ch);
//		}
//	}
//	while (!st.isEmpty()) {
//		postfix += st.pop();
//	}
//	return postfix;
//
//}
//int main() {
//	string INFIX="((a+b)*c-(d-e))^(f+g)";
//	cout << "Infix Expression: " << INFIX << endl;
//	cout << "Postfix Expression: " << postfix(INFIX) << endl;
//	return 0;
//}
    





//task 4
class stack {
public:

	int cap = 100;
	int arr[100];
	int top;
	stack() {
		top = -1;
	}
	void push(int a) {
		arr[++top] = a;
	}
int  pop() {
		return arr[top--];
	}
	bool isEmpty() {
		return top == -1;
	}
	int peek() {
		return arr[top];
	}
	bool isfull() {
		return top == cap - 1;
	}
	void display() {
		for (int i = top; i >= 0; i--) {
			cout << arr[i] << " ";
		}
	}
	bool isoperator(char ch) {
				if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
					return true;
				else
					return false;
			}
};
int evaluation(string s){
	stack st;
	
	for (int i = 0; i < s.length(); i++) {
		char ch = s[i];
		if (ch >= '0' && ch <= '9') {
			st.push(ch-'0');

		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
			int val1 = st.pop();
			int val2 = st.pop();
			if (ch == '+') { st.push(val1 + val2); }
			else if (ch == '-') { st.push(val1 - val2); }
			else if (ch == '*') { st.push(val1 * val2); }
			else if (ch == '/') { st.push(val1 / val2); }
			else if (ch == '^') { st.push(val1 ^ val2); }

		}

		return st.pop();


	}

		

}




int main(){
	string str = "23+5*";
	cout << "the given values are" << str << endl;
	cout << "the evaluated value is " << evaluation(str) << endl;	

}