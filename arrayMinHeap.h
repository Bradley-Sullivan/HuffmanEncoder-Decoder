#ifndef ARRAY_MIN_HEAP_H
#define ARRAY_MIN_HEAP_H

#include "heapInterface.h"
#include <iostream>

static const int DEFAULT_CAPACITY = 100;

template<typename ItemType>
class ArrayMinHeap : public HeapInterface<ItemType> {
    ItemType items[DEFAULT_CAPACITY];
    int itemCt;
public:
    ArrayMinHeap();
    bool isEmpty() const override;
    int getHeight() const override;
    int getNumberOfNodes() const override;
    bool add(const ItemType& newItm) override;
    bool remove(const ItemType& itm) override;
    ItemType peekTop() const override;
    void clear() override;
    ~ArrayMinHeap();
protected:
    int getLeftChildIndex(int nodeIndex) const;
    int getRightChildIndex(int nodeIndex) const;
    int getParentIndex(int nodeIndex) const;
    int getHeightHelper(int idx) const;
    bool isLeaf(int nodeIndex) const;
    void heapRebuild(int nodeIndex);
};
#include "arrayMinHeap.cpp"
#endif //ARRAY_MIN_HEAP_H