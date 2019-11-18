all: dir_main.o
	gcc -o program dir_main.o

dir_main.o: dir_main.c
	gcc -c dir_main.c

run:
	./program

clean:
	rm *.o
	rm *~

memcheck:
	valgrind --leak-check:yes ./test_stat
