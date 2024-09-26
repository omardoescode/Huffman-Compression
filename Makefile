all: main.o priority_queue.o huffman_tree.o vector.o bit_packer.o
	cc main.o priority_queue.o huffman_tree.o vector.o bit_packer.o -o compress 

main.o: main.c
	cc -c main.c 
 
test_queue: priority_queue_test.o priority_queue.o huffman_tree.o
	cc priority_queue_test.o priority_queue.o huffman_tree.o -o test_queue

priority_queue_test.o:  priority_queue_test.c 
	cc -c priority_queue_test.c 

priority_queue.o: src/priority_queue.c include/priority_queue.h
	cc -c src/priority_queue.c

test_wide: wide_test.o
	cc wide_test.o -o test_wide

wide_test.o: wide_test.c
	cc -c wide_test.c

huffman_tree.o: src/huffman_tree.c include/huffman_tree.h
	cc -c src/huffman_tree.c

vector.o: src/vector.c include/vector.h
	cc -c src/vector.c

bit_packer.o: src/bit_packer.c include/bit_packer.h
	cc -c src/bit_packer.c
clean:
	rm *.o compress test
