#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <assert.h>

int main (int argc, char* args[]){
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 400, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img  = IMG_LoadTexture(ren,"bubble.png");
    assert(img !=NULL);

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 50,100 };
    SDL_Rect c = {50, 320, 300, 800};
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
        if (lock) {
            c = (SDL_Rect) {  600,320, 300,800 };
        } else {
            c = (SDL_Rect) { 50,320, 300,800 };
        }
        SDL_RenderCopy(ren,img,&c,&r);
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
            espera = 15;
            switch (direcao) {
                case 0:
                    r.x += 2;
                    if (r.x>350){
                        r.x = 350;
                        direcao = 1;
                        lock = false;
                    }
                    break;
                case 1:
                    r.y += 2;
                    if (r.y>350){
                        r.y = 350;
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
