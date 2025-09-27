É um código simples seguindo a ideia da bolha. A bolha reage a eventos de clique.

1 clique  -> Ela se move até a região clicada pelo mouse.
2 cliques -> Ela se teletransporta com uma animação
3 cliques -> Ela segue o mouse 

O código se encontra com bugs...

Primeiro que no estado de 3 cliques era para em cada iteração
a imagem ser atualizada/tremer. Porém esse "tremido" apenas ocorre 
ao detectar a ação de movimento de mouse.

Mesmo problema pode ser encontrado na ação de 1 clique. O movimento
ocorre ao detectar movimento de mouse. 

Tentativas de corrigir estes problemas geraram outros bugs mais insatisfatórios,
por essa razão, essa é a versão oficial por hora.
