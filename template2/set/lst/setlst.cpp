namespace lasd {

// Constructors
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data> &container) {
    container.Traverse([this](const Data & dat) {
        Insert(dat);
    });
}

// SetLst (MappableContainer)
template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data> &&container) {
    container.Map([this](Data & dat) {
        Insert(std::move(dat));
    });
}

// Move constructor
template <typename Data>
SetLst<Data>::SetLst(SetLst<Data> &&setlist) noexcept  : List<Data>(std::move(setlist)) {
}

// Copy constructor
template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data> &setlist) : List<Data>(setlist)    {
}

// Copy assignment
template <typename Data>
SetLst<Data> &SetLst<Data>::operator=(const SetLst<Data> &setlist) {
    if(this != &setlist) {
        List<Data>::operator=(setlist);
    }
    return *this;
}

// Move assignment
template <typename Data>
SetLst<Data> &SetLst<Data>::operator=(SetLst<Data> &&setlist) noexcept {
    List<Data>::operator=(std::move(setlist));
    return *this;
}

// Comparison operators

// operator!= (SetLst)
template <typename Data>
bool SetLst<Data>::operator!=(const SetLst<Data> &setlist) const noexcept {
    return !(*this == setlist);
}

// operator== (SetLst)
template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data> &setlist) const noexcept {
    return List<Data>::operator==(setlist);
}

// Specific functions from OrderedDictionaryContainer

// Min (SetLst)
template <typename Data>
inline const Data &SetLst<Data>::Min() const {
    return this->Front();
}

// RemoveMin (SetLst)
template <typename Data>
inline void SetLst<Data>::RemoveMin() {
    this->RemoveFromFront();
}

// Min (SetLst)
template <typename Data>
inline Data SetLst<Data>::MinNRemove() {
    return this->FrontNRemove();
}

// Max (SetLst)
template <typename Data>
inline const Data &SetLst<Data>::Max() const {
    return this->Back();
}

// RemoveMax (SetLst)
template <typename Data>
inline void SetLst<Data>::RemoveMax() {
    this->RemoveFromBack();
}

// MaxNRemove (SetLst)
template <typename Data>
inline Data SetLst<Data>::MaxNRemove() {
    return this->BackNRemove();
}

// Function from TestableContainer
template <typename Data>
bool SetLst<Data>::Exists(const Data &data) const noexcept {
    if(this->size == 0) 
        return false;
  

    uint n = this->size;
    uint k = 0;
    Node * H = this->head;
    Node * T = this->tail;
    Node * Z = nullptr;
    if(H->element > data || T->element < data) {
        return false;
    }
    while(n > 0) {
        k = n / 2;
        Z = H;
        for(uint i = 0; i < k; i++) {
            Z = Z->next;
        }
        if(Z->element > data) {
            n = k;
        } else if(Z->element < data) {
            H = Z->next;
            n = n - k - 1;
        } else {
            return true;
        }
    }

    return false ;
}

// Predecessor
template <typename Data>
const Data &SetLst<Data>::Predecessor(const Data &data) const {
    if(!this -> head || this -> head -> element >= data) {
        throw std::length_error(" The set is empty or no predecessor has been found! ");
    } else if(this -> tail -> element < data) {
        return this -> tail -> element;
    }

    uint n = this -> size;
    uint k = 0;
    Node * H = this->head;
    Node * Z = nullptr;
    Node * P = nullptr;

    while(n > 0) {
        k = n / 2;
        Z = H;
        for(uint i = 0; i < k; i++) {
            Z = Z -> next;
        }
        if(Z -> element < data) {
            P = Z;
            H = Z->next;
            n = n - k - 1;
        } else {
            n = k;
        }
    }
    if(P == nullptr)
        throw std::length_error(" No predecessor has been found! ");
    
    return P -> element;
}

// RemovePredecessor (SetLst)
template <typename Data>
inline void SetLst<Data>::RemovePredecessor(const Data &data) {
    if(!this -> head || this -> head -> element >= data) {
        throw std::length_error(" The set is empty or no predecessor has been found! ");
    }

    uint n = this -> size;
    uint k = 0;
    Node * H = this -> head;
    Node* Prev = nullptr;
    Node * Z = nullptr;
    Node * P = nullptr;
    Node * PZ =  nullptr;
    Node * HPred = nullptr;

    while(n > 0) {
        k = n / 2;
        Z = H;
        PZ = HPred;
        for(uint i = 0; i < k; ++i) {

            PZ = Z;
            Z = Z -> next;
        }
        if(Z -> element < data) {

            P = Z;
            Prev = PZ;

            HPred = Z;
            H = Z -> next;
            n = n - k - 1;

        } else {
            n = k;
        }
    }
    if(P == nullptr)
        throw std::length_error(" No predecessor to eliminate! ");
    
    RemoveNode(Prev, P);
}

// PredecessorNRemove
template <typename Data>
inline Data SetLst<Data>::PredecessorNRemove(const Data &data) {
    if(!this -> head || this -> head -> element >= data) {
        throw std::length_error(" The set is empty or no predecessor has been found! ");
    }

    uint n = this -> size;
    uint k = 0;
    Node * H = this -> head;
    Node* Prev = nullptr;
    Node * Z = nullptr;
    Node * P = nullptr;
    Node * PZ =  nullptr;
    Node * HPred = nullptr;

    while(n > 0) {
        k = n / 2;
        Z = H;
        PZ = HPred;
        for(uint i = 0; i < k; ++i) {

            PZ = Z;
            Z = Z -> next;

        }
        if(Z -> element < data) {

            P = Z;
            Prev = PZ;

            HPred = Z;
            H = Z -> next;
            n = n - k - 1;

        } else {
            n = k;
        }
    }

    if(P == nullptr) 
        throw std::length_error(" No predecessor to eliminate! ");
    
    return RemoveNode(Prev, P);
}

// RemoveSuccessor (SetLst)
template <typename Data>
inline void SetLst<Data>::RemoveSuccessor(const Data &data) {
    if(this -> tail == nullptr || this -> tail -> element <= data) {
        throw std::length_error(" The set is empty or no successor has been found! ");
    }
    uint n = this -> size;
    uint k = 0;
    Node * H = this -> head;   
    Node * HPred = nullptr;      
    Node * Prev = nullptr;     
    Node * S = nullptr;      
    Node * Z = nullptr;
    Node * PZ = nullptr;
    
    while(n > 0) {
        k = n / 2;
        Z = H;
        PZ = HPred;
        for(uint i = 0; i < k; ++i) {
            PZ = Z;
            Z  = Z->next;
        }

        if(Z -> element <= data) {
            HPred = Z;
            H = Z->next;
            n -= (k + 1);
        } else {
            S = Z;
            Prev = PZ;
            n = k;
        }
    }
    if(S == nullptr) 
        throw std::length_error(" No successor has been found! ");

    RemoveNode(Prev, S);
}

// Successor (SetLst)
template <typename Data>
inline const Data &SetLst<Data>::Successor(const Data &data) const {
    if(this -> tail == nullptr || this -> tail -> element <= data) {
        throw std::length_error(" The set is empty or no successor has been found! ");
    } else if(this -> head -> element > data) {
        return this -> head -> element;
    }

    uint n = this -> size;
    uint k = 0;
    Node * H = this -> head;
    Node * Z = nullptr;
    Node * S = nullptr;

    while(n > 0) {
        k = n / 2;
        Z = H;
        for(uint i = 0; i < k; i++) {
            Z = Z -> next;
        }
        if(Z->element <= data) {
            H = Z -> next;
            n = n - k - 1;
        } else {
            S = Z;
            n = k;
        }
    }
    if(S == nullptr) 
        throw std::length_error(" No successor has been found! ");

    return S->element;
}

// SuccessorNRemove (SetLst)
template <typename Data>
inline Data SetLst<Data>::SuccessorNRemove(const Data &data) {
    if(this -> tail == nullptr || this -> tail -> element <= data) {
        throw std::length_error(" The set is empty or no successor has been found! ");
    }
    uint n = this -> size;
    uint k = 0;
    Node * H = this -> head;   
    Node * HPred = nullptr;      
    Node * Prev = nullptr;      
    Node * S = nullptr;      
    Node * Z = nullptr;
    Node * PZ = nullptr;

    while(n > 0) {
        k = n / 2;
        Z = H;
        PZ = HPred;
        for(uint i = 0; i < k; ++i) {
            PZ = Z;
            Z = Z -> next;
        }

        if(Z -> element <= data) {
            HPred = Z;
            H = Z->next;
            n -= (k + 1);
        } else {
            S = Z;
            Prev = PZ;
            n = k;
        }
    }
    if(S == nullptr)
        throw std::length_error(" No successor has been found! ");
    
    return RemoveNode(Prev, S);
}

// Insert (SetLst)
template<typename Data>
bool SetLst<Data>::Insert(const Data & data) {
    using Node = typename List<Data>::Node;

    if(this -> head == nullptr || data < this -> head -> element) {
        this->InsertAtFront(data);
        return true;
    }

    if(data > this->tail->element) {
        this->InsertAtBack(data);
        return true;
    }

    uint n = this -> size;
    Node* L = this -> head;
    Node* prevL = nullptr;

    while(n > 0) {
        uint k = n / 2;

        Node* Z = L;
        for(uint i = 0; i < k; ++i) {
            Z = Z->next;
        }

        if(Z->element == data) {
            return false;
        } else if(Z -> element < data) {
            prevL = Z;
            L = Z -> next;
            n = n - k - 1;
        } else {
            n = k;
        }
    }
    Node* newnode = new Node(data);

    if(prevL == nullptr) {
        newnode -> next = this -> head;
        this->head = newnode;
    } else {
        prevL -> next = newnode;
        newnode->next = L;
    }
    if(L == nullptr) {
        this -> tail = newnode;
    }
    ++this -> size;
    return true;
}

// Insert (SetLst)
template <typename Data>
bool SetLst<Data>::Insert(Data &&data) {
    using Node = typename List<Data>::Node;

    if(this -> head == nullptr || data < this -> head -> element) {
        this -> InsertAtFront(std::move(data));
        return true;
    }
    if(data > this->tail->element) {
        this -> InsertAtBack(std::move(data));
        return true;
    }
    uint n = this -> size;
    Node* L = this -> head;
    Node* prevL  = nullptr;

    while(n > 0) {
        uint k = n / 2;

        Node* Z = L;
        for(uint i = 0; i < k; ++i) {
            Z = Z -> next;
        }

        if(Z -> element == data) {
            return false;
        } else if(Z -> element < data) {
            prevL = Z;
            L = Z -> next;
            n = n - k - 1;
        } else {
            n = k;
        }
    }

    Node* newnode = new Node(std::move(data));

    if(prevL == nullptr) {
        newnode -> next = this -> head;
        this -> head = newnode;
    } else {
        prevL -> next = newnode;
        newnode -> next = L;
    }

    if(L == nullptr) {
        this -> tail = newnode;
    }

    ++this -> size;
    return true;
}

// Remove (SetLst)
template <typename Data>
bool SetLst<Data>::Remove(const Data &data) {
    using Node = typename List<Data>::Node;

    if(this -> tail == nullptr)
        return false;

    if(this -> head -> element == data) {
        this -> RemoveFromFront();
        return true;
    }

    if(this -> tail -> element == data) {
        this -> RemoveFromBack();
        return true;
    }

    uint n = this -> size;
    Node*L = this -> head;
    Node*prevL = nullptr;

    while(n > 0) {
        uint k = n / 2;
        Node* Z = L;
        Node* prevZ = prevL;

        for(uint i = 0; i < k; ++i) {
            prevZ = Z;
            Z = Z -> next;
        }

        if(Z -> element == data) {

            prevZ -> next = Z -> next;

            if(Z == this -> tail) {
                this -> tail = prevZ;
            }
            Z -> next = nullptr;
            delete Z;
            --this -> size;
            return true;
        } else if(Z -> element < data) {

            prevL = Z;
            L = Z -> next;
            n = n - k - 1;
        } else {
            n = k;
        }
    }
    return false;
}

// Operator function from LinearContainer

// operator[] (SetLst)
template <typename Data>
inline const Data &SetLst<Data>::operator[](ulong index) const {
    if(index > size)
        throw std::out_of_range(" Index out of range! ");
    
    using Node = typename List<Data>::Node;
    Node *current = this -> head;
    ulong idx = 0;
    while(idx < index) {
        idx++;
        current = current -> next;
    }
    return current -> element;
}

// Function from ClearableContainer

// Clear (SetLst)
template <typename Data>
void SetLst<Data>::Clear() {
    delete this -> head;
    this -> head = this -> tail = nullptr;
    this -> size = 0;
}

// Auxiliary functions

// RemoveNode (SetLst)
template <typename Data>
Data SetLst<Data>::RemoveNode(Node *prev, Node *node) {
    if(prev != nullptr) {

        prev -> next = node -> next;
    } else {
        this -> head = node -> next;
    }

    if(node == this -> tail) {
        this -> tail = prev;
    }

    --(this->size);

    Data value = std::move(node -> element);
    node -> next = nullptr;
    delete node;
    return value;
}

}