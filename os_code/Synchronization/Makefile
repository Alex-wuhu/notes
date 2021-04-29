.PHONY:all
all:Dining  first_read
Dining:Dining_Philosophers.c
	gcc -o $@ $^ -lpthread
first_read:first_reader_writer.c
	gcc -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm Dining first_read
