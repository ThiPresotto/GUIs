#include <SDL2/SDL.h>


int main (int argc, char* args[]){

    /*INICIALIZAÇÃO*/
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("3 Retângulos",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        600,600,SDL_WINDOW_SHOWN
    );
    SDL_Renderer* ren = SDL_CreateRenderer(window,-1,0);


    /*EXECUÇÃO*/
    SDL_Rect r1 = {40,20,25,25};
    SDL_Rect r2 = {290,290,25,25};
    SDL_Rect r3 = {535,555,25,25};
    int espera = 1000;
    int direcao = 1;

    while(1){
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren,0xFF,0x00,0x00,0x00);
        SDL_RenderFillRect(ren,&r1);
        SDL_SetRenderDrawColor(ren,0x00,0xFF,0x00,0x00);
        SDL_RenderFillRect(ren,&r2);
        SDL_SetRenderDrawColor(ren,0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren,&r3);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt,espera);
        if (isevt){
            espera -= (SDL_GetTicks()-antes);
            if (espera<0) { 
                espera = 0;
            }
            if(evt.type == SDL_KEYDOWN){
                switch(evt.key.keysym.sym){
                    case SDLK_UP:
                    r2.y -= 5;
                    break;
                    case SDLK_DOWN:
                    r2.y += 5;
                    break;
                    case SDLK_LEFT:
                    r2.x -= 5;
                    break;
                    case SDLK_RIGHT:
                    r2.x += 5;
                    break;
                }
            
            }
            else if (evt.type == SDL_QUIT){
                break;
            }
            else if (evt.type == SDL_MOUSEMOTION){
                r3.x = evt.motion.x - (r3.h/2);
                r3.y = evt.motion.y - (r3.w/2);
            }

        }
        else {
            espera = 10;
            switch(direcao){
                case 1:
                    r1.x +=5;
                    if(r1.x > 535){
                        r1.x = 535;
                        direcao = 2;
                    }
                    break;
                case 2:
                    r1.y +=5;
                    if(r1.y > 555){
                        r1.y = 535;
                        direcao = 3;
                    }
                    break;
                case 3:
                    r1.x -=5;
                    if(r1.x < 40){
                        r1.x = 40;
                        direcao = 4;
                    }
                    break;
                case 4:
                    r1.y -=5;
                    if(r1.y < 20){
                        r1.y = 20;
                        direcao = 1;
                    }
                    break;
            }
        } 



    }

    /*FINALIZAÇÃO*/
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
