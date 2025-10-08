
namespace lasd {

// Vector

// Constructors

// Vector (ulong)
template <typename Data>
Vector<Data>::Vector(const ulong sz) {
    size = sz;
    Elements = new Data[size] {};
}

// Vector (TraversableContainer) copy constructor
template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & container) : Vector(container.Size()) {
    ulong i = 0;
    container.Traverse([this, &i](const Data & data) {
        Elements[i] = data;
        i++;
    }
    );
}

// Vector (MappableContainer) move constructor
template<typename Data>
Vector<Data>::Vector(MappableContainer<Data> && container) : Vector(container.Size()) {
    ulong i = 0;
    container.Map([this, &i](Data & data) {
        Elements[i] = std::move(data);
        i++;
    }
    );
}

// Vector (Vector) copy constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data> & vec) {
    size = vec.size;
    Elements = new Data[size];
    std::copy(vec.Elements, vec.Elements + size, Elements);
}

// Vector (Vector &&) move constructor
template<typename Data>
Vector<Data>::Vector(Vector<Data> && vec) noexcept {
    std::swap(size, vec.size);
    std::swap(Elements, vec.Elements);
}
 
// Destructor (Vector)
template<typename Data>
Vector<Data>::~Vector() {
    delete[] Elements;
}

// Copy assignment (Vector)
template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & vec) {
    Vector<Data> * tmp = new Vector<Data>(vec);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

// Move assignment (Vector)
template<typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> && vec) noexcept {
    std::swap(size, vec.size);
    std::swap(Elements, vec.Elements);
    return *this;
}

// Comparison operators

// operator!= (Vector)
template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data> & vec) const noexcept {
    return !(*this == vec);
}

// operator== (Vector)
template<typename Data>
bool Vector<Data>::operator==(const Vector<Data> & vec) const noexcept {
    if(size == vec.size) {

        for(ulong i = 0; i < size; ++i) {
            if(Elements[i] != vec.Elements[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

// Specific member functions (inherited from MutableLinearContainer)

// operator[] (Vector)
template<typename Data>
Data & Vector<Data>::operator[](const ulong i) {
    return const_cast<Data &>(static_cast<const Vector<Data>* >(this)->operator[](i));
}

// Front (Vector)
template<typename Data>
Data & Vector<Data>::Front() {
    return const_cast<Data &>(static_cast<const Vector<Data>*>(this)->Front());
}

// Back (Vector)
template<typename Data>
Data & Vector<Data>::Back() {
    return const_cast<Data &>(static_cast<const Vector<Data>*>(this)->Back());
}

// Specific member functions (inherited from LinearContainer)

// operator[] (Vector)
template<typename Data>
const Data & Vector<Data>::operator[](const ulong i) const {
    if(i < size) {
        return Elements[i];
    } else {
        throw std::out_of_range("Access at index " + std::to_string(i) + "; vector size " + std::to_string(size) + ".");
    }
}

// Front (Vector)
template<typename Data>
const Data & Vector<Data>::Front() const {
    if(size != 0) {
        return Elements[0];
    } else {
        throw std::length_error("Access to an empty vector.");
    }
}

// Back (Vector)
template<typename Data>
const Data & Vector<Data>::Back() const {
    if(size != 0) {
        return Elements[size - 1];
    } else {
        throw std::length_error("Access to an empty vector.");
    }
}

// Resize & Clear
template<typename Data>
void Vector<Data>::Resize(const ulong newsize) {

    if(newsize == 0) {
        delete[] Elements;
        Elements = nullptr;
        size = 0;
    } else if(size != newsize) {
        Data * TmpE = new Data[newsize] {};
        ulong minsize = (size < newsize) ? size : newsize;
        for(ulong i = 0; i < minsize; i++) {
            std::swap(Elements[i], TmpE[i]);
        }
        std::swap(Elements, TmpE);
        size = newsize;
        delete[] TmpE;
    }
}

// Clear (Vector)
template<typename Data>
void Vector<Data>::Clear() {
    Resize(0);
}


/* ************************************************************************** */

// SortableVector

// Constructors

// SortableVector (ulong)
template<typename Data>
SortableVector<Data>::SortableVector(const ulong size) : Vector<Data>(size) { }

// SortableVector (TraversableContainer)
template<typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & container) : Vector<Data>(container) { }

// SortableVector (MappableContainer)
template<typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && container) : Vector<Data>(std::move(container)) { }

// SortableVector (Vector) copy constructor
template<typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data> & vec) : Vector<Data>(vec) { }

// SortableVector (Vector &&) move constructor
template<typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> && vec) noexcept : Vector<Data>(std::move(vec)) { }

// Copy assignment (SortableVector)
template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector<Data> & vec) {
    Vector<Data>::operator=(vec);
    return *this;
}

// Move assignment (SortableVector)
template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(SortableVector<Data> && vec) noexcept {
    Vector<Data>::operator=(std::move(vec));
    return *this;
}

}