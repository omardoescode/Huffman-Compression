CC=gcc
CFLAGS=-Wall -fno-builtin -include interpose.h -I./include -lm

all: main.o priority_queue.o huffman_tree.o vector.o bit_packer.o bit_unpacker.o tree_serializer.o interpose.o
	$(CC) $(CFLAGS) $^ -o compress

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

test_queue: priority_queue_test.o priority_queue.o huffman_tree.o
	$(CC) $(CFLAGS) $^ -o $@

priority_queue_test.o: priority_queue_test.c 
	$(CC) $(CFLAGS) -c $< -o $@

test_wide: wide_test.o
	$(CC) $(CFLAGS) $< -o $@

wide_test.o: wide_test.c
	$(CC) $(CFLAGS) -c $< -o $@
interpose.o: src/interpose.c include/interpose.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o compress test_queue test_wide
