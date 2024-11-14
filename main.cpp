#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "func.h"

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t size;
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    DynamicArray() : size(0), capacity(2) {
        data = new T[capacity];
    }
    ~DynamicArray() {
        delete[] data;
    }
    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }
    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) resize();
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }
    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }
    T get(size_t index) const {
        if (index < size) return data[index];
        throw std::out_of_range("Index out of range");
    }
    size_t get_size() const {
        return size;
    }
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << '\n';
    }
};


template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        size++;
    }
    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (!tail) tail = head;
        } else {
            Node* current = head;
            for (size_t i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
            if (!newNode->next) tail = newNode;
        }
        size++;
    }
    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;
        delete current;
        size--;
    }
    T get(size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    size_t get_size() const {
        return size;
    }
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << '\n';
    }
};


int main() {
    // DynamicArray
    DynamicArray<int> array;
    for (int i = 0; i < 10; ++i) {
        array.push_back(i);
    }

    std::cout << "DynamicArray elements after adding 10 elements: ";
    array.print();

    std::cout << "DynamicArray size: " << array.get_size() << '\n';

    array.erase(2);
    array.erase(3);
    array.erase(4);

    std::cout << "DynamicArray elements after removing 3rd, 5th, and 7th elements: ";
    array.print();

    array.insert(0, 10);
    std::cout << "DynamicArray elements after inserting 10 at the beginning: ";
    array.print();

    array.insert(array.get_size() / 2, 20);
    std::cout << "DynamicArray elements after inserting 20 in the middle: ";
    array.print();

    array.push_back(30);
    std::cout << "DynamicArray elements after inserting 30 at the end: ";
    array.print();

    // LinkedList
    LinkedList<int> list;
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    std::cout << "\nLinkedList elements after adding 10 elements: ";
    list.print();

    std::cout << "LinkedList size: " << list.get_size() << '\n';

    list.erase(2);
    list.erase(3);
    list.erase(4);

    std::cout << "LinkedList elements after removing 3rd, 5th, and 7th elements: ";
    list.print();

    list.insert(0, 10);
    std::cout << "LinkedList elements after inserting 10 at the beginning: ";
    list.print();

    list.insert(list.get_size() / 2, 20);
    std::cout << "LinkedList elements after inserting 20 in the middle: ";
    list.print();

    list.push_back(30);
    std::cout << "LinkedList elements after inserting 30 at the end: ";
    list.print();

    return 0;
}

