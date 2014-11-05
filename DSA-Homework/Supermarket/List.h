#pragma once

template <class T>
class List {
public:
	List();
	~List();
	List<T>& operator=(const List<T>& l);
	List(const List<T>& l);

	size_t Size() const;
	void PushFront(const T& data);
	void PushBack(const T& data);
	void PushAt(size_t index, const T& data);
	T PopFront();
	T PopBack();
	T PopAt(size_t index);
	T PeakFront() const;
	T PeakBack() const;
	T PeakAt(size_t index) const;
	void Clear();
	bool IsEmpty() const;

protected:
	class Node {
	public:
		T data;
		Node* next;
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
	Node* GetNode(size_t index) const;
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
	Clear();
}

template <class T>
void List<T>::CopyFrom(const List<T>& l) {
	Node* it = l.first;
	if (!it) return;
	do {
		this->PushBack(it->data);
		it = it->next;
	} while (it);
}

template <class T>
void List<T>::Clear() {
	Node* current;
	while (size > 0) {
		current = first;
		first = first->next;
		--size;
		delete current;
	}
	last = nullptr;
}

template <class T>
List<T>::List(const List<T>& l) {
	if (this != &l) {
		first = last = nullptr;
		size = 0;
		this->CopyFrom(l);
	}
}

template <class T>
List<T>& List<T>::operator=(const List<T>& l) {
	if (this != &l) {
		this->Clear();
		this->CopyFrom(l);
	}

	return *this;
}

template <class T>
void List<T>::PushBack(const T& data) {
	if (!last) 
		return PushFront(data);

	last = last->next = new Node(data, nullptr);
	++size;
}

template <class T>
void List<T>::PushFront(const T& data) {
	first = new Node(data, first);
	if (!last) last = first;
	++size;
}

template <class T>
T List<T>::PeakFront() const {
	return first->data;
}

template <class T>
T List<T>::PeakBack() const {
	return last->data;
}

template <class T>
size_t List<T>::Size() const {
	return size;
}

template <class T>
T List<T>::PopFront() {
	T returnValue = PeakFront();
	Node* current = first;
	first = first->next;
	--size;
	delete current;
	return returnValue;
}

template <class T>
T List<T>::PopBack() {
	T returnValue = PeakBack();
	Node* it = GetNode(this->size - 2);
	last = it;
	delete last->next;
	--size;
	return returnValue;
}

template <class T>
T List<T>::PeakAt(size_t index) const {
	return GetNode(index)->data;
}

template <class T>
T List<T>::PopAt(size_t index) {
	if (index >= size) throw "Index out of range!";
	Node* prev = GetNode(index - 1);
	Node* current = prev->next;
	T returnValue = current->data;
	prev->next = current->next;
	delete current;
	--size;
	return returnValue;
}

template <class T>
void List<T>::PushAt(size_t index, const T& data) {
	if (!size) return PushFront(data);
	if (size == index) return PushBack(data);
	if (size < index) throw "Invalid index: Size of list is less then the index!";

	Node* prev = GetNode(index - 1);
	prev->next = new Node(data, prev->next);
	++size;
}

template <class T>
typename List<T>::Node* List<T>::GetNode(size_t index) const {
	Node* it = first;
	while (index--) {
		it = it->next;
	}
	return it;
}

template <class T>
bool List<T>::IsEmpty() const {
	return size == 0;
}
