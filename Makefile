build: main.c
	cc main.c $(shell pkg-config --libs --cflags raylib) -o main

run: build
	./main
