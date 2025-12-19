INCLUDES= -I ./include
FLAGS= -g -lSDL2 -lSDL2main
all:
	gcc ${FLAGS} ${INCLUDES} ./src/main.c -o ./bin/main