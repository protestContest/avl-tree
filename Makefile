CPP = g++
CFLAGS = -Wall -Wextra -Werror


ttest: tree_test.cpp BST.o Node.o
	$(CPP) $(CFLAGS) -o ttest $^

BST.o: BST.h BST.cpp
	$(CPP) $(CFLAGS) -c BST.cpp

ntest: node_test.cpp Node.o
	$(CPP) $(CFLAGS) -o ntest node_test.cpp Node.o

Node.o: Node.h Node.cpp
	$(CPP) $(CFLAGS) -c Node.cpp

clean:
	rm -f *.o;
	rm -f ntest; rm -f ttest;
	rm -f *~;
