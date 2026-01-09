#include <stdio.h>
#include "SDL2/SDL.h"
#include "chip8.h"

int main() {
   struct chip8 chip8;
   chip8.registers.SP = 0;
   chip8_stack_push(&chip8, 0xff);
   chip8_stack_push(&chip8, 0xaa);

   printf("%x\n", chip8_stack_pop(&chip8));
   printf("%x\n", chip8_stack_pop(&chip8));

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
   while(1) {
      SDL_Event e;
      SDL_Rect r;

      // 이벤트 폴링: 키보드, 마우스, 윈도우 이벤트 처리
      while (SDL_PollEvent(&e)) {
         // 윈도우 닫기 버튼 클릭 시 종료
         if (e.type == SDL_QUIT) {
            goto out;
         }
      }

      // 배경색 설정 (검정색) 및 화면 클리어
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderClear(renderer);

      // 그리기 색상 설정 (흰색)
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

      // 사각형 정의: 좌표(0,0), 크기(40x40)
      r.x = 0;
      r.y = 0;
      r.w = 40;
      r.h = 40;

      // 사각형 테두리 그리기
      SDL_RenderDrawRect(renderer, &r);

      // 렌더링 결과를 화면에 표시
      SDL_RenderPresent(renderer);
   }

out:
   // 리소스 정리
   SDL_DestroyWindow(window);
   return 0;
}