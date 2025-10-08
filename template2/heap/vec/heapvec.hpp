
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

#include "../heap.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class HeapVec: virtual public Heap<Data>,  protected SortableVector<Data> { 

  private:
 // ...
  protected:
 // ...
    using Container::size;

  public:

    // Default constructor
    HeapVec() = default;

    // Specific constructors
    HeapVec(const TraversableContainer<Data>&);  // A heap obtained from a TraversableContainer
    HeapVec(MappableContainer<Data>&&); // A heap obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    HeapVec(const HeapVec&);

    // Move constructor
    HeapVec(HeapVec&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~HeapVec() = default;

    /* ************************************************************************ */

    // Copy assignment
    HeapVec & operator=(const HeapVec&);

    // Move assignment
    HeapVec & operator=(HeapVec&&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const HeapVec&) const noexcept;
    bool operator!=(const HeapVec&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Heap)

    bool IsHeap() const override; // Override Heap member
    void Heapify() override; // Override Heap member

    /* ************************************************************************ */

    // Specific member function (inherited from SortableLinearContainer)

    void Sort() noexcept override; // Override SortableLinearContainer member

    /* ************************************************************************ */
    const Data & operator[](ulong) const override;
    Data & operator[](ulong)  override;
    using Heap<Data>::Front;
    using Heap<Data>::Back;

    void Clear() override;

  protected:
    ulong GetSx(ulong i) const;
    ulong GetDx(ulong i) const;
    void heapify(ulong n, ulong i);

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
