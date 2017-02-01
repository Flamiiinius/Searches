Jogo dos 8

Rodrigo Flaminio Ribeiro e Ricardo Dias Azevedo


Disciplina: Inteligência Artificial



Compilar: g++ IA_Trabalho_1.cpp

executar: ./a.out

input: 
1- Uma matriz 3*3 (para a configuração de entrada) com os números de 0 a 8 sem repetições, os números podem estar separados por espaços e/ou parágrafos. O ‘0’ representa o espaço em branco.

2- Uma matriz 3*3 (para a configuração de final) com os números de 0 a 8 sem repetições, os números podem estar separados por espaços e/ou parágrafos. O ‘0’ representa o espaço em branco.

3- Se for possível de resolver, vai lhe ser apresentado outro menu, com os diferentes algoritmos de pesquisa, na pesquisa gulosa e A*, sera ainda dada a opção de escolher a heurística que quer usar.

4- Se a solução for encontrada c/ uma profundidade inferior a 100, sera dada a opção de escolher se quer uma visualização mais gráfica, com o “espaço em branco” a ser movido até encontrar a solução.

*Legenda: “U”-Cima, “D”-Baixo, “R”-Direita, “L”-Esquerda



ex: ps: nao colocar o que esta dentro dos ()

3 4 2

5 1 7

6 0 8

1 2 3

8 0 4

7 6 5

2  (BFS)

2 (não quer a visualização)



ex2:
3 4 2 
5 1 7 
6 0 8

1 2 3 
8 0 4
 7 6 5

5  (A*)
2  (heurística)

1  (1 se quiser a visualização)



