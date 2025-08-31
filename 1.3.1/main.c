#include <SDL2/SDL.h>

int main (int argc, char* args[]){
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    int direcao = 1;
    int run = 1;
    while(run){
        if (evt.type == SDL_QUIT){
            break;
        }
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0xFF);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
        switch (direcao) {
            case 1:
                r.x += 2;
                if (r.x>190){
                    r.x = 190;
                    direcao = 2;
                }
                break;
            case 2:
                r.y += 2;
                if (r.y>90){
                    r.y = 90;
                    direcao = 3;
                }
                break;
            case 3:
                r.x -= 2;
                if (r.x<0){
                    r.x = 0;
                    direcao = 4;
                }
                break;
            case 4:
                r.y -= 2;
                if (r.y<0){
                    r.y = 0;
                    direcao = 1;
                }
                break;
        }
        while (SDL_PollEvent(&evt)) {  
            if (evt.type == SDL_QUIT) {
                run = 0;  
            }
        }
        SDL_Delay(100);
    }
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
