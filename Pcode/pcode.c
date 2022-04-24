
/*
    Author: Gustavo B. Fragoso
    2021-10-26: Updated by Allana Campos 
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
int s[STACKSIZE] = {};		// Vector with only integers, used as a datastore
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
int main(){
	int aa = 5;
	printf("start pl/0              stack\n");
    	h = 0; 
    	t = -1; b = 0; p = 0; 
    	

    printf("%3s %3s %3s %3s %3s %3s","f","l","a","p","b","t");
    for(h = 0; h <22; h++) {
        printf(" %3d" , h);
    }
    printf("\n");
    printf("--- --- --- --- --- ---");
    for(h = 0; h <22; h++) {
        printf(" ---");
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
					case 0: t = b - 1; p = s[t+3]; b = s[t+2]; break;
					case 1: s[t]= -s[t]; break;
					case 2: t--; s[t] += s[t+1]; break;
					case 3: t--; s[t] -= s[t+1]; break;
					case 4: t--; s[t] *= s[t+1]; break;
					case 5: t--; s[t] /= s[t+1]; break;
					case 6: t--; s[t] %= s[t+1]; break;
					case 7: s[t] = (s[t]%2 == 1); break;
					case 8: t--; s[t] = (s[t] == s[t+1]); break;
					case 9: t--; s[t] = (s[t] != s[t+1]); break;
					case 10: t--; s[t] = (s[t] < s[t+1]); break;
					case 11: t--; s[t] = (s[t] <= s[t+1]); break;
					case 12: t--; s[t] = (s[t] > s[t+1]); break;
					case 13: t--; s[t] = (s[t] >= s[t+1]); break;
					}
				break;
			case LOD: t++; s[t] = s[ base(i.l) + i.a ]; break;
			case STO: s[ base(i.l) + i.a ] = s[t]; t--; break;
			case CAL: s[t+1] = base( i.l ); s[t+2] = b; s[t+3] = p; b = t+1; p = i.a; break;
			case INT: t += i.a; break;
			case JMP: p = i.a; break; 
			case JPC: if ( s[t] == 0 ) { p = i.a; } t--; break; 
		}
		
		printf("%3s %3d %3d %3d %3d %3d ", getInstructionName(i.f), i.l, i.a, p, b, t);

		for (h = 0; h < t+1; h++){
			printf(" %3d", s[h]);
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
