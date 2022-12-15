
all: main

main: avl.o main.o
	gcc -o main $^

%.o: %.c
	gcc -c -ggdb -O0 -o $@ $<

clean:
	rm -rf *.o
	rm -rf main

