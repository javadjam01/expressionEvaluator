#pragma once
#define MAX 100

template <class T>
class Stack {
private:
	T items[MAX];
	int top;
public:
	Stack() : top(-1) {}
	bool empty() {
		if (top == -1)
			return true;
		return false;
	}
	bool push(T item) {
		if (top == MAX - 1)
			return false; // overflow
		items[++top] = item;
		return true;
	}
	T pop() {
		if (empty()) {
			exit(1); // underflow
		}
		return items[top--];
	}
	T stackTop() {
		if (empty()) {
			exit(2); // underflow
		}
		return items[top];
	}
};
