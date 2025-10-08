
namespace lasd {

// Map (PostOrderMappableContainer)
template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun function){
    PostOrderMap(function);
}

// Map (PreOrderMappableContainer)
template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun function){
    PreOrderMap(function);
}

}
