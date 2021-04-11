.PHONY:all
all:parent child atomic
atomic:Peterson_lock.cpp
	g++ -o $@ $^ -lpthread
child:child.c
	gcc -o $@ $^
parent:Peterson_shared_memory.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm atomic child parent
