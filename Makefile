
all: main

main: avl.o main.o
	gcc -o main $^

%.o: %.c
	gcc -gdwarf-2 -O0 -c -ggdb -O0 -o $@ $<

clean:
	rm -rf *.o
	rm -rf main

