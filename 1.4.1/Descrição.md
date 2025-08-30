<h1>As mudanças geradas no código...</h1>

if (evt.type == SDL_QUIT){            
break;
}

Reporta eventos de saída, tal como apertar no 
botão de fechar janela. Entrando na condicional
saímos do loop while(1) e o programa executa as
linhas de finalização.

------------------------------------------------------------------------------------

case SDLK_LEFT:
r.x -= 5;
if (r.x<0) r.x = 0;
break;

Nos eventos de teclado, para cada cenário das setas UP,DOWN,LEFT,RIGHT, 
foi adicionado uma condicional para verificar se o retângulo não saíra de tela.
Esse comando está imperfeito, pois apenas funciona nas dimensões em que a janela
abriu e não calcula qualquer alteração em seu tamanho.

---------------------------------------------------------------------------------

void mousefunc(int count,SDL_Rect rect[],SDL_Renderer* ren){
    for(int i=0;i<count;i++){
        SDL_SetRenderDrawColor(ren, ((i*30)+100)%256,((i*30)+255)%256,((i*15)+200)%256,0xFF);  
        SDL_RenderFillRect(ren,&rect[i]);
    }
    return;
}

A função acima é exectuda antes da troca de buffers. Ela define uma cor baseada 
na iteração do loop for e em sequência gera o retângulo baseado nas informações capturadas
no evento de clicar o mouse (posição x e y do mouse). As informações são armazenadas em um
array de SDL_Rect de tamanho 10.
