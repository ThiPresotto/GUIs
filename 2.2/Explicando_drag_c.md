O código possui 3 estados:
1) IDLE para quando não houver ação de mouse do quadrado
2) CLICADO para quando o mouse clicar na região do retângulo.
3) ARRASTANDO para quando o mouse não for liberado e seu movimento também arrastar o retângulo.

As cores servem para sinalizar o Estado do código:
1) Branco = IDLE, com a ação da tecla escape ou após arrastar o quadrado
2) Verde = IDLE, porém vindo de um mouseUP do estado CLICADO
3) Vermelho = CLICADO, representa o clique do quadrado
4) Azul = ARRASTANDO, representa a ação de drag.


O arrasto é calculado pelo ponto de origem em que o quadrado está, somado com a posição atual do mouse subtraído pelo ponto em que ocorre o clique.
