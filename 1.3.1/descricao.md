<h1>Funcionamento do código</h1>

O retângulo é redenrizado na posição do código "hello.c".

A cada ciclo ele se move dois pixels para uma de quatro direções,
iniciando o movimento para a direita.

Ao encostar em uma das bordas da tela, a variavel de direção é alterada 
para a próxima "seta" em sentido horário.

No final do ciclo há um "SDL_PollEvent" escolhido ao invés de
"SDL_WaitEvent", pois o segundo bloqueia o fluxo do código até o surgimento
de um evento, ao contrário do primeiro.

