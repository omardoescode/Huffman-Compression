CC=gcc
CFLAGS=-Wall -fno-builtin  -lm

all: main.o priority_queue.o huffman_tree.o vector.o bit_packer.o bit_unpacker.o tree_serializer.o 
	$(CC) $(CFLAGS) $^ -o huff

debug: main.o priority_queue.o huffman_tree.o vector.o bit_packer.o bit_unpacker.o tree_serializer.o interpose.o
	$(CC) $(CFLAGS) -include interpose.h  -I./include $^ -o huff

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

interpose.o: src/interpose.c include/interpose.h
	$(CC) $(CFLAGS) -c $< -o $@

docs: Doxyfile
	doxygen Doxyfile

clean:
	rm -f *.o

clean_docs: 
	rm ./docs -rf
