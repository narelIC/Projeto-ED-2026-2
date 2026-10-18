# Projeto Estrutura de Dados | 2026.2

O trabalho consiste na construção e apresentação dos algoritmos de Árvore B, Dijkstra, SAT Solver e Huffman, para a composição de uma das notas do semestre, na disciplina de Estrutura de Dados do curso de Graduação em Engenharia da Computação  -Instituo de Computação(UFAL).

<p align="center">
  <img src="https://user-images.githubusercontent.com/91018438/204195385-acc6fcd4-05a7-4f25-87d1-cb7d5cc5c852.png" alt="animated" />
</p>

<center>
Equipe:

  Narel Oliveira | Laryssa Calazans | Rafael Antonio | Murilo Santos

 </center>

## O que é a Árvore B?

A Árvore B é uma árvore de busca balanceada em que cada nó pode guardar várias chaves em ordem e ter vários filhos. Com isso a profundidade é bastante reduzida,como  cada nó guarda muitas chaves a árvore fica baixa, o que reduz a quantidade de acessos em uma busca. Por isso ela é usada em bancos de dados e sistemas de arquivos.

## O que é Algoritmo de Djkistra?

Algoritmo de Dijkstra encontra a menor distância de um vértice de origem até todos os outros vértices de um grafo ponderado. Muito utilizado no roteamento de pacotes de internet, mas principalmente conhecido pela implementação dem GPS e softwares de navegação como Waze e Google Maps.

## O que é o SAT Solver?

Um SAT solver é um programa que resolve o Problema da Satisfatibilidade Booleana (SAT): dada uma fórmula lógica, ele descobre se existe uma combinação de valores verdadeiro (1) e falso (0) para as variáveis que torna a fórmula inteira verdadeira. Se existir, a fórmula é SAT (satisfazível) e o programa mostra essa combinação; se não existir, a fórmula é UNSAT (insatisfazível).

## O que é o Algoritmo de HUFFMAN?

O algoritmo de Huffman é uma técnica de compressão de dados sem perda que cria códigos binários de comprimento variável com base na frequência dos símbolos presentes em um conjunto de dados. O objetivo é representar os símbolos mais frequentes com códigos mais curtos e os símbolos menos frequentes com códigos mais longos, reduzindo, assim, o tamanho total do arquivo.

## Instalação dos programas com cmd

<p>

> Clone esse projeto em seu computador com o comando:
>
> ```
> 	git clone https://github.com/narelIC/Projeto-ED-2026-2.git 
> ```
>
> Acesse o diretório do projeto seu terminal.
> Para a Árvore B e Dijkstra:
> ```
> 	cd Projeto-ED-2026-2\Seminário
> ```
>
> Para o SAT Solver:
> ```
> 	cd Projeto-ED-2026-2\SAT solver
> ```
>
> Para o Algoritmo de Huffman:
> ```
> 	cd Projeto-ED-2026-2\huffman
> ```
>
> Já no diretório da aplicação em seu terminal, digite os comandos de compilação.
>   Para a Árvore B:
>
> ```
> 	  gcc arvoreB.c -o arvoreB.exe
> ```
>
>   Para o Dijkstra:
>
> ```
> 	  gcc dijkstra.c -o dijkstra.exe
> ```
>
>   Para o SAT Solver:
>
> ```
> 	  gcc sat.c -o sat.exe
> ```
>
>   Para o Huffman:
>
> ```
> 	  gcc -Iinc src/arvore.c src/compressao.c src/descompressao.c src/lista.c src/main.c -o projeto_huffman.exe
> ```
>
> Logo depois, basta executar com o seguinte comando:
>
> ```
>   arvoreB.exe OU dijkstra.exe OU sat.exe OU huffman.exe
> ```

  </p>

## Menu do programa do Huffman

<p> Ao inicializar o programa, você terá direito de escolha de 2 opções:
  
* Compactar um arquivo
* Descompactar o arquivo

# Obrigado!
