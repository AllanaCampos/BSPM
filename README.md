# BSPM
Este repositório contém 3 pastas que serão descritas a seguir.
## Pcode
O arquivo pcode.c contém o algoritmo em C da máquina virtual especificada por Nicklaus Wirth, que pode ser encontrada na linguagem pascal na [Wikipedia](https://en.wikipedia.org/wiki/P-code_machine). A máquina permite a execução de no máximo 50 instruções e contém 3 registradores:
- contador do programa: p;
- registrador de base: b;
- registrador de topo de pilha: t.

O conjunto de instruções de máquina possui 8 instruções:
1. lit 0, a: carrega uma constante a;
2. opr 0, a: executa a operação a;
3. lod l, a: carrega uma variável que se encontra no nível l na posição a;
4. sto l, a: armazena uma variável no nível l na posição a;
5. cal l, a: chama um processo que se encontra no nível l na posição a;
6. int 0, a: incrementa o registrador de topo de pilha por a;
7. jmp 0, a: pula para a posição a;
8. jpc 0, a: pula condicionalmente para a posição a.


As operações permitidas na instrução 2 são:
1. rtn: retorna a chamada anterior;
2. neg: calcula o negado do valor do topo da pilha;
3. add: soma os dois valores que se encontram no topo da pilha;
4. sub: subtrai o penultimo valor da pilha pelo topo da pilha;
5. mul: multiplica o penultimo valor da pilha pelo topo da pilha;
6. div: divide o penultimo valor da pilha pelo topo da pilha;
7. mod: calcula o módulo do penultimo valor da pilha pelo topo da pilha;
8. odd: verifica se a variável do topo da pilha é ímpar; 
9. eql: verifica se os dois valores que se encontram no topo da pilha são iguais;
10. neq: verifica se os dois valores que se encontram no topo da pilha não são iguais;
11. lss: verifica se o penultimo valor da pilha é menor que o valor do topo da pilha;
12. leq: verifica se o penultimo valor da pilha é menor ou igual ao valor do topo da pilha;
13. gtr: verifica se o penultimo valor da pilha é maior que ao valor do topo da pilha;
14. geq: verifica se o penultimo valor da pilha é maior ou igual ao valor do topo da pilha;

Nos demais arquivos da pasta além de conter o algoritmo da máquina virtual também encontram-se códigos armazenados na memória RAM que calculam alguns valores. Para cada arquivo será indicado sua funcionalidade nos pontos abaixo:
* pcode1p2m3.c -> calcula a multiplicação de dois valores e a adição de um terceiro valor a esse resultado, no caso esá calculando 2 * 3 + 1, tais valores podem ser modificados nas linhas 48, 50 e 56 alterando os números inseridos no code[x].a pelos valores desejados;
* pcode-fact5.c -> calcula o fatorial de 5;
* pcode-mult.c -> calcula a multiplicação de dois valores, no caso esá calculando 4 *7, tais valores podem ser modificados nas linhas 48  e 50 alterando os números inseridos no code[x].a pelos valores desejados;
* pcode-quad5pos.c -> calcula a soma do quadrado dos 5 primeiros numeros inteiros positivos;
* pcode-sum5pos.c -> calcula a soma dos 5 primeiros numeros inteiros positivos;
* pcode-fact3.c -> calcula o fatorial de  3.

## Brookshear
O arquivo brookshear.c contém o algoritmo em C descrito por Glenn Brookshear no apêndice C do livro ```Ciência da Computação: uma visão abrangente```. A máquina contém 16 registradores de 8 bits de comprimento, memória principal com 256 células e 12 instruções de máquina apresentadas a seguir:
1. LOAD RXY: carrega o registrador R com o padrão de bits encontrado na posição de memória de endereço XY;
2. LOAD RXY: carrega o registrador R com o padrão de bits XY;
3. STORE RXY: armazena o padrão de bits encontrado no registrador R na posição de memória de endereço XY;
4. MOVE 0RS: copia o padrão de bits encontrado no registrador R para o registrador S;
5. ADD RST: soma os padrões de bits dos registradores S e T, em complemento de dois, e armazena o resultado no registrador R;
6. ADD RST: soma os padrões de bits dos registradores S e T em notação de ponto flutuante e coloca o resultado em ponto flutuante no registrador R;
7. OR RST: executa a operação lógicar OR sobre os padrões de bits dos registradores S e T e coloca o resultado no registrador R;
8. AND RST: executa a operação lógicar AND sobre os padrões de bits dos registradores S e T e coloca o resultado no registrador R;
9. EXCLUSIVE OR RST: executa a operação lógicar EXCLUSIVE OR sobre os padrões de bits dos registradores S e T e coloca o resultado no registrador R;
10. ROTATE R0X: rotaciona o padrão de bits do registrador R, de X bits para a direita.
11. JUMP RXY: salta para a instrução localizada na posição de memória de endereço XY se o padrão de bits do registrador R coincidir com o padrão de bits do registrador 0.
12. HALT 000: para a execução.

Nos demais arquivos da pasta além de conter o algoritmo da máquina virtual também encontram-se códigos armazenados na memória RAM que calculam alguns valores. Para cada arquivo será indicado sua funcionalidade nos pontos abaixo:
- fatorial(3).c: calcula o fatorial de 3;
- soma5intpos.c: calcula a soma dos primeiros 5 inteiros positivos;
- soma-cubo-5intpos.c: calcula a soma do cubo dos 5 primeiros inteiros positivos;
- soma-quad-5intpos.c: calcula a soma do quadrado dos 5 primeiros inteiros positivos.

## BSPM
O arquivo BSPM.c contém o algoritmo de uma máquina virtual desenvolvida pelo autor sobre orientação do Prof. Dr. César Alberto Bravo Pariente, que engloba a arquitetura da máquina descrita por Brookshear e as instruções da máquina Pcode especificada por Nicklaus Wirth. As instruções implementadas da Pcode foram armazenadas na memória RAM da máquina, para isso foi necessário a expansão da memória RAM que passou de 256 células de 8 bits cada para 65536 células de 32 bits.

A máquina também apresenta um sistema de chamada e retorno de subrotina baseado na instância de registro de ativação descrito por Sebesta no livro ```Concepts of Programming Languages```. 

Para escrever um código aceito pela máquina deve-se armazenar todas as instruções na memória principal e começar utilizando as seguintes instruções:
```
    RAM[ 0x0] = 0x000200fa;           RAM[ 0x1] = 0x00000005;       //RAM[ 0x0]: LOAD  0a 02   // REG[0xfa] <- 5
    RAM[ 0x2] = 0x000200fb;           RAM[ 0x3] = 0xfffffffb;       //RAM[ 0x2]: LOAD  fb -5   // REG[0xfb] <- -5
    RAM[ 0x4] = 0x000200fe;           RAM[ 0x5] = 0x0000fc09;       //RAM[ 0x4]: LOAD  fe fc09 // REG[0xfe] <- 0xfc09 // posicao return
    RAM[ 0x6] = 0x000200f1;           RAM[ 0x7] = 0x0000fc0a;       //RAM[ 0x6]: LOAD  f1 fc0a // REG[0xf1] <- 0xfc0a // posicao param
    RAM[ 0x8] = 0x000200ff;           RAM[ 0x9] = 0x0000fc0b;       //RAM[ 0x8]: LOAD  ff fc0b // REG[0xff] <- 0xfc0b // posicao param
    RAM[ 0xa] = 0x000200fc;           RAM[ 0xb] = 0x0000fc0c;       //RAM[ 0xa]: LOAD  fc fc0c // REG[0xfc] <- 0xfc0c // posicao result
```
Tais instruções reservam as posições iniciais para o registro de instrução que armazena a posição de retorno da chamada, os parametros da função e o resultado da função; as primeiras duas instruções armazenam nos registradores ```fa``` e ```fb``` (em hexadecimal) os valores 5 e -5 que auxiliam na adição de um registro de ativação na pilha e na remoção de um registro de chamada da pilha.

Para fazer a chamada a alguma função que está armazenada na memória RAM deve-se adicionar as instruções abaixo:

```
    RAM[ 0xc] = 0x0002000f;           RAM[ 0xd] = 0x00000002;       //RAM[ 0xc]: LOAD  0f 02   // REG[0x0f] <- 0x0002 // Parametros
    RAM[ 0xe] = 0x0002000e;           RAM[ 0xf] = 0x00000001;       //RAM[ 0xe]: LOAD  0e 01   // REG[0x0e] <- 0x0001 // Parametros
    RAM[0x10] = 0x000200fd;           RAM[0x11] = 0x0000001a;       //RAM[0x10]: LOAD  fd 1a   // REG[0xfd] <- 0x001a // retorno da chamada FIBONACCI
    RAM[0x12] = 0x00020000;           RAM[0x13] = 0x00000018;       //RAM[0x12]: LOAD  00 18   // REG[0x00] <- 0x0018 // posicao de retorno da chamada LIT
    RAM[0x14] = 0x00030000;           RAM[0x15] = 0x0000fc07;       //RAM[0x14]: STORE 00 fc07 // RAM[0xfc07] <- REG[00] // salva retorno da chamada LIT
    RAM[0x16] = 0x000b0000;           RAM[0x17] = 0x0000fbea;       //RAM[0x16]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;} // LIT 
    RAM[0x18] = 0x000b0000;           RAM[0x19] = 0x0000001c;       //RAM[0x18]: JUMP  00 1c   // if (REG[0x00] == REG[0x00]) {p <- 0x001c;} // FIBONACCI
    RAM[0x1a] = 0x000c0000;           RAM[0x1b] = 0x00000000;       //RAM[0x1a]: HALT  00 00   // END
```
As duas primeiras instruções armazeram os parâmetros da função nos registradores ```f``` e ```e```.

As três instruções seguintes armazeram as posições de retorno da função a ser chamada e da função de adição do registro de ativação na pilha.

Logo após faz-se a chamada da função de adição do registro de ativação na pilha e a chamada da função desejada.

A ultima instrução é a de término do programa.

A máquina possui posições da memória e registradores reservados pela máquina, e são indicados abaixo:
* Posição ```eece``` até ```f001``` contém as instruções aritméticas e lógicas adaptadas da máquina Pcode;
* Posição ```fbcf``` até ```fc07``` contém as instruções para adição e deleção de registros de ativação na pilha;
* Posição ```fc08``` até ```fc4d``` contém os registros de ativação;
* Registradores ```0``` à ```4``` e registrador ```9``` são utilizados nas funções;
* Registradores ```f9``` à ```ff``` são utilizados para auxiliar na manipulação dos registros de ativação.

Para exemplificar o funcionamento da máquina no arquivo fibonacci-recursivo.c encontra-se um código que executa o algoritmo fibonnaci recursivamente, como entrada está salvo o valor 5, porém pode ser alterado na linha 33 (apenas altere o valor da variável ```a```).
