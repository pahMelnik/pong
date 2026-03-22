build: main.c
	cc main.c $(shell pkg-config --libs --cflags raylib) -o main -lm

run: build
	./main
