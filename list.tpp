template <typename T>
LinkedList<T>::Node::Node(const T &arg) {
    this->item = arg;
}

template <typename T>
T& LinkedList<T>::Node::get() {
    return item;
}

template <typename T>
LinkedList<T>::iterator::iterator(const std::shared_ptr<Node> &current) {
    this->current = current;
}

template <typename T>
void LinkedList<T>::iterator::operator++() {
    current = current->next;
}

template <typename T>
T& LinkedList<T>::iterator::operator*() {
    return current.get()->get();
}

template <typename T>
bool LinkedList<T>::iterator::operator!=(const iterator &other) {
    if (this->current == other.current) {
        return false;
    }
    return true;
}

template <typename T>
LinkedList<T>::reverse_iterator::reverse_iterator(const std::shared_ptr<Node> &current): iterator(current) {
}

template <typename T>
void LinkedList<T>::reverse_iterator::operator++() {
    this->current = this->current->prev.lock();
}

template <typename T>
LinkedList<T>::LinkedList() {

}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    return iterator(first);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return iterator(nullptr);
}

template <typename T>
typename LinkedList<T>::reverse_iterator LinkedList<T>::rbegin() {
    return reverse_iterator(last);
}

template <typename T>
typename LinkedList<T>::reverse_iterator LinkedList<T>::rend() {
    return reverse_iterator(nullptr);
}

template <typename T>
void LinkedList<T>::push_back(const T& arg) {
    std::shared_ptr<Node> el = std::make_shared<Node>(arg);
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

template <typename T>
void LinkedList<T>::push_front(const T& arg) {
    std::shared_ptr<Node> el = std::make_shared<Node>(arg);
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

