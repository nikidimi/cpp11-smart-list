#include <iostream>
#include <memory>

template<class T> class Node {

private:



public:
    Node(const T &arg) {
        this->item = arg;
    }
    std::shared_ptr<Node<T> > next;
    std::weak_ptr<Node<T> > prev;
    T item;
};

template<class T> class LinkedList {
private:

    unsigned int size;
public:
    std::shared_ptr<Node<T> > first;
    std::shared_ptr<Node<T> > last;

    LinkedList() {

    }

    void push_back(const T& arg) {
        std::shared_ptr<Node<T> > el(new Node<T>(arg));
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
        std::shared_ptr<Node<T> > el(new Node<T>(arg));
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

    for(Node<int> *curr = list.first.get(); curr != nullptr; curr=curr->next.get()) {
        std::cout << curr->item << std::endl;
    }

    for(std::shared_ptr<Node<int> > curr = list.last; curr != nullptr; curr=curr->prev.lock()) {
        std::cout << curr.get()->item << std::endl;
    }

    return 0;
}
