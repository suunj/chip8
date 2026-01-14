#include <stdio.h>
#include "SDL2/SDL.h"
#include "chip8.h"
#include "chip8keyboard.h"

const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};

int main() {
    struct chip8 chip8;
    chip8_init(&chip8);

    chip8_screen_set(&chip8.screen, 0, 0);

    // SDL 라이브러리 초기화 (비디오, 오디오, 이벤트 등 모든 서브시스템)
    SDL_Init(SDL_INIT_EVERYTHING);

    // 윈도우 생성: 제목, 위치(자동), 크기(640x320), 표시 옵션
    SDL_Window *window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLER,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLER,
        SDL_WINDOW_SHOWN
    );

    // 렌더러 생성: 윈도우에 그래픽을 그리기 위한 객체
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);

    // 메인 루프
    while (1) {
        SDL_Event e;

        // 이벤트 폴링: 키보드, 마우스, 윈도우 이벤트 처리
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    goto out;
                    break;
                case SDL_KEYDOWN: {
                    char key = e.key.keysym.sym;
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    if (vkey != -1) {
                        chip8_keyboard_down(&chip8.keyboard, vkey);
                    }
                    break;
                }
                case SDL_KEYUP: {
                    char key = e.key.keysym.sym;
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    if (vkey != -1) {
                        chip8_keyboard_up(&chip8.keyboard, vkey);
                    }
                    break;
                }
            }
        }

        // 배경색 설정 (검정색) 및 화면 클리어
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // 그리기 색상 설정 (흰색)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for (int x = 0; x < CHIP8_WIDTH; x++) {
            for (int y = 0; y < CHIP8_HEIGHT; y++) {
                if (chip8_screen_is_set(&chip8.screen, x, y)) {
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOW_MULTIPLER;
                    r.y = y * CHIP8_WINDOW_MULTIPLER;
                    r.w = CHIP8_WINDOW_MULTIPLER;
                    r.h = CHIP8_WINDOW_MULTIPLER;

                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        // 렌더링 결과를 화면에 표시
        SDL_RenderPresent(renderer);
    }

out:
    // 리소스 정리
    SDL_DestroyWindow(window);
    return 0;
}