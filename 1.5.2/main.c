#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    int isevt;
    isevt = SDL_WaitEventTimeout(&evt,*ms);
    if (isevt){
        if ((*ms -= SDL_GetTicks()-antes)<0){
            *ms = 0; //Altera ms e compara com 0  
        }
        return 1;
        
    }
    else {
        *ms = 0; //Assumi que o tempo de espera seja definido fora desse escopo
        return 0;
    }
}

