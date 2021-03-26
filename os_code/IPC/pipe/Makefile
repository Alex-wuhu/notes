cc=gcc
.PHONY:all
all: read write

read: namedpipe_reader.c
	cc -o $@ $^
write:namedpipe_writer.c
	cc -o $@ $^
.PHONY:clean
clean:
	rm  read write
