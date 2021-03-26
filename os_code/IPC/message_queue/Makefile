cc=gcc
.PHONY:all
all: read write

read: message_queue_consumer.c
	cc -o $@ $^
write: message_queue_producer.c
	cc -o $@ $^
.PHONY:clean
clean:	
	rm  read write
