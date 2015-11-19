CC = gcc
FLAGS = -Wall
FILES = clientTCP.c parser.c download.c getip.c 
OUT_EXE = download

all:
	$(CC) -o $(OUT_EXE) main.c $(FILES) $(FLAGS)

clean:
	rm -f *.o
