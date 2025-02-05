#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#define LC(x) x*2 +1
#define RC(x) x*2 +2
#define PA(x) x/2
#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;

public:
    MinHeap() {}

    /// <summary>
    /// insert key-value pair
    /// </summary>
    ///
    /// <param name="key">
    /// the key that is used for sorting
    /// </param>
    ///
    /// <param name="value">
    /// the value that is managed in this heap
    /// </param>
    void Push(TKey key, TValue value);
    /// <summary>
    /// remove the minimum element
    /// </summary>
    void Pop();
    /// <summary>
    /// get the minimum element
    /// </summary>
    ///
    /// <returns>
    /// the minimum element
    /// </returns>
    std::pair<TKey, TValue> Top();
    /// <summary>
    /// get the key-value pair which the value is the same as the target
    /// </summary>
    ///
    /// <returns>
    /// the key-value pair which the value is the same as the target
    /// </returns>
    std::pair<TKey, TValue> Get(TValue target);
    /// <summary>
    /// check whether this heap is empty or not
    /// </summary>
    ///
    /// <returns>
    /// true if this heap is empty
    /// </returns>
    bool IsEmpty();
    /// <summary>
    /// change the key of the node which the value is the target.<para/>
    /// In general, the newKey should be smaller than the old key.<para/>
    /// </summary>
    ///
    /// <parma name="target">
    /// the target to change the key
    /// </param>
    ///
    /// <param name="newKey">
    /// new key for the target
    /// </param>
    void DecKey(TValue target, TKey newKey);

private:
    /// <summary>
    /// heap-sort, heapify.<para/>
    /// this function can be called recursively
    /// </summary>
    void Heapify(int index);
};

#endif

template<typename TKey, typename TValue>
inline void MinHeap<TKey, TValue>::Push(TKey key, TValue value)
{
}

template<typename TKey, typename TValue>
inline void MinHeap<TKey, TValue>::Pop()
{
}

template<typename TKey, typename TValue>
inline std::pair<TKey, TValue> MinHeap<TKey, TValue>::Top()
{
	return std::pair<TKey, TValue>();
}

template<typename TKey, typename TValue>
inline bool MinHeap<TKey, TValue>::IsEmpty()
{
	return false;
}

template<typename TKey, typename TValue>
inline void MinHeap<TKey, TValue>::DecKey(TValue target, TKey newKey)
{
}

template<typename TKey, typename TValue>
inline void MinHeap<TKey, TValue>::Heapify(int index)
{

}
