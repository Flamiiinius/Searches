Trabalho realizado no ambito da disciplina de Inteligencia Artificial, eu fiz o codigo e o meu colega o relat�rio.



Jogo dos 8

Rodrigo Flaminio Ribeiro e Ricardo Dias Azevedo


Disciplina: Intelig�ncia Artificial



Compilar: g++ IA_Trabalho_1.cpp

executar: ./a.out

input: 
1- Uma matriz 3*3 (para a configura��o de entrada) com os n�meros de 0 a 8 sem repeti��es, os n�meros podem estar separados por espa�os e/ou par�grafos. O �0� representa o espa�o em branco.

2- Uma matriz 3*3 (para a configura��o de final) com os n�meros de 0 a 8 sem repeti��es, os n�meros podem estar separados por espa�os e/ou par�grafos. O �0� representa o espa�o em branco.

3- Se for poss�vel de resolver, vai lhe ser apresentado outro menu, com os diferentes algoritmos de pesquisa, na pesquisa gulosa e A*, sera ainda dada a op��o de escolher a heur�stica que quer usar.

4- Se a solu��o for encontrada c/ uma profundidade inferior a 100, sera dada a op��o de escolher se quer uma visualiza��o mais gr�fica, com o �espa�o em branco� a ser movido at� encontrar a solu��o.

*Legenda: �U�-Cima, �D�-Baixo, �R�-Direita, �L�-Esquerda



ex: ps: nao colocar o que esta dentro dos ()

3 4 2

5 1 7

6 0 8

1 2 3

8 0 4

7 6 5

2  (BFS)

2 (n�o quer a visualiza��o)



ex2:
3 4 2 
5 1 7 
6 0 8

1 2 3 
8 0 4
 7 6 5

5  (A*)
2  (heur�stica)

1  (1 se quiser a visualiza��o)



