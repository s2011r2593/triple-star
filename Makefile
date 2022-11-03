CC := gcc
CFLAGS = -g -O0

bin/triple-star: build/main.o
	$(CC) -o $@ $^

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf build/*.o

.PHONY: clean

