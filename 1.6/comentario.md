Atualização nova: Foi adicionado o texto para anunciar o vencedor.


Situação goto

Normalmente quando há um (evt.type == SDL_QUIT) opto por apenas utilizar o
comando "break;" para sair do loop principal.

No caso, ao anunciar o vencedor, um segundo loop "while" é criado. Assim sendo,
a linha de código "break" irá sair apenas do loop secundário. O que poderia fazer
para fixar esse erro era criar uma variável bool, e ao apertar "quit", alteramos seu
valor e fazemos um break

(evt.type == SDL_QUIT){
  sair = true; //while no loop principal será afetado por essa mudança
  break;

Porém, essa mudança me obriga criar uma nova variável. Por conta disso, o goto faz
um jump que automaticamente irá levar o programa às linhas de FINALIZAÇÃO...
