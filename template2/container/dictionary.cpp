
namespace lasd {

// DictionaryContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &container) {
    bool all = true;
    container.Traverse([this, &all](const Data & data) {
        all &= Insert(data);
    });
    return all;
}

// RemoveAll (TraversableContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &container) {
    bool all = true;
    container.Traverse([this, &all](const Data & data) {
        all &= Remove(data);
    });
    return all;
}

// RemoveSome (TraversableContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &container) {
    bool some = false;
    container.Traverse([this, &some](const Data & data) {
        some |= Remove(data);
    });
    return some;
}

// InsertAll (MappableContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&container) {
    bool all = true;
    container.Map([this, &all](Data & data) {
        all &= Insert(std::move(data));
    });
    return all;
}

// InsertSome (TraversableContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &container) {
    bool some = false;
    container.Traverse([this, &some](const Data & data) {
        some |= Insert(data);
    });
    return some;
}

// InsertSome (MappableContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&container) {
    bool some = false;
    container.Traverse([this, &some](const Data & data) {
        some |= Insert(std::move(data));
    });
    return some;
}

}