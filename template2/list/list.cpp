
namespace lasd {

// Node

// Constructors

// Move constructor
template<typename Data>
List<Data>::Node::Node(Data && d) noexcept {
    std::swap(element, d);
}

// Copy constructor
template<typename Data>
List<Data>::Node::Node(Node && n) noexcept {
    std::swap(element, n.element);
    std::swap(next, n.next);
}

// Destructor
template<typename Data>
List<Data>::Node::~Node() {
    delete next;
}

// Comparison Operators

// operator!= (Node)
template<typename Data>
bool List<Data>::Node::operator!=(const Node & n) const noexcept {
    return !(*this == n);
}

// operator== (Node)
template<typename Data>
bool List<Data>::Node::operator==(const Node & n) const noexcept {
    return (element == n.element) \
           && ((next == nullptr && n.next == nullptr) || ((next != nullptr && n.next != nullptr) && (*next == *n.next)));
}

// Clone (Node)
template<typename Data>
typename List<Data>::Node * List<Data>::Node::Clone(Node * tail) {
    if(next == nullptr) {
        return tail;
    } else {
        tail->next = new Node(next->element);
        return next->Clone(tail->next);
    }
}

/* ************************************************************************** */

// List

// Constructors

// List (MappableContainer)
template<typename Data>
List<Data>::List(MappableContainer<Data> && c) {
    c.Map([this](Data & data) {
        InsertAtBack(std::move(data));
    });
}

// List (TraversableContainer)
template<typename Data>
List<Data>::List(const TraversableContainer<Data> & c) {
    c.Traverse([this](const Data & data) {
        InsertAtBack(data);
    });
}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
List<Data>::List(const List<Data> & lst) {
    if(lst.tail != nullptr) {
        head = new Node(*lst.head);
        tail = lst.head->Clone(head);
        size = lst.size;
    }
}

// Move constructor
template<typename Data>
List<Data>::List(List<Data> && lst) noexcept {
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
}

/* ************************************************************************ */

// Destructor
template<typename Data>
List<Data>::~List() {
    delete head;
}

// Copy assignment
template<typename Data>
List<Data> & List<Data>::operator=(const List<Data> & list) {
    List<Data> tmp(list);
    std::swap(head, tmp.head);
    std::swap(tail, tmp.tail);
    std::swap(size, tmp.size);
    return *this;

}

// Move assignment
template<typename Data>
List<Data> & List<Data>::operator=(List<Data> && list) noexcept {
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
    return *this;
}

/* ************************************************************************ */

// Comparison operators

// operator!= (List)
template<typename Data>
inline bool List<Data>::operator!=(const List<Data> & list) const noexcept {
    return !(*this == list);
}

// operator== (List)
template<typename Data>
inline bool List<Data>::operator==(const List<Data> & list) const noexcept {
    return (size == list.size) \
           && ((head == nullptr && list.head == nullptr) || ((head != nullptr && list.head != nullptr) && (*head == *list.head)));
}

/* ************************************************************************ */

// Specific member functions

// InsertAtFront (List)
template<typename Data>
void List<Data>::InsertAtFront(const Data & data) {
    Node * ptr = new Node(data);
    ptr->next = head;
    head = ptr;
    if(tail == nullptr) {
        tail = head;
    }
    ++size;
}

// InsertAtFront (List)
template<typename Data>
void List<Data>::InsertAtFront(Data && data) {
    Node * ptr = new Node(std::move(data));
    ptr->next = head;
    head = ptr;
    if(tail == nullptr) {
        tail = head;
    }
    ++size;
}

// RemoveFromFront (List)
template<typename Data>
void List<Data>::RemoveFromFront() {
    if(head != nullptr) {
        Node * front = head;
        if(tail == head) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }
        --size;
        front->next = nullptr;
        delete front;
    } else {
        throw std::length_error("Access to an empty list!");
    }
}

// FrontNRemove (List)
template<typename Data>
Data List<Data>::FrontNRemove() {
    if(head != nullptr) {
        Node * front = head;
        if(tail == head) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }
        --size;
        front->next = nullptr;
        Data data(std::move(front->element));
        delete front;
        return data;
    } else {
        throw std::length_error("Access to an empty list!");
    }
}

// InsertAtBack (List)
template<typename Data>
void List<Data>::InsertAtBack(const Data & data) {
    Node * end = new Node(data);
    if(tail == nullptr) {
        head = end;
    } else {
        tail->next = end;
    }
    tail = end;
    ++size;
}

// InsertAtBack (List)
template<typename Data>
void List<Data>::InsertAtBack(Data && data) {
    Node * end = new Node(std::move(data));
    if(tail == nullptr) {
        head = end;
    } else {
        tail->next = end;
    }
    tail = end;
    ++size;
}

// RemoveFromBack (List)
template<typename Data>
void List<Data>::RemoveFromBack() {
    if(head != nullptr) {
        if(head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node* ptr = head;
            while(ptr->next != tail) {
                ptr = ptr->next;
            }
            delete tail;
            tail = ptr;
            tail->next = nullptr;
        }
        --size;
    } else {
        throw std::length_error("Remove from empty list!");
    }
}

// BackNRemove (List)
template<typename Data>
Data List<Data>::BackNRemove() {
    if(head != nullptr) {
        Data d = tail->element;
        if(head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node* ptr = head;
            while(ptr->next != tail) {
                ptr = ptr->next;
            }
            delete tail;
            tail = ptr;
            tail->next = nullptr;
        }
        --size;
        return d;
    } else {
        throw std::length_error("BackNRemove from empty list!");
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from MutableLinearContainer)

// Front (List)
template<typename Data>
Data & List<Data>::Front() {
    return const_cast<Data &>(static_cast<const List<Data>*>(this)->Front());
}

// Back (List)
template<typename Data>
Data & List<Data>::Back() {
    return const_cast<Data &>(static_cast<const List<Data>*>(this)->Back());
}

// operator[] (List)
template<typename Data>
Data & List<Data>::operator[](const ulong index) {
    return const_cast<Data &>(static_cast<const List<Data>* >(this)->operator[](index));
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

// Front (List)
template<typename Data>
const Data & List<Data>::Front() const {
    if(head != nullptr) {
        return head->element;
    } else {
        throw std::length_error("Access to an empty list!.");
    }
}

// Back (List)
template<typename Data>
const Data & List<Data>::Back() const {
    if(tail != nullptr) {
        return tail->element;
    } else {
        throw std::length_error("Access to an empty list!.");
    }
}

// operator[] (List)
template<typename Data>
const Data & List<Data>::operator[](const ulong i) const {
    if(i < size) {
        Node * cur = head;
        for(ulong idx = 0; idx < i; ++idx, cur = cur->next) {}
        return cur->element;
    } else {
        throw std::out_of_range("Access at index " + std::to_string(i) + "; list size " + std::to_string(size) + "!");
    }
}

/* ************************************************************************ */

// Specific member function (inherited from MappableContainer)

// Map (List)
template<typename Data>
inline void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun, head);
}

// Specific member function (inherited from PreOrderMappableContainer)

// PreOrderMap (List)
template<typename Data>
inline void List<Data>::PreOrderMap(MapFun fun) {
    PreOrderMap(fun, head);
}

// Specific member function (inherited from PostOrderMappableContainer)

// PostOrderMap (List)
template<typename Data>
inline void List<Data>::PostOrderMap(MapFun fun) {
    PostOrderMap(fun, head);
}

/* ************************************************************************ */

// Specific member function (inherited from TraversableContainer)

// Traverse (List)
template<typename Data>
inline void List<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun, head);
}

// Specific member function (inherited from PreOrderTraversableContainer)

// PreOrderTraverse (List)
template<typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
    PreOrderTraverse(fun, head);
}

// Specific member function (inherited from PostOrderTraversableContainer)

// PostOrderTraverse (List)
template<typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
    PostOrderTraverse(fun, head);
}

/* ************************************************************************ */

// Specific member function (inherited from ClearableContainer)

// Clear (List)
template<typename Data>
void List<Data>::Clear() {
    delete head;
    head = tail = nullptr;
    size = 0;
}

// Auxiliary functions

// PostOrderMap (List)
template<typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node * cur) {
    if(cur != nullptr) {
        PostOrderMap(fun, cur->next);
        fun(cur->element);
    }
}

// PreOrderMap (List)
template<typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node * cur) {
    while(cur != nullptr) {
        fun(cur->element);
        cur = cur->next;
    }
}

// PostOrderTraverse (List)
template<typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node * cur) const {
    if(cur != nullptr) {
        PostOrderTraverse(fun, cur->next);
        fun(cur->element);
    }
}

// PreOrderTraverse (List)
template<typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node * cur) const {
    while(cur != nullptr) {
        fun(cur->element);
        cur = cur->next;
    }
}

}