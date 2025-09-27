#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    int isevt;
    isevt = SDL_WaitEventTimeout(evt,*ms);
    if (isevt){
        *ms -= SDL_GetTicks()-antes;
        if (*ms < 0){
            *ms = 0; //Assumindo que o tempo de espera seja definido fora desse escopo
        }
        return 1;
        
    }
    else {
        *ms = 0; //Assumindo que o tempo de espera seja definido fora desse escopo
        return 0;
    }
}

void teleport(SDL_Rect r, SDL_Rect* c, SDL_Rect cc, SDL_Texture* img, SDL_Renderer* ren,
                int mousex, int mousey){
    for(int i = 1;i<6;i++){
        cc = c[i]; 
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren,img,&cc,&r);
        SDL_RenderPresent(ren); 
        SDL_Delay(16);  
    } 
    r.x = mousex - (r.w/2);
    r.y = mousey - (r.h/2);

    for(int i = 5;i>0;i--){
        cc = c[i]; 
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren,img,&cc,&r);
        SDL_RenderPresent(ren); 
        SDL_Delay(32);  
    }   
    
}

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
    SDL_Texture* img  = IMG_LoadTexture(ren,"bubble2.png");
    assert(img !=NULL);

    /* EXECUÇÃO */
    enum state{
        PARADO,
        MOVENDO,
        POWER
    };

    srand(time(NULL));

    SDL_Rect r = { 170,167, 60,75 };
    SDL_Rect c[6] ={
        { 40, 50, 126, 310},
        {200, 50, 206, 310},
        {406, 50, 246, 310},
        {667, 50, 306, 310},
        {993, 50, 306, 310},
        {1329,50, 306,310}
};
    SDL_Rect cc = c[1];
    SDL_Event evt;
    Uint32 lastClick = 0;
    int clickCount = 0;
    int timeout = 250;
    enum state current_state = PARADO;
    int mousey;
    int mousex; 
    int safety_count = 0;
    
    while(1){
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren,img,&cc,&r);
        SDL_RenderPresent(ren);

        int toomuchpower = rand() % 9 - 4;

        
            if (AUX_WaitEventTimeoutCount(&evt,&timeout)){
                if (evt.type == SDL_QUIT){
                    break;
                }

                if (evt.type == SDL_MOUSEMOTION){
                    if (current_state == POWER){
                        r.x = evt.motion.x - (r.h/2)+5 + toomuchpower;
                        r.y = evt.motion.y - (r.w/2)-5 + toomuchpower;
                    }
                }

                if (evt.type == SDL_MOUSEBUTTONDOWN) {  
                    if(evt.button.button == SDL_BUTTON_LEFT){
                        mousex = evt.button.x;
                        mousey = evt.button.y; 
                        Uint32 current = SDL_GetTicks();             
                        if (current - lastClick < 250) {
                            if (clickCount < 3){
                                clickCount++;
                                lastClick = SDL_GetTicks();
                            }
                        } else {
                            clickCount = 1;
                            lastClick = SDL_GetTicks();
                        }
                    }
                    SDL_Event user_evt;
                    SDL_zero(user_evt);
                    user_evt.type = SDL_USEREVENT;
                    user_evt.user.code = clickCount;
                    SDL_PushEvent(&user_evt);
                }

                if (evt.type == SDL_USEREVENT){
                    switch(evt.user.code){
                        case 1:
                            current_state = MOVENDO;
                            r = (SDL_Rect) {r.x,r.y,60,75};
                            cc = c[1];
                            timeout = 80;
                            break;
                        case 2:
                            current_state = PARADO;
                            teleport(r,c,cc,img,ren,mousex,mousey);
                            r.x = mousex - (r.w/2);
                            r.y = mousey - (r.h/2);
                            r = (SDL_Rect) {r.x,r.y,60,75};
                            cc = c[1];
                            timeout = 250;
                            break;
                        case 3:
                        current_state = POWER;
                            r = (SDL_Rect) {r.x,r.y,30,45};
                            cc = c[0];
                            r.x = mousex - (r.h/2) + 5 + toomuchpower;
                            r.y = mousey - (r.w/2) - 5 + toomuchpower;
                            timeout = 250;
                            break;
                    }
                }

            }   

        if (current_state == MOVENDO){
            timeout = 80;
            safety_count++;
            if (r.x < mousex - (r.w/2)){
                r.x++;
            }
            else if(r.x>mousex - (r.w/2)){
                r.x--;
            }
            if (r.y <mousey - (r.h/2)){
                r.y++;
            }
            else if(r.y>mousey - (r.w/2)){
                r.y--;
            }
            if(((r.x == mousex - (r.w/2))&&(r.y==mousey - (r.h/2)))||safety_count >= 300){
                current_state = PARADO;
                safety_count = 0;
            }
            SDL_Delay(4);
        }
        
        
    }



    /* FINALIZACAO */
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

}
