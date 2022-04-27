#include "arrayMinHeap.h"

template<typename ItemType>
ArrayMinHeap<ItemType>::ArrayMinHeap() {
    itemCt = 0;
}

template<typename ItemType>
bool ArrayMinHeap<ItemType>::isEmpty() const {
    return itemCt == 0;
}

template<typename ItemType>
int ArrayMinHeap<ItemType>::getHeight() const {
    return getHeightHelper(0);
}

template<typename ItemType>
int ArrayMinHeap<ItemType>::getNumberOfNodes() const {
    return itemCt;
}

template<typename ItemType>
bool ArrayMinHeap<ItemType>::add(const ItemType& newItm) {
    int curIdx = itemCt;
    bool isAdded = false;
    items[itemCt] = newItm;

    if (itemCt == 0) {
        items[itemCt] = newItm;
        itemCt++;
        isAdded = true;
    } else if (itemCt < DEFAULT_CAPACITY) {
        while (curIdx >= 0 && !isAdded) {
            int parentIdx = getParentIndex(curIdx);
            if (items[curIdx] >= items[parentIdx]) {
                isAdded = true;
                itemCt++;
            } else {
                ItemType swap = items[curIdx];
                items[curIdx] = items[parentIdx];
                items[parentIdx] = swap;
                curIdx = parentIdx;
            }
        }
    }   

    return isAdded;
}

template<typename ItemType>
bool ArrayMinHeap<ItemType>::remove(const ItemType& itm) {
    bool isSwapped = false;
    int curIdx = 0;
    for (int i = 0; i < itemCt && !isSwapped; i++) {
        if (items[i] == itm) {
            ItemType swap = items[i];
            items[i] = items[itemCt - 1];
            items[itemCt - 1] = swap;
            curIdx = i;
            itemCt--;
            isSwapped = true;
        }
    }

    if (isSwapped) {
        heapRebuild(curIdx);
        return true;
    } else {
        return false;
    }
}

template<typename ItemType>
ItemType ArrayMinHeap<ItemType>::peekTop() const {
    if (itemCt > 0) {
        return items[0];
    } else {
        throw std::runtime_error("Heap is empty");
    }
}

template<typename ItemType>
void ArrayMinHeap<ItemType>::clear() {
    itemCt = 0;
}

template<typename ItemType>
ArrayMinHeap<ItemType>::~ArrayMinHeap() {
    itemCt = 0;
}

template<typename ItemType>
int ArrayMinHeap<ItemType>::getLeftChildIndex(int nodeIndex) const {
    int leftIdx = 2 * nodeIndex + 1;
    if (leftIdx < itemCt) {
        return leftIdx;
    } else {
        return -1;
    }
}

template<typename ItemType>
int ArrayMinHeap<ItemType>::getRightChildIndex(int nodeIndex) const {
    int rightIdx = 2 * nodeIndex + 2;
    if (rightIdx < itemCt) {
        return rightIdx;
    } else {
        return -1;
    }
}

template<typename ItemType>
int ArrayMinHeap<ItemType>::getParentIndex(int nodeIndex) const {
    int parentIdx = (nodeIndex - 1) / 2;
    if (parentIdx >= 0) {
        return parentIdx;
    } else {
        return -1;
    }
}

template<typename ItemType>
bool ArrayMinHeap<ItemType>::isLeaf(int nodeIndex) const {
    int leftIdx = getLeftChildIndex(nodeIndex);
    int rightIdx = getRightChildIndex(nodeIndex);
    return (leftIdx == -1 && rightIdx == -1);
}

template<typename ItemType>
int ArrayMinHeap<ItemType>::getHeightHelper(int idx) const {
    if (isLeaf(idx)) {
        return 0;
    } else {
        int leftChildIdx = getLeftChildIndex(idx);
        int rightChildIdx = getRightChildIndex(idx);
        int leftChildHeight = getHeightHelper(leftChildIdx);
        int rightChildHeight = getHeightHelper(rightChildIdx);
        return 1 + (leftChildHeight > rightChildHeight ? leftChildHeight : rightChildHeight);
    }
}

template<typename ItemType>
void ArrayMinHeap<ItemType>::heapRebuild(int nodeIndex) {
    int leftChildIdx = getLeftChildIndex(nodeIndex);
    int rightChildIdx = getRightChildIndex(nodeIndex);
    int largestIdx = nodeIndex;
    if (leftChildIdx != -1 && items[leftChildIdx] < items[nodeIndex]) {
        largestIdx = leftChildIdx;
    }

    if (rightChildIdx != -1 && items[rightChildIdx] < items[largestIdx]) {
        largestIdx = rightChildIdx;
    }

    if (largestIdx != nodeIndex) {
        ItemType swap = items[nodeIndex];
        items[nodeIndex] = items[largestIdx];
        items[largestIdx] = swap;
        heapRebuild(largestIdx);
    }   
}
