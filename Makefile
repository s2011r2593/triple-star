CC := cc
CFLAGS = -g -O0

bin/triple-star: build/main.o
	$(CC) -o $@ $^

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

build/main.o: src/go.h src/util.h
build/go.o: src/go.h src/util.h
build/util.c: src/util.h

clean:
	rm -rf build/*.o

.PHONY: clean

