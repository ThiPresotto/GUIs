#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main (int argc, char* args[]){

    /*INICIALIZAÇÃO*/
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Tangram",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 400, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer (win, -1, 0 );


    /*EXECUÇÃO*/

    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 255);
    SDL_RenderClear(ren);

    roundedBoxRGBA (ren,
    130, 300,
    230, 400,
    0, 0xFF, 0x00, 0x00, 255);

    roundedBoxRGBA (ren,
    80, 350,
    130, 400,
    0, 0x00, 0xFF, 0x00, 255);

    //Trig atras
    filledTrigonRGBA(ren,
                     80, 350,   
                     130, 300,   
                     130, 350,  
                     0, 125, 0, 255); 

    //Trig topo
    filledTrigonRGBA(ren,
                     130, 300,   
                     230, 300,   
                     180, 250,  
                     0, 0, 125, 255);  

    //paralelogramo 1
    filledTrigonRGBA(ren,
                     230, 300,   
                     230, 350,   
                     280, 300,   
                     0, 125, 55, 255);  

    //paralelogramo 2
    filledTrigonRGBA(ren,
                     230, 300,   
                     280, 300,   
                     280, 250,   
                     0, 125, 55, 255);  

    filledTrigonRGBA(ren,
                     280, 300,   
                     280, 250,   
                     330, 250,  
                     255, 125, 0, 255);  

    SDL_RenderPresent(ren);
    SDL_Delay(3000);





    /*FINALIZAÇÃO*/
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

}


