#pragma once

// Singly linked list with just one pointer - top and no functionality to add/remove elements to back or middle.

template <class T>
class Stack {
private:
	struct Element {
		T value;
		Element* next;
		
		Element() {
			this->next = nullptr;
		}
		Element(const T& value, Element* next){
			this->next = next;
			this->value = value;
		}
	};

public:
	Stack();
	void Push(const T& value);
	T Pop();
	T Peak();
	bool Empty() const;
	~Stack();

private:
	Element* top;
	size_t count;

};

template <class T>
Stack<T>::Stack() {
	this->count = 0;
	this->top = nullptr;
}

template <class T>
Stack<T>::~Stack() {
	Element* current;
	while (this->top != NULL) {
		current = this->top;
		this->top = this->top->next;
		delete current;
		--this->count;
	}
	delete this->top;
}

template <class T>
bool Stack<T>::Empty() const {
	return !this->count;
}

template <class T>
void Stack<T>::Push(const T& value) {
	this->top = new Element(value, this->top);
	++this->count;
}

template <class T>
T Stack<T>::Peak() {
	return this->top->value;
}

template <class T>
T Stack<T>::Pop() {
	T value = this->Peak();
	Element* top = this->top;
	this->top = this->top->next;
	delete top;
	--this->count;
	return value;
}