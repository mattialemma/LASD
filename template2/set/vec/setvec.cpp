namespace lasd {

// Constructors

// SetVec (TraversableContainer)
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data> &container) {
    container.Traverse([this](const Data & dat) {
        Insert(dat);
    });
}

// SetVec (MappableContainer)
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data> &&container) {
    container.Map([this](Data & dat) {
        Insert(std::move(dat));
    });
}

// Copy constructor (SetVec)
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data> &other) {
    this -> Resize(other.capacity);
    this -> size = other.size;
    this -> head = other.head;
    this -> tail = other.tail;
    this -> capacity = other.capacity;
    for(ulong index = 0; index < this->size; index++) {
        ulong realIndex = (this->head + index) % this->capacity;
        ulong vectorIndex = (other.head + index) % other.capacity;
        vec[realIndex] = other.vec[vectorIndex];
    }
}

// Move constructor (SetVec)
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data> &&other) noexcept {
    vec = std::move(other.vec);

    std::swap(this -> size, other.size);
    std::swap(this -> head, other.head);
    std::swap(this -> tail, other.tail);
    std::swap(this -> capacity, other.capacity);
}

// Copy assignment (SetVec)
template <typename Data>
SetVec<Data> &SetVec<Data>::operator=(const SetVec<Data> &other) {
    this -> Resize(other.capacity);
    this -> size = other.size;
    this -> head = other.head;
    this -> tail = other.tail;
    this -> capacity = other.capacity;

    for(ulong i = 0; i < this -> size; ++i) {
        vec[i] = other.vec[i];
    }
    return *this;
}

// Move assignment (SetVec)
template <typename Data>
SetVec<Data> &SetVec<Data>::operator=(SetVec<Data> &&other) noexcept {
    vec = std::move(other.vec);

    std::swap(this -> size, other.size);
    std::swap(this -> head, other.head);
    std::swap(this -> capacity, other.capacity);
    std::swap(this -> tail, other.tail);
    return *this;
}

// Comparison operators

// operator!= (SetVec)
template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data> &other) const noexcept {
    return !(*this == other);
}

// operator== (SetVec)
template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data> &other) const noexcept {
    if(this -> size != other.size)
        return false;

    for(ulong i = 0; i < this -> size; ++i) {
        ulong realIdx = (this -> head + i) % capacity;
        ulong otherRealIdx = (other.head + i) % other.capacity;
        if(vec[realIdx] != other.vec[otherRealIdx])
            return false;
    }
    return true;
}

/* ************************************************************************** */

// Insert (copy)
template <typename Data>
bool SetVec<Data>::Insert(const Data &val) {

    if(this -> capacity == 0) {
        this -> Resize(1);
        vec[0] = val;
        this -> head = 0;
        this -> tail = 1 ;
        this -> size = 1;
        return true;
    }

    if((size * 100) / capacity >= 80) {
        this -> Resize(capacity * 2);
    }
    ulong insertPos = 0;
    uint i = 0;
    uint j = this->size;
    uint k = 0;

    while(i < j) {
        k = (i + j) / 2;
        if(val < vec[(this -> head + k) % this -> capacity]) {
            j = k;

        } else if(val > vec[(this -> head + k) % this -> capacity]) {
            i = k + 1;
        } else {
            return false;
        }
    }
    insertPos = i;

    for(ulong i = this -> size; i > insertPos; --i) {
        ulong from = (this -> head + i - 1) % this -> capacity;
        ulong to = (this -> head + i) % this -> capacity;
        vec[to] = vec[from];
    }

    ulong realInsertIdx = (this -> head + insertPos) % this -> capacity;
    vec[realInsertIdx] = val;
    this -> size++;

    this -> tail = (this -> head + this -> size) % this -> capacity;
    return true;
}

// Insert (move)
template <typename Data>
bool SetVec<Data>::Insert(Data &&val) {
    
    if(this -> capacity == 0) {
        this -> Resize(1);
        vec[0] = std::move(val);
        this -> head = 0;
        this -> tail = 1 ;
        this -> size = 1;
        return true;
    }

    if((size * 100) / capacity >= 80) {
        this -> Resize(capacity * 2);
    }

    ulong insertPos = 0;
    uint i  = 0;
    uint j = this -> size;
    uint k = 0;

    while(i < j) {
        k = (i + j) / 2;
        if(val < vec[(this -> head + k) % this -> capacity]) {
            j = k;

        } else if(val > vec[(this -> head + k) % this -> capacity]) {
            i = k + 1;

        } else {
            return false;
        }
    }
    insertPos = i;

    for(ulong i = this -> size; i > insertPos; --i) {
        ulong from = (this -> head + i - 1) % this -> capacity;
        ulong to = (this -> head + i) % this -> capacity;
        vec[to] = std::move(vec[from]);
    }

    ulong realInsertIdx = (this -> head + insertPos) % this -> capacity;;
    vec[realInsertIdx] = std::move(val);
    this -> size++;
    this -> tail = (this -> head + this -> size) % this -> capacity;

    return true;
}

// Remove
template <typename Data>
bool SetVec<Data>::Remove(const Data &val) {

    if(this->size == 0) {
        return false;
    }
    ulong i = 0;
    ulong j = size;
    while(i < j) {
        ulong k = (i + j) / 2;
        if(val < vec[(head + k) % capacity]) {
            j = k;
        } else if(val > vec[(head + k) % capacity]) {
            i = k + 1;
        } else {
            i = k;
            break;
        }
    }
    if(i >= size) {
        return false;
    }
    ulong pos = (head + i) % capacity;
    if(vec[pos] != val) {
        return false;
    }

    ulong read  = (pos + 1) % capacity;
    ulong write = pos;

    ulong end   = (head + size) % capacity;
    while(read != end) {
        vec[write] = std::move(vec[read]);
        write = read;
        read  = (read + 1) % capacity;
    }

    size--;
    tail = (tail + capacity - 1) % capacity;
    if((size * 100) / capacity <= 20) {
        this->Resize(capacity / 2);
    }

    return true;
}

/* ************************************************************************** */

// operator[]
template <typename Data>
const Data &SetVec<Data>::operator[](ulong index) const {
    if(index >= this -> size || index < 0) 
        throw std::out_of_range(" Index out of range! ");
    
    ulong indx = (this -> head + index) % this -> capacity;

    return vec[indx];
}

// Min (SetVec)
template <typename Data>
const Data& SetVec<Data>::Min() const {
    if(this -> size == 0) 
        throw std::length_error(" Container is empty! ");
    

    return vec[this -> head];
}

// RemoveMin (SetVec)
template <typename Data>
void SetVec<Data>::RemoveMin() {
    if(this->Empty()) {
        throw std::length_error(" Container is empty! ");
    }

    this->head = (this->head + 1) % capacity;
    size--;
    if((size * 100) / capacity <= 20) {
        this->Resize(capacity / 2);
    }
}

// MinNRemove (SetVec)
template <typename Data>
Data SetVec<Data>::MinNRemove() {
    if(this->Empty()) {
        throw std::length_error(" Container is empty! ");
    }
    Data d = vec[this->head];
    this->head = (this->head + 1) % capacity;
    size--;
    if((size * 100) / capacity <= 20) {
        this->Resize(capacity / 2);
    }
    return d;

}

// Max (SetVec)
template <typename Data>
const Data& SetVec<Data>::Max() const {
    if(this->size == 0) {
        throw std::length_error(" Container is empty! ");
    }
    ulong index = (this->tail + capacity - 1) % this->capacity;
    return vec[index];
}

// RemoveMax (SetVec)
template <typename Data>
void SetVec<Data>::RemoveMax() {
    if(this->Empty()) {
        throw std::length_error(" Container is empty! ");
    }

    size--;
    tail = (tail + capacity - 1) % capacity;

    if((size * 100) / capacity <= 20) {
        this->Resize(capacity / 2);
    }
}

// MaxNRemove (SetVec)
template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    if(this->Empty()) {
        throw std::length_error(" Container is empty! ");
    }

    ulong idx = (tail + capacity - 1) % capacity;
    Data maxVal = vec[idx];
    size--;
    tail = (tail + capacity - 1) % capacity;

    if((size * 100) / capacity <= 20) {
        this->Resize(capacity / 2);
    }
    return maxVal;

}

// Predecessor (SetVec)
template <typename Data>
inline const Data& SetVec<Data>::Predecessor(const Data &key) const {
    if(this -> size == 0) 
        throw std::length_error(" Container is empty! ");
    
    ulong i = 0;
    ulong j = this -> size ;
    ulong p;
    bool found = false;
    while(i < j) {
        ulong k = (i + j) / 2;
        if(vec[(this -> head + k) % this -> capacity] < key) {
            p = k;
            i = k + 1;

            found = true;
        } else {
            j = k;
        }
    }
    if(found == false) 
        throw std::length_error(" No predecessor has been found! ");
    
    return vec[(head + p) % capacity];
}

// PredecessorNRemove (SetVec)
template <typename Data>
inline Data SetVec<Data>::PredecessorNRemove(const Data &key) {
    if(this -> size == 0) 
        throw std::length_error(" Container is empty! ");
    
  ulong i = 0;
    ulong j = this -> size ;
    ulong p;
    bool found = false;
    while(i < j) {
        ulong k  = (i + j) / 2;
        if(vec[(this->head + k) % this -> capacity] < key) {
            p = k;
            i = k + 1;

            found = true;
        } else {
            j = k;
        }
    }
    if(found == false) 
        throw std::length_error(" No predecessor has been found! ");

    
    ulong realPos = (head + p) % capacity;
    Data d = vec[(head + p) % capacity];

    ulong read = (realPos + 1) % capacity;
    ulong write = realPos;

    ulong end = (head + size) % capacity;
    while(read != end) {
        vec[write] = std::move(vec[read]);
        write = read;
        read  = (read + 1) % capacity;
    }

    size--;
    tail = (tail + capacity - 1) % capacity;
    if((size * 100) / capacity <= 20) 
        this -> Resize(capacity / 2);
    
    return d;
}

// RemovePredecessor (SetVec)
template <typename Data>
inline void SetVec<Data>::RemovePredecessor(const Data &key) {
      if(this -> size == 0) 
        throw std::length_error(" Container is empty! ");
    
  ulong i = 0;
    ulong j = this -> size ;
    ulong p;
    bool found = false;
    while(i < j) {
        ulong k = (i + j) / 2;
        if(vec[(this -> head + k) % this -> capacity] < key) {
            p = k;
            i = k + 1;

            found = true;
        } else {
            j = k;
        }
    }
    if(found == false) 
        throw std::length_error(" No predecessor has been found! ");
    
    ulong realPos = (head + p) % capacity;

    ulong read = (realPos + 1) % capacity;
    ulong write = realPos;

    ulong end   = (head + size) % capacity;
    while(read != end) {
        vec[write] = std::move(vec[read]);
        write = read;
        read  = (read + 1) % capacity;
    }

    size--;
    tail = (tail + capacity - 1) % capacity;
    if((size * 100) / capacity <= 20) 
        this -> Resize(capacity / 2);
    
}

// Successor (SetVec)
template <typename Data>
inline const Data& SetVec<Data>::Successor(const Data &key) const {
    if(this -> size == 0) {
        throw std::length_error(" Container is empty! ");
    }
    ulong i = 0;
    ulong j = this -> size ;
    ulong s;
    bool found = false;
    while(i < j) {
        ulong k = (i + j) / 2;
        if(vec[(this -> head + k) % this -> capacity] > key) {
            j = k;
            s = k;
            found = true;
        } else {
            i = k + 1;
        }
    }
    if(found == false) 
        throw std::length_error(" No successor has been found! ");
    
    return vec[(head + s) % capacity];
}

// SuccessorNRemove (SetVec)
template <typename Data>
inline Data SetVec<Data>::SuccessorNRemove(const Data &key) {
    if(this -> size == 0) 
        throw std::length_error(" Container is empty! ");

    ulong i = 0;
    ulong j = this -> size ;
    ulong s;
    bool found = false;
    while(i < j) {
        ulong k     = (i + j) / 2;
        if(vec[(this->head + k) % this->capacity] > key) {
            j = k;
            s = k;
            found = true;
        } else {
            i = k + 1;
        }
    }
    if(found == false) 
        throw std::length_error(" No successor has been found! ");
    
    ulong realPos = (head + s) % capacity;
    Data d = vec[(head + s) % capacity];

    ulong read = (realPos + 1) % capacity;
    ulong write = realPos;
    ulong end = (head + size) % capacity;
    while(read != end) {
        vec[write] = std::move(vec[read]);
        write = read;
        read  = (read + 1) % capacity;
    }

    size--;
    tail = (tail + capacity - 1) % capacity;
    if((size * 100) / capacity <= 20) {
        this -> Resize(capacity / 2);
    }
    return d;
}

// RemoveSuccessor (SetVec)
template <typename Data>
inline void SetVec<Data>::RemoveSuccessor(const Data &key) {
    if(this->size == 0) 
        throw std::length_error(" Container is empty! ");
    
    ulong i = 0;
    ulong j = this -> size ;
    ulong s;
    bool found = false;
    while(i < j) {
        ulong k = (i + j) / 2;
        if(vec[(this->head + k) % this -> capacity] > key) {
            j = k;
            s = k;
            found = true;
        } else {
            i = k + 1;
        }
    }
    if(found == false) 
        throw std::length_error(" No successor has been found! ");

    ulong realPos = (head + s) % capacity;
    ulong read = (realPos + 1) % capacity;
    ulong write = realPos;
    ulong end = (head + size) % capacity;

    while(read != end) {
        vec[write] = std::move(vec[read]);
        write = read;
        read  = (read + 1) % capacity;
    }

    size--;
    tail = (tail == 0 ? capacity - 1 : tail - 1);
    if((size * 100) / capacity <= 20) {
        this -> Resize(capacity / 2);
    }
}

/* ************************************************************************** */

// Exists (SetVec)
template <typename Data>
bool SetVec<Data>::Exists(const Data &val) const noexcept {
    if(this -> Size() == 0)
        return false;

    ulong i = 0, j = this -> size;
    while(i < j) {
        ulong mid = (i + j) / 2;
        ulong realMid = (head + mid) % capacity;
        if(val < vec[realMid]) {
            j = mid;
        } else if(val > vec[realMid]) {
            i = mid + 1;
        } else {
            i = mid;
            return true;
        }
    }
    return false;
}

// Clear function
template <typename Data>
void SetVec<Data>::Clear() {
    this->Resize(0);
}

/* ************************************************************************** */

// Resize (SetVec)
template <typename Data>
void SetVec<Data>::Resize(ulong newSize) {

    if(newSize == 0) {
        vec.Clear();
        this->size = 0;
        this->head = 0;
        this->capacity = 0;
        this->tail = 0;
        return;
    }

    lasd::Vector<Data> newVec(newSize);
    ulong copySize = std::min(this->size, newSize);

    for(ulong i = 0; i < copySize; ++i) {
        newVec[i] = std::move(vec[(this->head + i) % this->capacity]);
    }

    vec = std::move(newVec);
    this->head = 0;
    this->tail = copySize;
    this->size = copySize;
    this->capacity = newSize;
}

}