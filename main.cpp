#include <iostream>

template<class T> class Node {

private:



public:
    Node(const T &arg) {
        this->item = arg;
    }
    Node<T> *next;
    Node<T> *prev;
    T item;
};

template<class T> class LinkedList {
private:

    unsigned int size;
public:
    Node<T> *first = nullptr;
    Node<T> *last = nullptr;

    LinkedList() {

    }

    void push_back(const T& arg) {
        Node<T> *el = new Node<T>(arg);
        if (first == nullptr) {
            first = el;
            last = el;
        } else {
            last->next = el;
            el->prev = last;
            last = el;
        }
        size++;
    }

    void push_front(const T& arg) {
        Node<T> *el = new Node<T>(arg);
        if (first == nullptr) {
            first = el;
            last = el;
        } else {
            first->prev = el;
            el->next = first;
            first = el;
        }
        size++;

    }
};




int main(int argc, char const *argv[]) {
    LinkedList<int> list;
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    list.push_front(10);

    for(Node<int> *curr = list.first; curr != nullptr; curr=curr->next) {
        std::cout << curr->item << std::endl;
    }

    return 0;
}
