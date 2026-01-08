INCLUDES= -I ./include
FLAGS= -g -lSDL2 -lSDL2main

OBJECTS=./build/chip8memory.o
all: ${OBJECTS}
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} -o ./bin/main

./build/chip8memory.o:src/chip8memory.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8memory.c -c -o ${OBJECTS}

clean:
	rm -rf build/*