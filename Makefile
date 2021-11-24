all: lista_circular

run:
	./lista

lista_circular: main.o circular_linked_list.o
	gcc -g -o lista main.o circular_linked_list.o

main.o: main.c circular_linked_list.h
	gcc -g -o main.o main.c -c

lista.o: circular_linked_list.c circular_linked_list.h
	gcc -g -o circular_linked_list.o circular_linked_list -c

clean:
	rm -rf *.o

zip:
	zip -r lista.zip Makefile ./*c ./*h
