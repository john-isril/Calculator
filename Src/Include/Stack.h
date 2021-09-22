#pragma once
#include <iostream>

template<typename T>
struct Node {
	T data;
	Node* next;

	Node()
		: data{}, next{ nullptr } {}
	Node(T _data)
		: data{ _data }, next{ nullptr } {}
};

template <typename T>
class Stack {
public:
	Stack();
	Stack(T data);
	~Stack();
	void push(T data);
	T pop();
	bool isEmpty() const;
	size_t size() const;
	const T& top() const;
	void clear();

protected:
	Node<T>* head;
	size_t length;
};

template <typename T>
Stack<T>::Stack()
	: head{ nullptr }, length{ 0 } {}

template <typename T>
Stack<T>::Stack(T data)
	: head{ nullptr }, length{ 0 } {
	push(data);
}

template <typename T>
Stack<T>::~Stack() {
	clear();
}

template <typename T>
void Stack<T>::push(T _data) {
	Node<T>* newNode = new Node<T>{ _data };

	if (length > 0) {
		newNode->next = head;
		head = newNode;
	}
	else {
		head = newNode;
	}

	length++;
}

template <typename T>
T Stack<T>::pop() {
	if (length == 0) {
		throw std::out_of_range("Empty stack.");
	}

	T topValue = head->data;
	Node<T>* temp = head;
	head = head->next;
	delete temp;
	length--;

	return topValue;
}

template <typename T>
bool Stack<T>::isEmpty() const {
	return (length == 0);
}

template <typename T>
size_t Stack<T>::size() const {
	return length;
}

template <typename T>
const T& Stack<T>::top() const {
	return head->data;
}

template <typename T>
void Stack<T>::clear() {
	if (length != 0) {
		Node<T>* temp = nullptr;

		while (head != nullptr) {
			temp = head;
			head = head->next;

			delete temp;
		}

		length = 0;
	}
}