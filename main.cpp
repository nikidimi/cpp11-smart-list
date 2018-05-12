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
    class iterator {
    protected:
        std::shared_ptr<Node<T> > current;
    public:
        iterator(const std::shared_ptr<Node<T> > &current) {
            this->current = current;
        }

        virtual void operator++() {
            current = current->next;
        }

        T operator*() {
            return current.get()->item;
        }

        bool operator!=(const iterator &other) {
            if (this->current == other.current) {
                return false;
            }
            return true;
        }
    };

    class reverse_iterator: public iterator {
    public:
        reverse_iterator(const std::shared_ptr<Node<T> > &current): iterator(current) {
        }

        void operator++() {
            this->current = this->current->prev.lock();
        }
    };


    std::shared_ptr<Node<T> > first;
    std::shared_ptr<Node<T> > last;

    LinkedList() {

    }

    iterator begin() {
        return iterator(first);
    }

    iterator end() {
        return iterator(nullptr);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(last);
    }

    reverse_iterator rend() {
        return reverse_iterator(nullptr);
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

    for(auto curr : list) {
        std::cout << curr << std::endl;
    }

    for(auto curr = list.rbegin(); curr != list.rend(); ++curr) {
        std::cout << *curr << std::endl;
    }

    return 0;
}
