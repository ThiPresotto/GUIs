<h1>FUNCIONAMENTO</h1>

O código é similar ao funcionamento da atividade
1.3.1 com uma leve alteração.

```C
            else if(evt.type = SDL_KEYDOWN && lock == false){
                if(evt.key.keysym.sym == SDLK_SPACE){
                    lock = true;
                    direcao = (direcao+1)%4;
                }

            }
```

O código acima demonstra um evento acionado ao clicar a tecla ESPAÇO...

Neste evento a direção é alterada e uma trava é acionada (para evitar que 
o evento seja acionado mais de uma vez)

Após o retângulo colidir com a borda da tela, sua direção retorna à 
programação normal e a trava é liberada.

A intenção da mudança é fazer com que o retângulo atravesse/corte a tela
até alcançar a outra extremidade.
