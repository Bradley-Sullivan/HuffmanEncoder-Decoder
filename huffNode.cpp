#include "huffNode.h"

HuffNode::HuffNode(char c, int freqSum, HuffNode* left, HuffNode* right) {
    this->c = c;
    this->freqSum = freqSum;
    this->left = left;
    this->right = right;
}

bool HuffNode::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

int HuffNode::getFreqSum() const {
    return freqSum;
}

char HuffNode::getChar() const {
    return c;
}

HuffNode* HuffNode::getLeft() const {
    return left;
}

HuffNode* HuffNode::getRight() const {
    return right;
}

void HuffNode::setFreqSum(int freqSum) {
    this->freqSum = freqSum;
}

void HuffNode::setChar(char c) {
    this->c = c;
}

void HuffNode::setLeft(HuffNode* left) {
    this->left = left;
}

void HuffNode::setRight(HuffNode* right) {
    this->right = right;
}

bool operator==(const HuffNode& lhs, const HuffNode& rhs) {
    return lhs.freqSum == rhs.freqSum;
}

bool operator!=(const HuffNode& lhs, const HuffNode& rhs) {
    return !(lhs == rhs);
}

bool operator<(const HuffNode& lhs, const HuffNode& rhs) {
    return lhs.freqSum < rhs.freqSum;
}

bool operator>(const HuffNode& lhs, const HuffNode& rhs) {
    return lhs.freqSum > rhs.freqSum;
}

bool operator<=(const HuffNode& lhs, const HuffNode& rhs) {
    return lhs.freqSum <= rhs.freqSum;
}

bool operator>=(const HuffNode& lhs, const HuffNode& rhs) {
    return lhs.freqSum >= rhs.freqSum;
}
