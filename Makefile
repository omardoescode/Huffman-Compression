main: main.o priority_queue.o huffman_tree.o
	cc main.o priority_queue.o huffman_tree.o -o compress

main.o: main.c
	cc -c main.c

test_queue: priority_queue_test.o priority_queue.o huffman_tree.o
	cc priority_queue_test.o priority_queue.o huffman_tree.o -o test

priority_queue_test.o:  priority_queue_test.c 
	cc -c priority_queue_test.c 

priority_queue.o: src/priority_queue.c include/priority_queue.h
	cc -c src/priority_queue.c

huffman_tree.o: src/huffman_tree.c include/huffman_tree.h
	cc -c src/huffman_tree.c

clean:
	rm *.o compress test
