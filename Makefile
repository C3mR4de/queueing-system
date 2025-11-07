.PHONY: all build run clean

all: build run

build:
	gcc -O0 -g -Wall -Wextra -Wpedantic *.c -o main -lm

run:
	./main

clean:
	rm main
