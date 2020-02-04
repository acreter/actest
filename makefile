all:
	mkdir -p build/
	$(CC) -c src/actest.c -o src/actest.o
	ar rcs build/libactest.a src/actest.o

example: all
	$(CC) -c example.c
	$(CC) -o example example.o -L build/ -lactest

clean:
	rm -f src/actest.o
	rm -rf build/
	rm -f example
	rm -f example.o

.PHONY: all example clean
