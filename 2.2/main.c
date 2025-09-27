#include <SDL2/SDL.h>
#include <stdbool.h>

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


int main (int argc, char* args){
    
    
    //INICIALIZAÇÃO
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 400, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win,-1,0);


    //EXECUÇÃO
    enum state{
        IDLE,
        CLICADO,
        ARRASTANDO
    };

    int timeout = 250;

    SDL_Rect r = {400/2-40/2,400/2-40/2,40,40};
    SDL_Point p;
    SDL_Rect origin;
    SDL_Color cor= {0xFF,0xFF,0xFF,0xFF};

    SDL_Event evt;
    enum state current_state = IDLE;

    while(1){

        SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0xFF);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(ren,&r);
        SDL_RenderPresent(ren);



        bool isevt = AUX_WaitEventTimeoutCount(&evt,&timeout);
        if(isevt){
            if (evt.type == SDL_QUIT){
                    break;
                }

            switch(current_state){
                
                case IDLE:
                if(evt.type == SDL_MOUSEBUTTONDOWN){
                    p.x = evt.button.x;
                    p.y = evt.button.y;
                    if (SDL_PointInRect(&p,&r)){
                        current_state = CLICADO;
                        origin = r;
                        cor = (SDL_Color) {0xFF,0x00,0x00,0x00};
                    }
                }
                break;
                
                case CLICADO:
                if(evt.type == SDL_KEYDOWN){
                    if(evt.key.keysym.sym == SDLK_ESCAPE){
                        r = origin;
                        current_state = IDLE;
                        cor = (SDL_Color) {0xFF,0xFF,0xFF,0x00};
                    }
                }
                else if(evt.type == SDL_MOUSEBUTTONUP){
                    current_state = IDLE;
                    cor = (SDL_Color) {0x00,0xFF,0x00,0x00};
                }
                else if(evt.type == SDL_MOUSEMOTION){
                    current_state = ARRASTANDO;
                    cor = (SDL_Color) {0x00,0x00,0xFF,0x00};
                }
                break;
                
                case ARRASTANDO:
                if(evt.type == SDL_KEYDOWN){
                    if(evt.key.keysym.sym == SDLK_ESCAPE){
                        r = origin;
                        current_state = IDLE;
                        cor = (SDL_Color) {0xFF,0xFF,0xFF,0x00};
                    }
                }
                else if(evt.type == SDL_MOUSEBUTTONUP){
                    current_state = IDLE;
                    cor = (SDL_Color) {0xFF,0xFF,0xFF,0x00};
                }
                else if(evt.type == SDL_MOUSEMOTION){
                    r.x = origin.x + evt.motion.x-p.x;
                    r.y = origin.y + evt.motion.y-p.y;
                    cor = (SDL_Color) {0x00,0x00,0xFF,0x00};
                }
                

                break;



            }
        }
    
    
    }
    
    //FINALIZANDO
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
