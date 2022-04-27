CC = g++
CFLAGS = -g -Wall

all: huff

huff: huffmanCoding.o huffNode.o
	$(CC) $(CFLAGS) huffmanCoding.o huffNode.o -o huff

huffmanCoding.o: huffmanCoding.cpp
	$(CC) $(CFLAGS) -c huffmanCoding.cpp

huffNode.o: huffNode.cpp
	$(CC) $(CFLAGS) -c huffNode.cpp

clean:
	rm huff *.o