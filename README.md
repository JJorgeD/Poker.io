🃏 Jogo de Poker em C
Disciplina: Algoritmos e Estruturas de Dados
Colaboradores: Jorge Dias e Miguel Arcanjo

📌 Sobre o Projeto
Este projeto apresenta um jogo de Poker Texas Hold'em simplificado, desenvolvido inteiramente na linguagem C, com execução via terminal. O jogo foi projetado para aplicar os principais conceitos estudados na disciplina de Algoritmos e Estruturas de Dados, como uso de estruturas, modularização, vetores, controle de fluxo, ponteiros e lógica condicional.

🧠 Como o Jogo Funciona
O jogo é para dois jogadores: o usuário (jogador humano) e um bot.

Cada jogador recebe duas cartas.

O jogo sorteia cinco cartas comunitárias, sendo:

3 no flop

1 no turn

1 no river

Antes da abertura das cartas da mesa, há uma rodada de apostas, onde o jogador pode:

Pagar (call) a aposta atual

Aumentar (raise) a aposta

Desistir (fold) da rodada

O bot responde automaticamente com base em uma lógica de IA simulada.

O jogo compara as cartas da mão e da mesa e determina o vencedor.

O vencedor recebe o valor acumulado no pot (apostas).

✅ Funcionalidades Implementadas
Baralho completo com 52 cartas

Embaralhamento aleatório

Distribuição de cartas para os jogadores

Rodada única de apostas

Cartas comunitárias: flop, turn e river

Sistema de apostas com fichas e pot acumulado

Ações do jogador: call, raise, fold

Comportamento do bot com decisão baseada em lógica de IA

Avaliação automática das mãos:

Carta mais alta (High Card)

Um Par

Dois Pares

Trinca (Three of a Kind)

Determinação do vencedor e atualização das fichas

Interface via terminal com feedback textual claro

⚙️ Como Compilar e Executar
Requisitos:
Compilador C (como gcc)

Terminal (Linux, WSL, ou ambiente compatível como MinGW no Windows)

Compilação:
Execute no terminal dentro da pasta do projeto:
make
Isso irá compilar todos os arquivos e gerar o executável poker.
Execução:
./poker
📁 Estrutura do Projeto
main.c – Função principal e fluxo do jogo

deck.c / deck.h – Lógica de criação e embaralhamento do baralho

player.c / player.h – Estrutura e ações dos jogadores

game.c / game.h – Cartas da mesa, pot e controle da rodada

evaluate.c / evaluate.h – Avaliação das mãos (quem ganha)

betting.c / betting.h – Lógica de apostas e decisões

ia_api.c / ia_api.h – Simulação de uma API de IA para decisões do bot

Makefile – Compilação automatizada

🎓 Objetivos Acadêmicos
Este projeto teve como propósito:

Aplicar de forma prática as estruturas de dados estudadas em aula

Desenvolver lógica de jogo usando programação em C

Utilizar modularização, ponteiros e arrays de forma eficiente

Simular uma aplicação com integração de múltiplos módulos

Demonstrar compreensão de tomada de decisão e estruturas condicionais

Realizar uma simulação interativa, controlada por entrada do usuário e lógica automatizada (IA)
