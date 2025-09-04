#include <SDL2/SDL.h>
#include <stdbool.h>

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
    int espera = 50;
    int direcao = 0;
    bool lock = false;
    while(1){
        if (evt.type == SDL_QUIT){
            break;
        }
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0xFF);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);


        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt,espera);
        if (isevt){
            espera -= (SDL_GetTicks()-antes);
            if(espera<0){
                espera =0;            
            }
            if (evt.type==SDL_QUIT){
                break;
            }
            else if(evt.type = SDL_KEYDOWN && lock == false){
                if(evt.key.keysym.sym == SDLK_SPACE){
                    lock = true;
                    direcao = (direcao+1)%4;
                }

            }


        }
        else{
            espera = 50;
            switch (direcao) {
                case 0:
                    r.x += 2;
                    if (r.x>190){
                        r.x = 190;
                        direcao = 1;
                        lock = false;
                    }
                    break;
                case 1:
                    r.y += 2;
                    if (r.y>90){
                        r.y = 90;
                        direcao = 2;
                        lock = false;
                    }
                    break;
                case 2:
                r.x -= 2;
                    if (r.x<0){
                        r.x = 0;
                        direcao = 3;
                        lock = false;
                    }
                    break;
                case 3:
                    r.y -= 2;
                    if (r.y<0){
                        r.y = 0;
                        direcao = 0;
                        lock = false;
                    }
                    break;
            }
        }
    }
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}