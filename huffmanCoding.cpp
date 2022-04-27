/**
 * @file huffmanCoding.cpp
 * @author Bradley Sullivan (bradleysullivan@nevada.unr.edu)
 * @brief Huffman coding implementation. Programmed cuz I was bored and wanted to learn how to do it I guess.
 * @version 0.1
 * @date 2022-04-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <sstream>
#include "arrayMinHeap.h"
#include "huffNode.h"

std::string getInput();
int getDistinctChars(std::string& str, int charBuffer[]);
int** evaluateCharFreq(int numDistinct, std::string str, int charBuffer[]);
void buildHuffTree(int numDistinct, int** charFreq, ArrayMinHeap<HuffNode>& nodeHeap);
std::string encodeCharacter(char c, ArrayMinHeap<HuffNode> nodeHeap);
bool buildEncodingMap(char c, HuffNode* root, std::stringstream& encodingMap);
char decodeCharacter(std::string& encoding, HuffNode* root);
int evaluateBitDepth(std::string input, ArrayMinHeap<HuffNode> nodeHeap);
void printTree(ArrayMinHeap<HuffNode> nodeHeap, HuffNode* root, int depth);

int main(void) {
    std::string input;
    std::cout << "Enter a string: ";
    input = getInput();
    std::cout << "Input: " << input << std::endl;

    ArrayMinHeap<HuffNode> heap;
    std::string encoding = "";
    int numDistinctChars = 0;
    int charBuffer[256];
    int** charFreq;
    char c;

    numDistinctChars = getDistinctChars(input, charBuffer);
    charFreq = evaluateCharFreq(numDistinctChars, input, charBuffer);

    buildHuffTree(numDistinctChars, charFreq, heap);
    std::cout << "=== Tree Constructed ===" << std::endl;

    HuffNode* rootPtr(new HuffNode(heap.peekTop()));
    printTree(heap, rootPtr, 1);

    encoding.clear();
    std::cout << "Uncompressed bit depth: " << input.length() * 8 << std::endl;
    int bitsRequired = evaluateBitDepth(input, heap);
    std::cout << "Compressed bit depth: " << bitsRequired << std::endl;

    do {
        std::cout <<"\nEnter a character to encode (press ESC then ENTER to exit): ";
        std::cin >> c;
        if (c != 27) {
            encoding = encodeCharacter(c, heap);
            std::cout << "Encoded: ";
            for (int i = (int)encoding.length() - 1; i >= 0; i--) std::cout << encoding[i];
        }  
    } while (c != 27);

    do {
        rootPtr = new HuffNode(heap.peekTop());
        std::cout << "\nEnter a single bit-string to decode (press ESC then ENTER to exit): ";
        std::cin >> encoding;
        if (encoding[0] != 27) {
            try { c = decodeCharacter(encoding, rootPtr); }
            catch (const char* msg) { std::cout << msg << std::endl; }
            std::cout << "Decoded: " << c << std::endl;
        }
    } while (encoding[0] != 27);
    

    

    return 0;
}

std::string getInput() {
    char c;
    std::string output;
    do {
        c = getchar();
        if (c != '\n') output += c;
    } while(c != '\n');
    return output;
}

int getDistinctChars(std::string& str, int charBuffer[]) {
    int numDistinctChars = 0;
    for (int i = 0; i < (int)str.length(); i++) {
        if (numDistinctChars == 0) {
            charBuffer[numDistinctChars] = str[i];
            numDistinctChars++;
        } else {
            bool isDistinct = true;
            for (int k = 0; k < numDistinctChars && isDistinct; k++) {
                if (charBuffer[k] == str[i]) isDistinct = false;
            }

            if (isDistinct) {
                charBuffer[numDistinctChars] = str[i];
                numDistinctChars++;
            }
        }
    }

    return numDistinctChars;
}

int** evaluateCharFreq(int numDistinct, std::string str, int charBuffer[]) {
    int** charFreq;
    charFreq = new int*[numDistinct];
    for (int i = 0; i < numDistinct; i++) {
        charFreq[i] = new int[2];
        charFreq[i][0] = charBuffer[i];
        charFreq[i][1] = 0;
    }

    for (int i = 0; i < (int)str.length(); i++) {
        for (int k = 0; k < numDistinct; k++) {
            if (charBuffer[k] == str[i]) {
                charFreq[k][1] += 1;
            }
        }
    }

    return charFreq;
}

void buildHuffTree(int numDistinct, int** charFreq, ArrayMinHeap<HuffNode>& nodeHeap) {
    bool pulled[numDistinct];
    int maxFreq = 0, maxFreqIdx = 0;

    for (int i = 0; i < numDistinct; i++) {
        pulled[i] = false;
    }

    for (int i = 0; i < numDistinct; i++) {
        for (int k = 0; k < numDistinct; k++) {
            if (!pulled[k]) {
                if (charFreq[k][1] > maxFreq) {
                    maxFreq = charFreq[k][1];
                    maxFreqIdx = k;
                }
            }
        }
        pulled[maxFreqIdx] = true;
        HuffNode node(charFreq[maxFreqIdx][0], charFreq[maxFreqIdx][1], nullptr, nullptr);
        // std::cout << "Added: " << node.getChar() << " " << node.getFreqSum() << std::endl;
        nodeHeap.add(node);
        maxFreq = 0;
    }
    std::cout << "=== Heap Filled ===" << std::endl;
    while (nodeHeap.getNumberOfNodes() > 1) {
        HuffNode* left(new HuffNode(nodeHeap.peekTop()));
        nodeHeap.remove(nodeHeap.peekTop());
        HuffNode* right(new HuffNode(nodeHeap.peekTop()));
        nodeHeap.remove(nodeHeap.peekTop());
        HuffNode parent('\0', left->getFreqSum() + right->getFreqSum(), left, right);

        nodeHeap.add(parent);
    }

}

std::string encodeCharacter(char c, ArrayMinHeap<HuffNode> nodeHeap) {
    std::stringstream encoding;
    HuffNode* root(new HuffNode(nodeHeap.peekTop()));
    buildEncodingMap(c, root, encoding);
    return encoding.str();
}

bool buildEncodingMap(char c, HuffNode* root, std::stringstream& encodingMap) {
    if (root != nullptr) {
        if (root->getChar() == c) {
            return true;
        } if (buildEncodingMap(c, root->getLeft(), encodingMap)) {
            encodingMap << "0";
            return true;
        } if (buildEncodingMap(c, root->getRight(), encodingMap)) {
            encodingMap << "1";
            return true;
        }
        return false;
    } else {
        return false;
    }    
}

char decodeCharacter(std::string& encoding, HuffNode* root) {
    for (int i = 0; i < (int)encoding.length() && root != nullptr; i++) {
        if (encoding[i] == '0') {
            root = root->getLeft();
        } else {
            root = root->getRight();
        }
    }

    if (root != nullptr) {
        return root->getChar();
    } else {
        throw std::runtime_error("Error: Invalid character encoding string");
    }
}

int evaluateBitDepth(std::string input, ArrayMinHeap<HuffNode> nodeHeap) {
    // Character buffer and getDistinctChar call is sloppy but I'm tired as fuck rn
    int buf[256];
    int numDistinctChars = getDistinctChars(input, buf);
    int bitDepth = 0;
    std::string encoding;
    for (int i = 0; i < numDistinctChars; i++) {
        encoding = encodeCharacter(buf[i], nodeHeap);
        bitDepth += (int)encoding.length();
        encoding.clear();
    }

    return bitDepth;
}

void printTree(ArrayMinHeap<HuffNode> nodeHeap, HuffNode* root, int depth) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        if (i == depth - 1) {
            std::cout << "---|";
        } else {
            std::cout << "--- ";
        }
    }
    if (root->getChar() == '\0') {
        printf("#  %d\n", root->getFreqSum());
    } else {
        printf("%c  %d (", root->getChar(), root->getFreqSum());
        std::string s = encodeCharacter(root->getChar(), nodeHeap);
        for (int i = s.length() - 1; i >= 0; i--) std::cout << s[i];        // String library really needs a printStringInReverse function ffs
        printf(")\n");
    }
    printTree(nodeHeap, root->getLeft(), depth + 1);
    printTree(nodeHeap, root->getRight(), depth + 1);
}
