#pragma once

template <class T>
class List {
public:
	List();
	~List();
	List& operator=(const List<T>& l);
	List(const List<T>& l);

	size_t Size() const;
	void PushFront(const T& data);
	void PushBack(const T& data);
	T PopFront();
	T PopBack();
	T PeakFront();
	T PeakBack();

protected:
	class Node {
		T data;
		Node* next;
	public:
		Node();
		Node(const T& data, Node* next);
	private:
		Node(const Node& n);
		void operator=(const Node& n);
	};
	
	Node* first;
	Node* last;
	size_t size;

	void CopyFrom(const List<T>& l);
};

template <class T>
List<T>::Node::Node() {
	next = nullptr;
}

template <class T>
List<T>::Node::Node(const T& data, Node* next) {
	this->data = data;
	this->next = next;
}

template <class T>
List<T>::List() {
	first = last = NULL;
	size = 0;
}

template <class T>
List<T>::~List() {
	Node* current;
	while (size--) {
		current = first;
		first = first->next;
		delete current;
	}
}

