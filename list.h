#include <memory>



template<typename T> class LinkedList {
private:
    class Node {
    private:
        T item;
    public:
        Node(const T &arg);
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;

        T& get();
    };
    unsigned int size;
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
public:
    class iterator {
    protected:
        std::shared_ptr<Node> current;
    public:
        iterator(const std::shared_ptr<Node> &current);
        virtual void operator++();
        T& operator*();
        bool operator!=(const iterator &other);
    };

    class reverse_iterator: public iterator {
    public:
        reverse_iterator(const std::shared_ptr<Node> &current);
        void operator++();
    };

    LinkedList();
    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();
    void push_back(const T& arg);
    void push_front(const T& arg);
};

#include "list.tpp"