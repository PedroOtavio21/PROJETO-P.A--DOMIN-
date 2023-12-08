# PROJETO-P.A--DOMIN-

NOTAS APÓS O TERMINO -

O jogo consegue iniciar normalmente, porém falta revisar algumas coisas, como peças irem para a mão do usuário de maneira correta, confirmar se a peça a ser jogada na mesa é possível 
ou não, controles de erro ( digitar uma letra ou numéro errado nas opções ), além de alterar a lógica de carregar ou salvar jogo ( não consigo carregar o jogo após uma nova 
compilação ) e confirmar empate ou jogador vencedor. 

PASSO A PASSO DO TRABALHO -

Inicialização do Jogo -

Criar um conjunto de 28 peças de dominó.
Embaralhar as peças.
Distribuir 7 peças para cada jogador.

Determinar o Jogador Inicial -

Verificar quem tem a dupla mais alta.
Em caso de empate, verificar a maior soma ou a peça de maior número.
O jogador vencedor começa.

Desenvolvimento do Turno -

Mostrar a mão do jogador atual.
Exibir as peças na mesa.
Informar a quantidade de peças na mão do adversário.
Mostrar a quantidade de peças disponíveis para compra.

Tomada de Decisões -

O jogador pode escolher entre jogar uma peça, comprar peças ou passar a vez.

Jogar uma Peça -

Permitir ao jogador escolher uma peça da mão que se conecte à mesa.
Atualizar o estado da mesa.

Comprar Peças -

Permitir ao jogador comprar peças até que seja possível jogar.
Atualizar a mão do jogador e as peças disponíveis.

Passar a Vez -

Se todas as peças da mesa estiverem esgotadas, o jogador passa a vez.

Salvar e Continuar o Jogo -

Oferecer a opção de salvar o estado do jogo em um arquivo externo.
Oferecer a opção de continuar um jogo salvo anteriormente.

Fim do Jogo -

Verificar se algum jogador venceu ou se o jogo está empatado.
