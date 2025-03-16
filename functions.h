#pragma once
#include <string>
#include <cctype> // For isalpha, isdigit
#include <cmath> // for pow, sin, cos
using namespace std;

#define PI 3.14159265358979323846

bool isOperator(const string& s) {
	return (s == "(" || s == ")" || s == "^" || s == "*" || s == "/" || s == "+" || s == "-" || s == "!" || s == "sin" || s == "cos" || s == "u-");
}

int precedence(const string& op) {
	if (op == "!") return 5; // for eg:  -a! (first fact then -u)
	if (op == "sin" || op == "cos" || op == "u-") return 4; // unaries
	if (op == "^") return 3;
	if (op == "*" || op == "/") return 2;
	if (op == "+" || op == "-") return 1;
}

string infixToPostfix(const string& infix) {
	string postfix;
	Stack<string> s;
	int i = 0; // i for infix nav

	while (i < infix.length()) {
		string slice;

		// multi-char functions or single-char variables:
		if (isalpha(infix[i])) {
			while (i < infix.length() && isalpha(infix[i])) {
				slice += infix[i];
				i++;
			}
		}
		// numbers:
		else if (isdigit(infix[i]) || infix[i] == '.') {
			while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
				slice += infix[i];
				i++;
			}
		}
		// Single-char operators
		else {
			slice = infix[i];
			i++;
		}

		// Check for u-
		if (slice == "-" && (i == 1 || isOperator(string(1, infix[i - 2])))) { // infix[i - 2] is a char --> type cast needed // tip: multi-char operators can not be before u- (they have parantheses)
			slice = "u-";
		}

		if (!isOperator(slice)) {
			postfix += slice + " "; // Add operand to postfix
		}
		else if (slice == "(") {
			s.push(slice);
		}
		else if (slice == ")") {
			while (!s.empty() && s.stackTop() != "(") {
				postfix += s.pop() + " ";
			}
			if (!s.empty() && s.stackTop() == "(") {
				s.pop(); // Remove '('
			}
		}
		else { // operators
			while (!s.empty() && precedence(s.stackTop()) > precedence(slice)) {
				postfix += s.pop() + " ";
			}
			// lefty operators
			while (!s.empty() && precedence(s.stackTop()) == precedence(slice) && slice != "^") { // ^ is a righty and it can push on itself
				postfix += s.pop() + " ";
			}
			s.push(slice);
		}
	}

	// Pop remaining
	while (!s.empty()) {
		postfix += s.pop() + " ";
	}

	return postfix;
}

bool isNumber(const string& s) {
	for (char ch : s) {
		if (isdigit(ch) || ch == '.')
			return true;
	}
	return false;
}

struct Var {
	char name;
	float value;
	Var() : name('\0'), value(0) {}
};

int dupCheck(char ch, const Var* array) {
	int i = 0;
	while (array[i].name != '\0') { // Check until hit an uninitialized var
		if (array[i].name == ch) return i;
		i++;
	}
	return -1;
}

// recursive fact:
/*unsigned long long fact(int n) {
	if (n <= 0) {
		cout << "\tfact(n<0) is not supported\n";
		exit(3);
	}
	if (n <= 1) {
		return 1;
	}
	return n * fact(n - 1);
}*/

unsigned fact(int n) {
	if (n <= 0) {
		cout << "\tfact(n<0) is not supported\n";
		exit(3);
	}
	unsigned sum = 1;
	for (int i = 1; i <= n; i++)
	{
		sum *= i;
	}
	return sum;
}

float degToRad(float deg) {
	return deg * (PI / 180.0);
}

float calc(const string& postfix) {
	Stack<float> s;
	Var vars[MAX];
	int i = 0; // for postfix nav
	int j = 0; // for vars nav
	while (i < postfix.length()) {
		string slice;
		int k = 0; // for slice nav
		if (postfix[i] == ' ') {
			i++;
			continue;
		}
		while (postfix[i] != ' ') {
			slice += postfix[i++];
		}
		// number:
		if (isNumber(slice))
			s.push(stof(slice)); // cast to float
		// variable:
		else if (!isOperator(slice)) {
			if (dupCheck(slice[0], vars) == -1) { // if (not duplicate)
				vars[j].name = slice[0];
				cout << "        " << slice[0] << " = ";
				cin >> vars[j].value;
				s.push(vars[j++].value);
			}
			else // if (duplicate)
				s.push(vars[dupCheck(slice[0], vars)].value);
		}
		// operator:
		else {
			if (slice == "^") {
				double exponent = s.pop();
				double base = s.pop();
				s.push(pow(base, exponent));
			}
			else if (slice == "*") {
				float secondOp = s.pop();
				float firstOp = s.pop();
				s.push(firstOp * secondOp);
			}
			else if (slice == "/") {
				float secondOp = s.pop();
				if (secondOp == 0) {
					cout << "\tn/0 is not defined\n";
					exit(4);
				}
				float firstOp = s.pop();
				s.push(firstOp / secondOp);
			}
			else if (slice == "+") {
				float secondOp = s.pop();
				float firstOp = s.pop();
				s.push(firstOp + secondOp);
			}
			else if (slice == "-") {
				float secondOp = s.pop();
				float firstOp = s.pop();
				s.push(firstOp - secondOp);
			}
			else if (slice == "u-") {
				float op = s.pop();
				s.push(-1 * op);
			}
			else if (slice == "!") {
				float op = s.pop();
				s.push(fact(int(op)));
			}
			else if (slice == "sin") {
				float op = s.pop();
				s.push(sin(degToRad(op)));
			}
			else if (slice == "cos") {
				float op = s.pop();
				s.push(cos(degToRad(op)));
			}
		}
	}
	return s.pop();
}