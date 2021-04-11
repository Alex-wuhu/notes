.PHONY:all
all: sum sum_improved

sum_improved:multiThread_improved.c
	gcc -o $@ $^ -lpthread

sum:multiThread.c
	gcc -o $@ $^ -lpthread
clean:
	rm sum sum_improved
