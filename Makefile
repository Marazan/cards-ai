all:
	gcc -std=c99 cards.h briscola.h cards.c briscola.c main.c -o cards.exe
debug:
	gcc -g -std=c99 cards.h briscola.h cards.c briscola.c main.c -o cards.exe
clean:
	rm cards.exe
