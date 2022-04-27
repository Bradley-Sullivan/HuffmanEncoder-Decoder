#ifndef HEAPH_INTERFACE_H
#define HEAPH_INTERFACE_H

template<typename ItemType>
class HeapInterface {
public:
    virtual bool isEmpty() const = 0;
    virtual int getHeight() const = 0;
    virtual int getNumberOfNodes() const = 0;
    virtual bool add(const ItemType& newItm) = 0;
    virtual bool remove(const ItemType& itm) = 0;
    virtual ItemType peekTop() const = 0;
    virtual void clear() = 0;
    virtual ~HeapInterface() {}
};

#endif //HEAPH_INTERFACE_H