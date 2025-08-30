#include <SDL2/SDL.h>

SDL_Rect rects[10];

void mousefunc(int count,SDL_Rect rect[],SDL_Renderer* ren);

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    int count = 0;
    int mouseX,mouseY;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        mousefunc(count,rects,ren);
        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 5;
                    if (r.y<0) r.y = 0;
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    if (r.y>90) r.y = 90;
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    if (r.x<0) r.x = 0;
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    if (r.x>190) r.x = 190;
                    break;
            }
        }
        if (evt.type == SDL_QUIT){
            break;
        }
        if (evt.type == SDL_MOUSEBUTTONDOWN){
            if (count<10){
                rects[count].x=evt.button.x;
                rects[count].y=evt.button.y;
                rects[count].w=10;
                rects[count].h=10;
                count+=1;
            }
            
        }

    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void mousefunc(int count,SDL_Rect rect[],SDL_Renderer* ren){
    for(int i=0;i<count;i++){
        SDL_SetRenderDrawColor(ren, ((i*30)+100)%256,((i*30)+255)%256,((i*15)+200)%256,0xFF);  
        SDL_RenderFillRect(ren,&rect[i]);
    }
    return;
}
