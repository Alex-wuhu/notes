cc=gcc
.PHONY:all
all: read write

read:shared_reader.c
	cc -o $@ $^
write:shared_writer.c
	cc -o $@ $^

.PHONY:clean
clean:
	rm  read write
