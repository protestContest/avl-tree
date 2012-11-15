CPP = g++
CFLAGS = -Wall -Wextra -Werror -lm -ggdb


ttest: tree_test.cpp avltree.cpp Node.cpp
	$(CPP) $(CFLAGS) -o ttest tree_test.cpp avltree.cpp Node.cpp

clean:
	rm -f *.o;
	rm -f ntest; rm -f ttest;
	rm -f *~;
