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
			this->value = value;
			this->next = next;
		}
		~Element() {
			// No cascade deletion of elements so no additional work to do
		}
	private:
		Element(const Element& el);
		void operator=(const Element& el);
	};

public:
	Stack();
	Stack(const Stack<T>& st);
	Stack<T>& operator=(const Stack<T>& st);
	~Stack();


	void Push(T value);
	T Pop();
	T Peak();
	bool Empty() const;
	void Clean();

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
Stack<T>::Stack(const Stack<T>& st) {
	if (this != &st) {
		this->count = 0;
		this->top = nullptr;
		Stack<T> temp;
		for (Element* it = st.top; it != NULL; it = it->next) {
			temp.Push(it->value);
		}
		while (!temp.Empty()) {
			this->Push(temp.Pop());
		}
	}
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& st) {
	if (this != &st) {
		this->Clean();
		Stack<T> temp;
		for (Element* it = st.top; it != NULL; it = it->next) {
			temp.Push(it->value);
		}
		while (!temp.Empty()) {
			this->Push(temp.Pop());
		}
	}

	return *this;
}

template <class T>
Stack<T>::~Stack() {
	if (!this->Empty())
		this->Clean();
}

template <class T>
bool Stack<T>::Empty() const {
	return !this->count;
}

template <class T>
void Stack<T>::Push(T value) {
	this->top = new Element(value, this->top);
	++this->count;
}

template <class T>
T Stack<T>::Peak() {
	if (this->top)
		return this->top->value;
	else
		throw "Stack is empty!";
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

template <class T>
void Stack<T>::Clean() {
	Element* it;
	while (this->top) {
		it = this->top;
		this->top = it->next;
		delete it;
	}
}