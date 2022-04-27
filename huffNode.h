#ifndef HUFF_NODE_H
#define HUFF_NODE_H

class HuffNode {
    int freqSum;
    char c;
    HuffNode* left;
    HuffNode* right;
public:
    HuffNode() = default;
    HuffNode(char c, int freqSum, HuffNode* left, HuffNode* right);
    bool isLeaf() const;
    int getFreqSum() const;
    char getChar() const;
    HuffNode* getLeft() const;
    HuffNode* getRight() const;
    void setFreqSum(int freqSum);
    void setChar(char c);
    void setLeft(HuffNode* left);
    void setRight(HuffNode* right);
    ~HuffNode() = default;

    friend bool operator==(const HuffNode& lhs, const HuffNode& rhs);
    friend bool operator!=(const HuffNode& lhs, const HuffNode& rhs);
    friend bool operator<(const HuffNode& lhs, const HuffNode& rhs);
    friend bool operator>(const HuffNode& lhs, const HuffNode& rhs);
    friend bool operator<=(const HuffNode& lhs, const HuffNode& rhs);
    friend bool operator>=(const HuffNode& lhs, const HuffNode& rhs);
};

#endif // HUFF_NODE_H