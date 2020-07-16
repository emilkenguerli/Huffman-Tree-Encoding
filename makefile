CXX=g++
RM=rm -f
CFLAGS = -std=c++11
LDFLAGS=-g $(--ldflags)
LDLIBS=$(--libs)

SRCS=main.cpp HuffmanTree.cpp HuffmanNode.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: huffencode

test: UnitTesting.o
	$(CXX) $(CFLAGS) UnitTesting.o -o test $(LDLIBS)

UnitTesting.o: UnitTesting.cpp catch.hpp
	$(CXX) $(CFLAGS) -c UnitTesting.cpp

huffencode: $(OBJS)
	$(CXX) $(LDFLAGS) -o huffencode $(OBJS) $(LDLIBS)

main.o: main.cpp HuffmanTree.cpp HuffmanNode.cpp

HuffmanTree.o: HuffmanTree.h HuffmanTree.cpp

HuffmanNode.o: HuffmanNode.h HuffmanNode.cpp

UnitTesting: test
	.\test	

run: huffencode
	.\huffencode aaa.txt output

clean:
	$(RM) *.o
	$(RM) huffencode
	$(RM) test