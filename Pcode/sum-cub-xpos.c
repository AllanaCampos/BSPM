/*
    Author: Gustavo B. Fragoso
    2021-10-26: Updated by Allana Campos passing as input fixed values for the sum of the first five integer values
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
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
void sum(int aa);
int main(){
    FILE *times;
    times = fopen("seconds.txt", "w");
    int aa = 2;
    time_t t_ini, t_fim;
    float trec = 0;
    while(aa < 257){
        t_ini = time(NULL); 
        sum(aa);
        t_fim = time(NULL);
        trec = difftime(t_fim, t_ini);
        fprintf(times, "%d\t%f\n", aa, trec );
        aa*=2;
    }
    fflush(times);
    fclose(times);
    return 0;
}
void sum (int aa){
	printf("start pl/0              stack\n");
    // Parametros
    h = 0; 
    t = -1; b = 0; p = 0; 
    code[ 0].f = 5;     code[ 0].l = 0;     code[ 0].a = 5;     //INT 0 5 // main
	code[ 1].f = 0;     code[ 1].l = 0;     code[ 1].a = 1;     //LIT 0 1
	code[ 2].f = 3;     code[ 2].l = 0;     code[ 2].a = 3;     //STO 0 3 
	code[ 3].f = 0;     code[ 3].l = 0;     code[ 3].a = 1;     //LIT 0 1
	code[ 4].f = 3;     code[ 4].l = 0;     code[ 4].a = 4;     //STO 0 4
	code[ 5].f = 2;     code[ 5].l = 0;     code[ 5].a = 3;     //LOD 0 3
	code[ 6].f = 0;     code[ 6].l = 0;     code[ 6].a = aa;    //LIT 0 3
	code[ 7].f = 1;     code[ 7].l = 0;     code[ 7].a = 13;    //OPR 0 13 // OPR 0 >= 
	code[ 8].f = 7;     code[ 8].l = 0;     code[ 8].a = 10;    //JPC 0 10
	code[ 9].f = 1;     code[ 9].l = 0;     code[ 9].a = 0;     //OPR 0 0 
	code[10].f = 2;     code[10].l = 0;     code[10].a = 3;     //LOD 0 3
	code[11].f = 0;     code[11].l = 0;     code[11].a = 1;     //LIT 0 1
	code[12].f = 1;     code[12].l = 0;     code[12].a = 2;     //OPR 0 2 // OPR 0 ADD
	code[13].f = 3;     code[13].l = 0;     code[13].a = 3;     //STO 0 3
	code[14].f = 2;     code[14].l = 0;     code[14].a = 3;     //LOD 0 3
	code[15].f = 2;     code[15].l = 0;     code[15].a = 3;     //LOD 0 3
	code[16].f = 1;     code[16].l = 0;     code[16].a = 4;     //OPR 0 4 // OPR 0 MUL
	code[17].f = 2;     code[17].l = 0;     code[17].a = 3;     //LOD 0 3
	code[18].f = 1;     code[18].l = 0;     code[18].a = 4;     //OPR 0 4 // OPR 0 MUL
	code[19].f = 2;     code[19].l = 0;     code[19].a = 4;     //LOD 0 4
	code[20].f = 1;     code[20].l = 0;     code[20].a = 2;     //OPR 0 2 // OPR 0 ADD
	code[21].f = 3;     code[21].l = 0;     code[21].a = 4;     //STO 0 4
	code[22].f = 6;     code[22].l = 0;     code[22].a = 5;     //JMP 0 5
	code[23].f = 1;     code[23].l = 0;     code[23].a = 0;     //OPR 0 0 
	//END 0 0

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



