
/*
    Author: Gustavo B. Fragoso
    2021-10-26: Updated by Allana Campos passing as input fixed values for the factorial of 5
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_INSTRUCTIONS 50 // Define your own
#define STACKSIZE 1024

typedef struct{
    int f;
    int l;
    int a;
} Tinstruction;

int p;  			// Points to an i in the program area
int b;				// Points to the b address in the s for the current invocation of a given procedure
int t; 				// Points to the current t of the s
int totalInstrctns = 0;
Tinstruction i;
int s[STACKSIZE] = {-1};		// Vector with only integers, used as a datastore
int h;
// Array of instructions (Input)
Tinstruction code[MAX_INSTRUCTIONS]; 

// List of available instructions
enum { LIT, OPR, LOD, STO, CAL, INT, JMP, JPC } instructionCode;
char * instructionString[] = { "LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC"};

// List of available arithmetic operations
enum { RTN, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ } operationCode;
char * operationString[] = { "RTN", "NEG", "ADD", "SUB", "MUL", "DIV", "MOD", "ODD", "EQL", "NEQ", "LSS", "LEQ", "GTR", "GEQ"};

// Prototypes 
void executeInstruction();
void stackOperation(int a);
int base(int l);
int getInstructionCode(char *c);
char * getInstructionName(int inst);

int main (){
	int aa = 5;
	printf("start pl/0\n");
    	h = 0; 
    	t = -1; b = 0; p = 0; 
	code[ 0].f = 5;     code[ 0].l = 0;     code[ 0].a = 5;     //INT 0 5 // main
	code[ 1].f = 0;     code[ 1].l = 0;     code[ 1].a = aa;    //LIT 0 3
	code[ 2].f = 3;     code[ 2].l = 0;     code[ 2].a = 8;     //STO 0 8 // passagem de parametro do main para fatorial
	code[ 3].f = 4;     code[ 3].l = 0;     code[ 3].a = 7;     //CAL 0 7
	code[ 4].f = 2;     code[ 4].l = 0;     code[ 4].a = 4;     //LOD 0 4
	code[ 5].f = 3;     code[ 5].l = 0;     code[ 5].a = 3;     //STO 0 3
	code[ 6].f = 1;     code[ 6].l = 0;     code[ 6].a = 0;     //OPR 0 0 // retorno do main
	code[ 7].f = 5;     code[ 7].l = 0;     code[ 7].a = 5;     //INT 0 5 // factorial(3)
	code[ 8].f = 2;     code[ 8].l = 0;     code[ 8].a = 3;     //LOD 0 3
	code[ 9].f = 0;     code[ 9].l = 0;     code[ 9].a = 1;     //LIT 0 1
	code[10].f = 1;     code[10].l = 0;     code[10].a = 11;    //OPR 0 11 // OPR 0 >= 
	code[11].f = 7;     code[11].l = 0;     code[11].a = 15;    //JPC 0 15
	code[12].f = 0;     code[12].l = 0;     code[12].a = 1;     //LIT 0 1
	code[13].f = 3;     code[13].l = 1;     code[13].a = 4;     //STO 1 4
	code[14].f = 1;     code[14].l = 0;     code[14].a = 0;     //OPR 0 0 // retorno da chamada do fatorial
	code[15].f = 2;     code[15].l = 0;     code[15].a = 3;     //LOD 0 3
	code[16].f = 0;     code[16].l = 0;     code[16].a = 1;     //LIT 0 1
	code[17].f = 1;     code[17].l = 0;     code[17].a = 3;     //OPR 0 3 // OPR 0 SUB
	code[18].f = 3;     code[18].l = 0;     code[18].a = 8;     //STO 0 8 // passagem de parametro
	code[19].f = 4;     code[19].l = 0;     code[19].a = 7;     //CAL 0 7 // chamada recursiva
	code[20].f = 2;     code[20].l = 0;     code[20].a = 3;     //LOD 0 3
	code[21].f = 2;     code[21].l = 0;     code[21].a = 4;     //LOD 0 4
	code[22].f = 1;     code[22].l = 0;     code[22].a = 4;     //OPR 0 4
	code[23].f = 3;     code[23].l = 1;     code[23].a = 4;     //STO 1 4
	code[24].f = 1;     code[24].l = 0;     code[24].a = 0;     //OPR 0 0 // retorno da chamada do fatorial
	//END 0 0

    printf("%-5s %-5s %-5s %-5s %-5s","f","l","a","t","p");
    for(h = 0; h < code[0].a; h++) {
        printf("s[%d] " , h);
    }
    printf("\n");
    do {
		i = code[p];
		p++;
		switch (i.f) {
			// LIT, OPR, LOD, STO, CAL, INT, JMP, JPC
			// 0	1	 2	  3	   4	5	 6	  7	   
			case LIT:  t++; s[t] = i.a; break;
			case OPR:
				switch (i.a) { 
					// RTN, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ
					// 0	1	 2	  3	   4	5	 6	  7    8	9	 10	  11   12	13
					case RTN: t = b - 1; p = s[t+3]; b = s[t+2]; break;
					case NEG: s[t]= -s[t]; break;
					case ADD: t--; s[t] += s[t+1]; break;
					case SUB: t--; s[t] -= s[t+1]; break;
					case MUL: t--; s[t] *= s[t+1]; break;
					case DIV: t--; s[t] /= s[t+1]; break;
					case MOD: t--; s[t] %= s[t+1]; break;
					case ODD: s[t] = (s[t]%2 == 1); break;
					case EQL: t--; s[t] = (s[t] == s[t+1]); break;
					case NEQ: t--; s[t] = (s[t] != s[t+1]); break;
					case LSS: t--; s[t] = (s[t] < s[t+1]); break;
					case LEQ: t--; s[t] = (s[t] <= s[t+1]); break;
					case GTR: t--; s[t] = (s[t] > s[t+1]); break;
					case GEQ: t--; s[t] = (s[t] >= s[t+1]); break;
					}
				break;
			case LOD: t++; s[t] = s[ base(i.l) + i.a ]; break;
			case STO: s[ base(i.l) + i.a ] = s[t]; t--; break;
			case CAL: s[t+1] = base( i.l ); s[t+2] = b; s[t+3] = p; b = t+1; p = i.a; break;
			case INT: t += i.a; break;
			case JMP: p = i.a-1; break; //CHECAR
			case JPC: if ( s[t] == 0 ) { p = i.a-1; } t--; break; //CHECAR
		}
			
		// PrintStackTrace
		printf("%-5s %-5d %-5d %-5d %-5d", getInstructionName(i.f), i.l, i.a, s[t], p);

		for (h = 0; h < t+1; h++){
			printf("%-5d", s[h]);
		}
		printf("\n");
    } while (p != 0);
    printf("--- --- --- --- --- ---");
    for(h = 0; h <22; h++) {
        printf(" ---");
    }
    printf("\n");
    printf("%3s %3s %3s %3s %3s %3s","f","l","a","p","b","t");
    for(h = 0; h <22; h++) {
        printf(" %3d" , h);
    }
    printf("\nend pl/0                stack\n");
    return 0;
}


int base(int l){
    int newBase;
	newBase = b;
	while (l>0){
		newBase = s[newBase];
		l--;
	}
	return newBase;
}

char * getInstructionName(int inst){
	return instructionString[inst];
}
