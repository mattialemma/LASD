
namespace lasd {

// TraversableContainer

// Fold (TraversableContainer)
template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator acc) const {
    Traverse([function, &acc](const Data & data) {
        acc = function(data, acc);
    }
            );
    return acc;
}

// Exists (TraversableContainer)
template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data & v) const noexcept  {
    bool exists = false;
    Traverse([v, &exists](const Data & data) {
        exists |= (data == v);
    });
    return exists;
}

/* ************************************************************************** */

// PreOrderTraversableContainer

// Traverse (PreOrderTraversableContainer)
template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
    PreOrderTraverse(function);
}

// PreOrderFold (PreOrderTraversableContainer)
template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator acc) const {
    PreOrderTraverse([function, &acc](const Data & data) {
        acc = function(data, acc);
    });
    return acc;
}

/* ************************************************************************** */

// PostOrderTraversableContainer

// Traverse (PostOrderTraversableContainer)
template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
    PostOrderTraverse(function);
}

// PostOrderFold (PostOrderTraversableContainer)
template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator acc) const {
    PostOrderTraverse([function, &acc](const Data & data) {
        acc = function(data, acc);
    });
    return acc;
}

}
