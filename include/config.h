#ifndef CONFIG_H
#define CONFIG_H

/*
Memory Map:
+---------------+= 0xFFF (4095) End of Chip-8 RAM
|               |
|               |
|               |
|               |
|               |
| 0x200 to 0xFFF|
|     Chip-8    |
| Program / Data|
|     Space     |
|               |
|               |
|               |
+- - - - - - - -+= 0x600 (1536) Start of ETI 660 Chip-8 programs
|               |
|               |
|               |
+---------------+= 0x200 (512) Start of most Chip-8 programs
| 0x000 to 0x1FF|
| Reserved for  |
|  interpreter  |
+---------------+= 0x000 (0) Start of Chip-8 RAM
*/
#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32
#define EMULATOR_WINDOW_TITLE "Chip8 Emulator"
#define CHIP8_WINDOW_MULTIPLER 10

#define CHIP8_TOTAL_DATA_REGISTERS 16
#define CHIP8_TOTAL_STACK_DEPTH 16
#define CHIP8_TOTAL_KEYS 16
#define CHIP8_CHARACTER_SET_LOAD_ADDRESS 0x00
#endif