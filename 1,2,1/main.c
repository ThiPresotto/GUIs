#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         16*50, 16*50, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */

    SDL_SetRenderDrawColor(ren, 0x08,0x85,0x39,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0x00,0x00);
    
    SDL_Rect r1 = { 2*50,4*50, 4*50, 4*50 };
    SDL_RenderFillRect(ren, &r1);

    SDL_Rect r2 = { 10*50,4*50,4*50,4*50};
    SDL_RenderFillRect(ren,&r2);

    SDL_Rect r3 = { 6*50,8*50, 4*50, 6*50};
    SDL_RenderFillRect(ren, &r3);

    SDL_Rect r4 = { 4*50,10*50, 2*50, 6*50 };
    SDL_RenderFillRect(ren, &r4);

    SDL_Rect r5 = {  10*50,10*50, 2*50, 6*50 };
    SDL_RenderFillRect(ren, &r5);


    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
