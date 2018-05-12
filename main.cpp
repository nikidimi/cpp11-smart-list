#include <iostream>
#include <memory>



template<class T> class LinkedList {
private:
    class Node {
    private:
        T item;
    public:
        Node(const T &arg) {
            this->item = arg;
        }
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;

        T& get() {
            return item;
        }
    };
    unsigned int size;
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
public:
    class iterator {
    protected:
        std::shared_ptr<Node> current;
    public:
        iterator(const std::shared_ptr<Node> &current) {
            this->current = current;
        }

        virtual void operator++() {
            current = current->next;
        }

        T& operator*() {
            return current.get()->get();
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
        reverse_iterator(const std::shared_ptr<Node> &current): iterator(current) {
        }

        void operator++() {
            this->current = this->current->prev.lock();
        }
    };

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
        std::shared_ptr<Node>  el(new Node(arg));
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
        std::shared_ptr<Node> el(new Node(arg));
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
