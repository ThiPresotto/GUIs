#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>


int main (int argc, char* args[]){

    /*INICIALIZAÇÃO*/
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("3 Retângulos",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        600,600,SDL_WINDOW_SHOWN
    );
    SDL_Renderer* ren = SDL_CreateRenderer(window,-1,0);
    TTF_Font* fnt = TTF_OpenFont("tiny.ttf",20);
    assert(fnt != NULL);
    SDL_Color clr = {0xFF,0x00,0x00,0xFF};
    SDL_Surface* sfc;
    SDL_Texture* txt;
    


    /*EXECUÇÃO*/
    SDL_Rect r1 = {40,20,25,25};
    SDL_Rect r2 = {40,290,25,25};
    SDL_Rect r3 = {40,555,25,25};
    SDL_Rect line = {570,0,15,600};
    int espera = 1000;
    int winner;
    bool fin[3] = {false,false,false};
    SDL_Rect vencedor = { 250,500, 150,80 };

    while(1){
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren,0xFF,0,0,0);
        SDL_RenderFillRect(ren,&line);
        SDL_SetRenderDrawColor(ren,0xFF,0x00,0x00,0x00);
        SDL_RenderFillRect(ren,&r1);
        SDL_SetRenderDrawColor(ren,0x00,0xFF,0x00,0x00);
        SDL_RenderFillRect(ren,&r2);
        SDL_SetRenderDrawColor(ren,0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren,&r3);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        Uint32 tempo[3];
        int isevt = SDL_WaitEventTimeout(&evt,espera);
        if (isevt){
            espera -= (SDL_GetTicks()-antes);
            if (espera<0) { 
                espera = 0;
            }
            if(evt.type == SDL_KEYDOWN){
                if(fin[1]) continue;
                switch(evt.key.keysym.sym){
                    case SDLK_UP:
                    r2.x += 20;
                    break;
                    case SDLK_DOWN:
                    r2.x -= 20;
                    break;
                    case SDLK_LEFT:
                    r2.x -= 5;
                    break;
                    case SDLK_RIGHT:
                    r2.x += 5;
                    break;
                }
                if (SDL_HasIntersection(&r2,&line)){
                    fin[1] = true;
                    tempo[1] = SDL_GetTicks();
                }
            
            }
            else if (evt.type == SDL_QUIT){
                break;
            }
            else if (evt.type == SDL_MOUSEMOTION){
                if(fin[2]) continue;
                r3.x = evt.motion.x - (r3.h/2);
                if (SDL_HasIntersection(&r3,&line)){
                    fin[2] = true;
                    tempo[2] = SDL_GetTicks();
                }
            }

        }
        else {
            if(fin[0]) continue;
            espera = 10;
            r1.x += 4;
            if (SDL_HasIntersection(&r1,&line)){
                fin[0] = true;
                tempo[0] = SDL_GetTicks();
            }
        }
        
        /*DECLARANDO VENCEDOR*/
        if(fin[0] && fin[1] && fin[2]){
            if (tempo[0]<tempo[1] && tempo[0]<tempo[2]) winner = 0;
            else if (tempo[1]<tempo[2]&& tempo[1]<tempo[0]) winner = 1;
            else if (tempo[2]<tempo[0]&& tempo[2]<tempo[1]) winner = 2;
            SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
            SDL_RenderClear(ren);
            switch(winner){
                case 0:
                    r1 = (SDL_Rect) {270,270,60,60};
                    SDL_SetRenderDrawColor(ren,0xFF,0x00,0x00,0x00);
                    SDL_RenderFillRect(ren,&r1);   
                    clr = (SDL_Color) {0xFF,0x00,0x00,0xFF};
                    sfc = TTF_RenderText_Blended(fnt,"red",clr);
                    assert(sfc != NULL);
                    txt = SDL_CreateTextureFromSurface(ren, sfc);
                    assert(txt != NULL);
                    SDL_RenderCopy(ren,txt,NULL,&vencedor);
                    break;
                case 1:
                    r2 = (SDL_Rect) {270,270,60,60};
                    SDL_SetRenderDrawColor(ren,0x00,0xFF,0x00,0x00);
                    SDL_RenderFillRect(ren,&r2);  
                    clr = (SDL_Color) {0x00,0xFF,0x00,0xFF};
                    sfc = TTF_RenderText_Blended(fnt,"green",clr);
                    assert(sfc != NULL);
                    txt = SDL_CreateTextureFromSurface(ren, sfc);
                    assert(txt != NULL);
                    SDL_RenderCopy(ren,txt,NULL,&vencedor); 
                    break;
                case 2:
                    r3 = (SDL_Rect) {270,270,60,60};
                    SDL_SetRenderDrawColor(ren,0x00,0x00,0xFF,0x00);
                    SDL_RenderFillRect(ren,&r3);   
                    clr = (SDL_Color) {0x00,0x00,0xFF,0xFF};
                    sfc = TTF_RenderText_Blended(fnt,"blue",clr);
                    assert(sfc != NULL);
                    txt = SDL_CreateTextureFromSurface(ren, sfc);
                    assert(txt != NULL);
                    SDL_RenderCopy(ren,txt,NULL,&vencedor);
                    break;
            }
            SDL_Delay(30);
            SDL_RenderPresent(ren);
            while(1){
                SDL_WaitEvent(&evt);
                if (evt.type == SDL_KEYDOWN){
                    if (evt.key.keysym.sym == SDLK_SPACE){
                        r1 = (SDL_Rect) {40,20,25,25};
                        r2 = (SDL_Rect) {40,290,25,25};
                        r3 = (SDL_Rect) {40,555,25,25};
                        fin[0] = fin[1] = fin[2] = false;
                        break;
                    }
                }
                if(evt.type == SDL_QUIT){
                    goto exit;
                }
                
            }
        }


    }
    exit:

    /*FINALIZAÇÃO*/
    SDL_DestroyRenderer(ren);
    SDL_FreeSurface(sfc);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
