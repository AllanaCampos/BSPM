// Example program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>
#include<math.h>
#include<time.h>

typedef struct{     
    uint64_t op;        // operacao
    uint64_t opr1;      // operando1
    uint64_t opr2;      // operando2
    uint64_t opr3;      // operando3
} Tinstruction;     



// List of available instructions
char * instructionString[] = { "LOAD", "LOAD", "STORE", "MOVE", "ADD", "ADD", "OR", "AND", "EXCLS", "ROTAT", "JUMP", "HALT", "NEG", "MULT"};

// Prototypes 
char * getInstructionName(uint64_t inst);
uint64_t sum_comp2(uint64_t val1, uint64_t val2);
uint64_t sum_flut(uint64_t val1, uint64_t val2);
uint64_t rot(uint64_t val1, uint64_t val2);
uint64_t trans(uint64_t val1, uint64_t val2);
uint64_t neg(uint64_t val1);
uint64_t mult(uint64_t val1, uint64_t val2);
uint64_t divide(uint64_t val1, uint64_t val2);
uint64_t mod(uint64_t val1, uint64_t val2);
void fact(uint64_t val1);
Tinstruction transformInstruction(uint64_t a, uint64_t b);

int main(){
    FILE *times;
    times = fopen("seconds.txt", "w");
    uint64_t f = 2;
    clock_t t_ini, t_fim;
    float trec = 0;
    while(f < 20){
        t_ini = clock();
        fact(f);
        t_fim = clock();
        trec = t_fim - t_ini;
        fprintf(times, "%d\t%f\n", f, (trec/CLOCKS_PER_SEC));
        f += 1;
    }
    printf("%d", f);
    fflush(times);
    fclose(times);
    return 0;
}

void fact(uint64_t a){
    //uint64_t a = 0x00000005;
    uint64_t RAM[65536]; // ffff
    uint64_t reg[65536]; // registradores
    Tinstruction i;
    printf("start                   \n");
    // Parametros
    
    //operador&operando1        operando2&operando3
    
    RAM[ 0x0] = 0x00000002000000fa;           RAM[ 0x1] = 0x0000000000000005;       //RAM[ 0x0]: LOAD  0a 02   // REG[0xfa] <- 5
    RAM[ 0x2] = 0x00000002000000fb;           RAM[ 0x3] = 0xfffffffffffffffb;       //RAM[ 0x2]: LOAD  fb -5   // REG[0xfb] <- -5
    RAM[ 0x4] = 0x00000002000000fe;           RAM[ 0x5] = 0x000000000000fc09;       //RAM[ 0x4]: LOAD  fe fc09 // REG[0xfe] <- 0xfc09 // posicao return
    RAM[ 0x6] = 0x00000002000000f1;           RAM[ 0x7] = 0x000000000000fc0a;       //RAM[ 0x6]: LOAD  f1 fc0a // REG[0xf1] <- 0xfc0a // posicao param
    RAM[ 0x8] = 0x00000002000000ff;           RAM[ 0x9] = 0x000000000000fc0b;       //RAM[ 0x8]: LOAD  ff fc0b // REG[0xff] <- 0xfc0b // posicao param
    RAM[ 0xa] = 0x00000002000000fc;           RAM[ 0xb] = 0x000000000000fc0c;       //RAM[ 0xa]: LOAD  fc fc0c // REG[0xfc] <- 0xfc0c // posicao result
    RAM[ 0xc] = 0x000000020000000f;           RAM[ 0xd] = a;                //RAM[ 0xc]: LOAD  0f a    // REG[0x0f] <- a      // Parametros
    RAM[ 0xe] = 0x000000020000000e;           RAM[ 0xf] = 0x0000000000000001;       //RAM[ 0xe]: LOAD  0e 01   // REG[0x0e] <- 0x0001 // Parametros
    RAM[0x10] = 0x00000002000000fd;           RAM[0x11] = 0x000000000000001a;       //RAM[0x10]: LOAD  fd 1a   // REG[0xfd] <- 0x001a // retorno da chamada FIBONACCI
    RAM[0x12] = 0x0000000200000000;           RAM[0x13] = 0x0000000000000018;       //RAM[0x12]: LOAD  00 18   // REG[0x00] <- 0x0018 // posicao de retorno da chamada LIT
    RAM[0x14] = 0x0000000300000000;           RAM[0x15] = 0x000000000000fc07;       //RAM[0x14]: STORE 00 fc07 // RAM[0xfc07] <- REG[00] // salva retorno da chamada LIT
    RAM[0x16] = 0x0000000b00000000;           RAM[0x17] = 0x000000000000fbea;       //RAM[0x16]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;} // LIT 
    RAM[0x18] = 0x0000000b00000000;           RAM[0x19] = 0x000000000000001c;       //RAM[0x18]: JUMP  00 1c   // if (REG[0x00] == REG[0x00]) {p <- 0x001c;} // FIBONACCI
    RAM[0x1a] = 0x0000000c00000000;           RAM[0x1b] = 0x0000000000000000;       //RAM[0x1a]: HALT  00 00   // END

    
    //FATORIAL
    RAM[0x1c] = 0x0000000200000001;           RAM[0x1d] = 0xffffffffffffffff;       //RAM[0xee90]: LOAD  01 -1    // REG[0x01] <- -1
    RAM[0x1e] = 0x000000020000000e;           RAM[0x1f] = 0x0000000000000001;       //RAM[0xee92]: LOAD  0e 01    // REG[0x0e] <- 01
    RAM[0x20] = 0x0000000200000000;           RAM[0x21] = 0x0000000000000028;       //RAM[0xee94]: LOAD  00 28    // REG[0x00] <- 28
    RAM[0x22] = 0x0000000300000000;           RAM[0x23] = 0x000000000000fc07;       //RAM[0xee96]: STORE 00 fc07  // RAM[0xfc07] <- REG[0x00]
    RAM[0x24] = 0x00000002000000fd;           RAM[0x25] = 0x000000000000002a;       //RAM[0xee98]: LOAD  fd 2a    // REG[0xfd] <- 2a
    RAM[0x26] = 0x0000000b00000000;           RAM[0x27] = 0x000000000000fbea;       //RAM[0xee9a]: JUMP  00 fbea  // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;} // LIT
    RAM[0x28] = 0x0000000b00000000;           RAM[0x29] = 0x000000000000eece;       //RAM[0xee9c]: JUMP  00 eece  // if (REG[0x00] == REG[0x00]) {p <- 0xeece;} // GEQ
    RAM[0x2a] = 0x0000000200000000;           RAM[0x2b] = 0x0000000000000000;       //RAM[0xee9e]: LOAD  00 00    // REG[0x00] <- 00
    RAM[0x2c] = 0x0000000b00000004;           RAM[0x2d] = 0x0000000000000032;       //RAM[0xeea0]: JUMP  04 38    // if (REG[0x00] == REG[0x04]) {p <- 0x38;}
    RAM[0x2e] = 0x0000000200000004;           RAM[0x2f] = 0x0000000000000001;       //RAM[0xeea2]: LOAD  04 01    // REG[0x04] <- 01
    RAM[0x30] = 0x0000000b00000000;           RAM[0x31] = 0x000000000000fbd2;       //RAM[0xeeaa]: JUMP  00 fbd2  // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0x32] = 0x000000050000000f;           RAM[0x33] = 0x0000000f00000001;       //RAM[0xeeac]: ADD   0f f1    // REG[0x0f] <- REG[0x0f] + REG[0x01] 
    RAM[0x34] = 0x0000000200000000;           RAM[0x35] = 0x000000000000003c;       //RAM[0xeeae]: LOAD  00 3c    // REG[0x00] <- 3c
    RAM[0x36] = 0x0000000300000000;           RAM[0x37] = 0x000000000000fc07;       //RAM[0xeeb0]: STORE 00 fc07  // RAM[0xfc07] <- REG[0x00]
    RAM[0x38] = 0x00000002000000fd;           RAM[0x39] = 0x000000000000003e;       //RAM[0xeeb2]: LOAD  fd 3e    // REG[0xfd] <- 3e
    RAM[0x3a] = 0x0000000b00000000;           RAM[0x3b] = 0x000000000000fbea;       //RAM[0xeeb4]: JUMP  00 fbea  // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;} // LIT
    RAM[0x3c] = 0x0000000b00000000;           RAM[0x3d] = 0x000000000000001c;       //RAM[0xeeb6]: JUMP  00 1c    // if (REG[0x00] == REG[0x00]) {p <- 0xee90;} // FATORIAL
    RAM[0x3e] = 0x0000000400000000;           RAM[0x3f] = 0x000000040000000e;       //RAM[0xeeb8]: MOVE  00 4e    // REG[0x0e] <- REG[0x04] 
    RAM[0x40] = 0x0000000200000003;           RAM[0x41] = 0x0000000000000001;       //RAM[0xeeb8]: LOAD  03 01    // REG[0x03] <- 01
    RAM[0x42] = 0x000000050000000f;           RAM[0x43] = 0x0000000f00000003;       //RAM[0xeeb8]: ADD   0f f3    // REG[0x0f] <- REG[0x0f] + REG[0x03] 
    RAM[0x44] = 0x0000000200000000;           RAM[0x45] = 0x000000000000004c;       //RAM[0xeeba]: LOAD  00 4c    // REG[0x00] <- 4c
    RAM[0x46] = 0x0000000300000000;           RAM[0x47] = 0x000000000000fc07;
    RAM[0x48] = 0x00000002000000fd;           RAM[0x49] = 0x000000000000004e;       //RAM[0xeebe]: LOAD  fd 4e    // REG[0xfd] <- 4e
    RAM[0x4a] = 0x0000000b00000000;           RAM[0x4b] = 0x000000000000fbea;       //RAM[0xeec0]: JUMP  00 fbea  // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;} // LIT
    RAM[0x4c] = 0x0000000b00000000;           RAM[0x4d] = 0x000000000000ef8e;       //RAM[0xeec2]: JUMP  00 1c    // if (REG[0x00] == REG[0x00]) {p <- 0xef8e;} // MULT
    RAM[0x4e] = 0x0000000b00000000;           RAM[0x4f] = 0x000000000000fbd2;       //RAM[0xeec8]: JUMP  00 fbd2  // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;} // RET

    //GEQ
    RAM[0xeece] = 0x0000000200000000;           RAM[0xeecf] = 0x000000000000eed6;       //RAM[0xeece]: LOAD  00 eed6 // REG[0x00] <- eed6
    RAM[0xeed0] = 0x0000000300000000;           RAM[0xeed1] = 0x000000000000fc07;       //RAM[0xeed0]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xeed2] = 0x00000002000000fd;           RAM[0xeed3] = 0x000000000000eed8;       //RAM[0xeed2]: LOAD  fd eed8 // REG[0xfd] <- eed8
    RAM[0xeed4] = 0x0000000b00000000;           RAM[0xeed5] = 0x000000000000fbea;       //RAM[0xeed4]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xeed6] = 0x0000000b00000000;           RAM[0xeed7] = 0x000000000000efd8;       //RAM[0xeed6]: JUMP  00 efd8 // if (REG[0x00] == REG[0x00]) {p <- 0xefd8;} // GTR
    RAM[0xeed8] = 0x0000000200000000;           RAM[0xeed9] = 0x0000000000000001;       //RAM[0xeed8]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xeeda] = 0x0000000b00000004;           RAM[0xeedb] = 0x000000000000eeee;       //RAM[0xeeda]: JUMP  04 eeee // if (REG[0x00] == REG[0x04]) {p <- 0xeeee;}
    RAM[0xeedc] = 0x0000000200000000;           RAM[0xeedd] = 0x000000000000eee4;       //RAM[0xeedc]: LOAD  00 eee4 // REG[0x00] <- eee4
    RAM[0xeede] = 0x0000000300000000;           RAM[0xeedf] = 0x000000000000fc07;       //RAM[0xeede]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xeee0] = 0x00000002000000fd;           RAM[0xeee1] = 0x000000000000eee6;       //RAM[0xeee0]: LOAD  fd eee6 // RAM[0xfd] <- REG[0xeee6]
    RAM[0xeee2] = 0x0000000b00000000;           RAM[0xeee3] = 0x000000000000fbea;       //RAM[0xeee2]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xeee4] = 0x0000000b00000000;           RAM[0xeee5] = 0x000000000000ef70;       //RAM[0xeee4]: JUMP  00 ef70 // if (REG[0x00] == REG[0x00]) {p <- 0xef70;} // EQL
    RAM[0xeee6] = 0x0000000200000000;           RAM[0xeee7] = 0x0000000000000001;       //RAM[0xeee6]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xeee8] = 0x0000000b00000004;           RAM[0xeee9] = 0x000000000000eeee;       //RAM[0xeee8]: JUMP  04 eeee // if (REG[0x00] == REG[0x04]) {p <- 0xeeee;}
    RAM[0xeeea] = 0x0000000200000004;           RAM[0xeeeb] = 0x0000000000000000;       //RAM[0xeeea]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xeeec] = 0x0000000b00000000;           RAM[0xeeed] = 0x000000000000fbd2;       //RAM[0xeeec]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xeeee] = 0x0000000200000004;           RAM[0xeeef] = 0x0000000000000001;       //RAM[0xeeee]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xeef0] = 0x0000000b00000000;           RAM[0xeef1] = 0x000000000000fbd2;       //RAM[0xeef0]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}

    //LEQ
    RAM[0xeef2] = 0x0000000200000000;           RAM[0xeef3] = 0x000000000000eefa;       //RAM[0xeef2]: LOAD  00 eefa // REG[0x00] <- eefa
    RAM[0xeef4] = 0x0000000300000000;           RAM[0xeef5] = 0x000000000000fc07;       //RAM[0xeef4]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xeef6] = 0x00000002000000fd;           RAM[0xeef7] = 0x000000000000eefc;       //RAM[0xeef6]: LOAD  fd eefc // REG[0xfd] <- eefc
    RAM[0xeef8] = 0x0000000b00000000;           RAM[0xeef9] = 0x000000000000fbea;       //RAM[0xeef8]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xeefa] = 0x0000000b00000000;           RAM[0xeefb] = 0x000000000000efd8;       //RAM[0xeefa]: JUMP  00 efd8 // if (REG[0x00] == REG[0x00]) {p <- 0xefd8;} // GTR
    RAM[0xeefc] = 0x0000000200000000;           RAM[0xeefd] = 0x0000000000000000;       //RAM[0xeefc]: LOAD  00 00   // REG[0x00] <- 00
    RAM[0xeefe] = 0x0000000b00000004;           RAM[0xeeff] = 0x000000000000ef12;       //RAM[0xeefe]: JUMP  04 ef12 // if (REG[0x00] == REG[0x04]) {p <- 0xef12;}
    RAM[0xef00] = 0x0000000200000000;           RAM[0xef01] = 0x000000000000ef08;       //RAM[0xef00]: LOAD  00 ef08 // REG[0x00] <- ef08
    RAM[0xef02] = 0x0000000300000000;           RAM[0xef03] = 0x000000000000fc07;       //RAM[0xef02]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef04] = 0x00000002000000fd;           RAM[0xef05] = 0x000000000000ef0a;       //RAM[0xef04]: LOAD  fd ef0a // REG[0xfd] <- ef0a
    RAM[0xef06] = 0x0000000b00000000;           RAM[0xef07] = 0x000000000000fbea;       //RAM[0xef06]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef08] = 0x0000000b00000000;           RAM[0xef09] = 0x000000000000ef70;       //RAM[0xef08]: JUMP  00 ef70 // if (REG[0x00] == REG[0x00]) {p <- 0xef70;} // EQL
    RAM[0xef0a] = 0x0000000200000000;           RAM[0xef0b] = 0x0000000000000001;       //RAM[0xef0a]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xef0c] = 0x0000000b00000004;           RAM[0xef0d] = 0x000000000000ef12;       //RAM[0xef0c]: JUMP  04 ef12 // if (REG[0x00] == REG[0x04]) {p <- 0xef12;}
    RAM[0xef0e] = 0x0000000200000004;           RAM[0xef0f] = 0x0000000000000000;       //RAM[0xef0e]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef10] = 0x0000000b00000000;           RAM[0xef11] = 0x000000000000fbd2;       //RAM[0xef10]: JUMP  00 fdb2 // if (REG[0x00] == REG[0x00]) {p <- 0xfdb2;}
    RAM[0xef12] = 0x0000000200000004;           RAM[0xef13] = 0x0000000000000001;       //RAM[0xef12]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef14] = 0x0000000b00000000;           RAM[0xef15] = 0x000000000000fbd2;       //RAM[0xef14]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    
    //LSS
    RAM[0xef16] = 0x0000000200000000;           RAM[0xef17] = 0x000000000000ef1e;       //RAM[0xef16]: LOAD  00 ef1e // REG[0x00] <- 0xef1e
    RAM[0xef18] = 0x0000000300000000;           RAM[0xef19] = 0x000000000000fc07;       //RAM[0xef18]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef1a] = 0x00000002000000fd;           RAM[0xef1b] = 0x000000000000ef20;       //RAM[0xef1a]: LOAD  fd ef20 // REG[0xfd] <- ef20
    RAM[0xef1c] = 0x0000000b00000000;           RAM[0xef1d] = 0x000000000000fbea;       //RAM[0xef1c]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef1e] = 0x0000000b00000000;           RAM[0xef1f] = 0x000000000000eece;       //RAM[0xef1e]: JUMP  00 eece // if (REG[0x00] == REG[0x00]) {p <- 0xeece;} // GEQ
    RAM[0xef20] = 0x0000000200000000;           RAM[0xef21] = 0x0000000000000000;       //RAM[0xef20]: LOAD  00 00   // REG[0x00] <- 00
    RAM[0xef22] = 0x0000000b00000004;           RAM[0xef23] = 0x000000000000ef28;       //RAM[0xef22]: JUMP  04 ef28 // if (REG[0x00] == REG[0x04]) {p <- 0xef28;}
    RAM[0xef24] = 0x0000000200000004;           RAM[0xef25] = 0x0000000000000000;       //RAM[0xef24]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef26] = 0x0000000b00000000;           RAM[0xef27] = 0x000000000000fbd2;       //RAM[0xef26]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xef28] = 0x0000000200000004;           RAM[0xef29] = 0x0000000000000001;       //RAM[0xef28]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef2a] = 0x0000000b00000000;           RAM[0xef2b] = 0x000000000000fbd2;       //RAM[0xef2a]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    

    //MOD
    RAM[0xef2c] = 0x000000030000000f;          RAM[0xef2d] = 0x000000000000fbd0;       //RAM[0xef2c]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef2e] = 0x000000010000000c;          RAM[0xef2f] = 0x000000000000fbd0;       //RAM[0xef2e]: LOAD  0c fbd0 // REG[0x0c] <- RAM[0xf6]
    RAM[0xef30] = 0x0000000200000000;          RAM[0xef31] = 0x000000000000ef38;       //RAM[0xef30]: LOAD  00 ef38 // REG[0x00] <- ef38
    RAM[0xef32] = 0x0000000300000000;          RAM[0xef33] = 0x000000000000fc07;       //RAM[0xef32]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef34] = 0x00000002000000fd;          RAM[0xef35] = 0x000000000000ef3a;       //RAM[0xef34]: LOAD  fd ef3a // REG[0xfd] <- ef3a
    RAM[0xef36] = 0x0000000b00000000;          RAM[0xef37] = 0x000000000000fbea;       //RAM[0xef36]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef38] = 0x0000000b00000000;          RAM[0xef39] = 0x000000000000efa6;       //RAM[0xef38]: JUMP  00 efa6 // if (REG[0x00] == REG[0x00]) {p <- 0xefa6;} // DIV
    RAM[0xef3a] = 0x000000030000000c;          RAM[0xef3b] = 0x000000000000fbd0;       //RAM[0xef3a]: STORE 0c fbd0 // RAM[0xf6] <- REG[0x0c]
    RAM[0xef3c] = 0x000000010000000f;          RAM[0xef3d] = 0x000000000000fbd0;       //RAM[0xef3c]: LOAD  0f fbd0 // REG[0x0f] <- RAM[0xf6]
    RAM[0xef3e] = 0x000000030000000e;          RAM[0xef3f] = 0x000000000000fbcf;       //RAM[0xef3e]: STORE 0e fbcf // RAM[0xf5] <- REG[0x0e]
    RAM[0xef40] = 0x0000000300000004;          RAM[0xef41] = 0x000000000000fbd1;       //RAM[0xef40]: STORE 04 fbd1 // RAM[0xf7] <- REG[0x04]
    RAM[0xef42] = 0x000000010000000e;          RAM[0xef43] = 0x000000000000fbd1;       //RAM[0xef42]: LOAD  0e fbd1 // REG[0x0e] <- RAM[0xf7]
    RAM[0xef44] = 0x0000000200000000;          RAM[0xef45] = 0x000000000000ef4c;       //RAM[0xef44]: LOAD  00 ef4c // REG[0x00] <- ef4c
    RAM[0xef46] = 0x0000000300000000;          RAM[0xef47] = 0x000000000000fc07;       //RAM[0xef46]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef48] = 0x00000002000000fd;          RAM[0xef49] = 0x000000000000ef4e;       //RAM[0xef48]: LOAD  fd ef4e // REG[0xfd] <- ef4e
    RAM[0xef4a] = 0x0000000b00000000;          RAM[0xef4b] = 0x000000000000fbea;       //RAM[0xef4a]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef4c] = 0x0000000b00000000;          RAM[0xef4d] = 0x000000000000ef8e;       //RAM[0xef4c]: JUMP  00 ef8e // if (REG[0x00] == REG[0x00]) {p <- 0xef8e;} // MULT
    RAM[0xef4e] = 0x0000000300000004;          RAM[0xef4f] = 0x000000000000fbd1;       //RAM[0xef4e]: STORE 04 fbd1 // RAM[0xf7] <- REG[0x04]
    RAM[0xef50] = 0x000000010000000f;          RAM[0xef51] = 0x000000000000fbd1;       //RAM[0xef50]: LOAD  0f fbd1 // REG[0x0f] <- RAM[0xf7]
    RAM[0xef52] = 0x0000000200000000;          RAM[0xef53] = 0x000000000000ef5a;       //RAM[0xef52]: LOAD  00 ef5a // REG[0x00] <- ef5a
    RAM[0xef54] = 0x0000000300000000;          RAM[0xef55] = 0x000000000000fc07;       //RAM[0xef54]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef56] = 0x00000002000000fd;          RAM[0xef57] = 0x000000000000ef5c;       //RAM[0xef56]: LOAD  fd ef5c // REG[0xfd] <- ef5c
    RAM[0xef58] = 0x0000000b00000000;          RAM[0xef59] = 0x000000000000fbea;       //RAM[0xef58]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef5a] = 0x0000000b00000000;          RAM[0xef5b] = 0x000000000000ef84;       //RAM[0xef5a]: JUMP  00 ef84 // if (REG[0x00] == REG[0x00]) {p <- 0xef84;} // NEG
    RAM[0xef5c] = 0x000000010000000f;          RAM[0xef5d] = 0x000000000000fbcf;       //RAM[0xef5c]: LOAD  0f fbcf // REG[0x0f] <- RAM[0xf5]
    RAM[0xef5e] = 0x0000000500000004;          RAM[0xef5f] = 0x0000000f00000004;       //RAM[0xef5e]: ADD   04 f4   // REG[0x04] <- REG[0x0f] + REG[0x04]
    RAM[0xef60] = 0x0000000b00000000;          RAM[0xef61] = 0x000000000000fbd2;       //RAM[0xef60]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x0f]) {p <- 0xfbd2;}
    
    //NEQ
    RAM[0xef62] = 0x000000030000000f;           RAM[0xef63] = 0x000000000000fbd0;      //RAM[0xef62]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef64] = 0x0000000100000000;           RAM[0xef65] = 0x000000000000fbd0;      //RAM[0xef64]: LOAD  00 fbd0 // REG[0x00] <- RAM[0xf6]
    RAM[0xef66] = 0x0000000b0000000e;           RAM[0xef67] = 0x000000000000ef68;      //RAM[0xef66]: JUMP  0e ef68 // if (REG[0x00] == REG[0x0e]) {p <- 0xef68;}
    RAM[0xef68] = 0x0000000200000004;           RAM[0xef69] = 0x0000000000000001;      //RAM[0xef68]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef6a] = 0x0000000b00000000;           RAM[0xef6b] = 0x000000000000fbd2;      //RAM[0xef6a]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xef6c] = 0x0000000200000004;           RAM[0xef6d] = 0x0000000000000000;      //RAM[0xef6c]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef6e] = 0x0000000b00000000;           RAM[0xef6f] = 0x000000000000fbd2;      //RAM[0xef6e]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    
    //EQL
    RAM[0xef70] = 0x000000030000000f;           RAM[0xef71] = 0x000000000000fbd0;      //RAM[0xef70]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef72] = 0x0000000100000000;           RAM[0xef73] = 0x000000000000fbd0;      //RAM[0xef72]: LOAD  00 fbd0 // REG[0x00] <- RAM[0xf6]
    RAM[0xef74] = 0x0000000b0000000e;           RAM[0xef75] = 0x000000000000ef7a;      //RAM[0xef74]: JUMP  0e ef7a // if (REG[0x00] == REG[0x0e]) {p <- 0xef7a;}
    RAM[0xef76] = 0x0000000200000004;           RAM[0xef77] = 0x0000000000000000;      //RAM[0xef76]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef78] = 0x0000000b00000000;           RAM[0xef79] = 0x000000000000fbd2;      //RAM[0xef78]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xef7a] = 0x0000000200000004;           RAM[0xef7b] = 0x0000000000000001;      //RAM[0xef7a]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef7c] = 0x0000000b00000000;           RAM[0xef7d] = 0x000000000000fbd2;      //RAM[0xef7c]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}

    //ODD
    RAM[0xef7e] = 0x000000020000000e;          RAM[0xef7f] = 0x0000000000000001;       //RAM[0xef7e]: LOAD  0e 01   // REG[0x0e] <- 01
    RAM[0xef80] = 0x0000000800000004;          RAM[0xef81] = 0x0000000e0000000f;       //RAM[0xef80]: AND   04 ef   // REG[0x04] <- REG[0x0e] && REG[0x0f]
    RAM[0xef82] = 0x0000000b00000000;          RAM[0xef83] = 0x000000000000fbd2;       //RAM[0xef82]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    
    //NEG
    RAM[0xef84] = 0x000000020000000e;          RAM[0xef85] = 0x0000000000000001;       //RAM[0xef84]: LOAD  0e 01   // REG[0x0e] <- 01
    RAM[0xef86] = 0x0000000200000002;          RAM[0xef87] = 0xffffffffffffffff;       //RAM[0xef86]: LOAD  02 -1   // REG[0x02] <- -1
    RAM[0xef88] = 0x0000000900000004;          RAM[0xef89] = 0x000000020000000f;       //RAM[0xef88]: XOR   04 2f   // REG[0x04] <- REG[0x02] XOR REG[0x0f]
    RAM[0xef8a] = 0x0000000500000004;          RAM[0xef8b] = 0x000000040000000e;       //RAM[0xef8a]: ADD   04 4e   // REG[0x04] <- REG[0x04] + REG[0x0e]
    RAM[0xef8c] = 0x0000000b00000000;          RAM[0xef8d] = 0x000000000000fbd2;       //RAM[0xef8c]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x0f]) {p <- 0xfbd2;}
    
    //MULT
    RAM[0xef8e] = 0x000000030000000f;          RAM[0xef8f] = 0x000000000000fbd1;       //RAM[0xef8e]: STORE 0f fbd1 // RAM[0xf7] <- REG[0x0f]
    RAM[0xef90] = 0x000000030000000e;          RAM[0xef91] = 0x000000000000fbd0;       //RAM[0xef90]: STORE 0e fbd0 // RAM[0xf6] <- REG[0x0e]
    RAM[0xef92] = 0x0000000200000002;          RAM[0xef93] = 0x0000000000000001;       //RAM[0xef92]: LOAD  02 01   // REG[0x02] <- 01
    RAM[0xef94] = 0x0000000200000003;          RAM[0xef95] = 0x0000000000000001;       //RAM[0xef94]: LOAD  03 01   // REG[0x03] <- 01
    RAM[0xef96] = 0x0000000100000004;          RAM[0xef97] = 0x000000000000fbd0;       //RAM[0xef96]: LOAD  04 fbd0 // REG[0x04] <- RAM[0xf6]
    RAM[0xef98] = 0x0000000100000000;          RAM[0xef99] = 0x000000000000fbd1;       //RAM[0xef98]: LOAD  00 fbd1 // REG[0x00] <- RAM[0xf7]
    RAM[0xef9a] = 0x0000000100000001;          RAM[0xef9b] = 0x000000000000fbd0;       //RAM[0xef9a]: LOAD  01 fbd0 // REG[0x01] <- RAM[0xf6]
    RAM[0xef9c] = 0x0000000b00000002;          RAM[0xef9d] = 0x000000000000fbd2;       //RAM[0xef9c]: JUMP  02 fbd2 // if (REG[0x00] == REG[0x02]) {p <- 0xfbd2;}
    RAM[0xef9e] = 0x0000000500000004;          RAM[0xef9f] = 0x0000000400000001;       //RAM[0xef9e]: ADD   04 41   // REG[0x04] <- REG[0x04] + REG[0x01]
    RAM[0xefa0] = 0x0000000500000002;          RAM[0xefa1] = 0x0000000200000003;       //RAM[0xefa0]: ADD   02 23   // REG[0x02] <- REG[0x02] + REG[0x03]
    RAM[0xefa2] = 0x0000000200000000;          RAM[0xefa3] = 0x0000000000000001;       //RAM[0xefa2]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xefa4] = 0x0000000b00000003;          RAM[0xefa5] = 0x000000000000ef98;       //RAM[0xefa4]: JUMP  03 ef98 // if (REG[0x00] == REG[0x03]) {p <- 0xef98;}

    //DIV
    RAM[0xefa6] = 0x000000030000000f;          RAM[0xefa7] = 0x000000000000fbd0;       //RAM[0xefa6]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xefa8] = 0x000000030000000e;          RAM[0xefa9] = 0x000000000000fbd1;       //RAM[0xefa8]: STORE 0e fbd1 // RAM[0xf7] <- REG[0x0e]
    RAM[0xefaa] = 0x0000000200000001;          RAM[0xefab] = 0x0000000000000001;       //RAM[0xefaa]: LOAD  01 01   // REG[0x01] <- 01
    RAM[0xefac] = 0x0000000200000003;          RAM[0xefad] = 0x0000000000000001;       //RAM[0xefac]: LOAD  03 01   // REG[0x03] <- 01
    RAM[0xefae] = 0x0000000100000002;          RAM[0xefaf] = 0x000000000000fbd0;       //RAM[0xefae]: LOAD  02 fbd0 // REG[0x02] <- RAM[0xf6]
    RAM[0xefb0] = 0x000000050000000f;          RAM[0xefb1] = 0x0000000f00000002;       //RAM[0xefb0]: ADD   0f f2   // REG[0x0f] <- REG[0x0f] + REG[0x02] 
    RAM[0xefb2] = 0x0000000200000000;          RAM[0xefb3] = 0x000000000000efba;       //RAM[0xefb2]: LOAD  00 efba // REG[0x00] <- efba
    RAM[0xefb4] = 0x0000000300000000;          RAM[0xefb5] = 0x000000000000fc07;       //RAM[0xefb4]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xefb6] = 0x00000002000000fd;          RAM[0xefb7] = 0x000000000000efbc;       //RAM[0xefb6]: LOAD  fd efbc // REG[0xfd] <- efbc
    RAM[0xefb8] = 0x0000000b00000000;          RAM[0xefb9] = 0x000000000000fbea;       //RAM[0xefb8]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    
    RAM[0xefba] = 0x0000000b00000000;          RAM[0xefbb] = 0x000000000000efd8;       //RAM[0xefba]: JUMP  00 efd8 // if (REG[0x00] == REG[0x00]) {p <- 0xefd8;} // GTR
    RAM[0xefbc] = 0x0000000200000000;          RAM[0xefbd] = 0x0000000000000000;       //RAM[0xefbc]: LOAD  00 00   // REG[0x00] <- 00
    RAM[0xefbe] = 0x0000000b00000004;          RAM[0xefbf] = 0x000000000000efc4;       //RAM[0xefbe]: JUMP  04 efc4 // if (REG[0x00] == REG[0x04]) {p <- 0xefc4;}
    RAM[0xefc0] = 0x0000000500000003;          RAM[0xefc1] = 0x0000000300000001;       //RAM[0xefc0]: ADD   03 31   // REG[0x03] <- REG[0x03] + REG[0x01] 
    RAM[0xefc2] = 0x0000000b00000000;          RAM[0xefc3] = 0x000000000000efae;       //RAM[0xefc2]: JUMP  00 efae // if (REG[0x00] == REG[0x00]) {p <- 0xefa2;}
    RAM[0xefc4] = 0x0000000100000000;          RAM[0xefc5] = 0x000000000000fbd1;       //RAM[0xefc4]: LOAD  00 fbd1 // REG[0x00] <- RAM[0xf7]
    RAM[0xefc6] = 0x0000000b0000000f;          RAM[0xefc7] = 0x000000000000efce;       //RAM[0xefc6]: JUMP  0f efce // if (REG[0x00] == REG[0x0f]) {p <- 0xefce;}
    RAM[0xefc8] = 0x0000000300000003;          RAM[0xefc9] = 0x000000000000fbd1;       //RAM[0xefc8]: STORE 03 fbd1 // RAM[0xf7] <- REG[0x03]
    RAM[0xefca] = 0x0000000100000004;          RAM[0xefcb] = 0x000000000000fbd1;       //RAM[0xefca]: LOAD  04 fbd1 // REG[0x04] <- RAM[0xf7]
    RAM[0xefcc] = 0x0000000b00000000;          RAM[0xefcd] = 0x000000000000fbd2;       //RAM[0xefcc]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xefce] = 0x0000000500000003;          RAM[0xefcf] = 0x0000000300000001;       //RAM[0xefce]: ADD   03 31   // REG[0x03] <- REG[0x03] + REG[0x01] 
    RAM[0xefd0] = 0x0000000300000003;          RAM[0xefd1] = 0x000000000000fbd1;       //RAM[0xefd0]: STORE 03 fbd1 // RAM[0xf7] <- REG[0x03]
    RAM[0xefd2] = 0x0000000100000004;          RAM[0xefd3] = 0x000000000000fbd1;       //RAM[0xefd2]: LOAD  04 fbd1 // REG[0x04] <- RAM[0xf7]
    RAM[0xefd4] = 0x0000000b00000000;          RAM[0xefd5] = 0x000000000000fbd2;       //RAM[0xefd4]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x0f]) {p <- 0xfbd2;}


    //GTR
    RAM[0xefd8] = 0x000000030000000f;          RAM[0xefd9] = 0x000000000000fbcf;       //RAM[0xefd8]: STORE 0f fbcf // RAM[0xf5] <- REG[0x0f]
    RAM[0xefda] = 0x0000000100000000;          RAM[0xefdb] = 0x000000000000fbcf;       //RAM[0xefda]: LOAD  00 fbcf // REG[0x00] <- RAM[0xf5]
    RAM[0xefdc] = 0x000000030000000e;          RAM[0xefdd] = 0x000000000000fbd1;       //RAM[0xefdc]: STORE 0e fbd1 // RAM[0xf7] <- REG[0x0e]
    RAM[0xefde] = 0x0000000b0000000e;          RAM[0xefdf] = 0x000000000000effa;       //RAM[0xefde]: JUMP  0e effa // if (REG[0x00] == REG[0x0e]) {p <- 0xeffa;}
    RAM[0xefe0] = 0x0000000200000000;          RAM[0xefe1] = 0x0000000000000001;       //RAM[0xefe0]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xefe2] = 0x0000000a0000000f;          RAM[0xefe3] = 0x0000000f0000001f;       //RAM[0xefe2]: ROT   0f 0f1f // REG[0x0f] <- REG[0x0f] >> 1f 
    RAM[0xefe4] = 0x0000000a0000000e;          RAM[0xefe5] = 0x0000000e0000001f;       //RAM[0xefe4]: ROT   0e 0e1f // REG[0x0e] <- REG[0x0e] >> 1f 
    RAM[0xefe6] = 0x0000000800000002;          RAM[0xefe7] = 0x000000000000000f;       //RAM[0xefe6]: AND   02 0f   // REG[0x02] <- REG[0x00] && REG[0x0f]
    RAM[0xefe8] = 0x0000000800000004;          RAM[0xefe9] = 0x000000000000000e;       //RAM[0xefe8]: AND   04 0e   // REG[0x04] <- REG[0x00] && REG[0x0e]
    RAM[0xefea] = 0x000000090000000d;          RAM[0xefeb] = 0x0000000200000004;       //RAM[0xefea]: XOR   0d 24   // REG[0x0d] <- REG[0x02] XOR REG[0x04]
    
    RAM[0xefec] = 0x0000000b0000000d;          RAM[0xefed] = 0x000000000000eff0;       //RAM[0xefec]: JUMP  0d eff0 // if (REG[0x00] == REG[0x02]) {p <- 0xeff0;}
    RAM[0xefee] = 0x0000000b00000000;          RAM[0xefef] = 0x000000000000efe2;       //RAM[0xefee]: JUMP  00 efe2 // if (REG[0x00] == REG[0x00]) {p <- 0xefe2;}
    RAM[0xeff0] = 0x0000000b00000002;          RAM[0xeff1] = 0x000000000000effa;       //RAM[0xeff0]: JUMP  02 efea // if (REG[0x00] == REG[0x02]) {p <- 0xefea;}
    RAM[0xeff2] = 0x0000000200000004;          RAM[0xeff3] = 0x0000000000000001;       //RAM[0xeff2]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xeff4] = 0x000000010000000f;          RAM[0xeff5] = 0x000000000000fbcf;       //RAM[0xeff4]: LOAD  0f fbcf // REG[0x0f] <- RAM[0xf5]
    RAM[0xeff6] = 0x000000010000000e;          RAM[0xeff7] = 0x000000000000fbd1;       //RAM[0xeff6]: LOAD  0e fbd1 // REG[0x0e] <- RAM[0xf7]
    RAM[0xeff8] = 0x0000000b00000000;          RAM[0xeff9] = 0x000000000000fbd2;       //RAM[0xeff8]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xeffa] = 0x0000000200000004;          RAM[0xeffb] = 0x0000000000000000;       //RAM[0xeffa]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xeffc] = 0x000000010000000f;          RAM[0xeffd] = 0x000000000000fbcf;       //RAM[0xeffc]: LOAD  0f fbcf // REG[0x0f] <- RAM[0xf5]
    RAM[0xeffe] = 0x000000010000000e;          RAM[0xefff] = 0x000000000000fbd1;       //RAM[0xeffe]: LOAD  0e fbd1 // REG[0x0e] <- RAM[0xf7]
    RAM[0xf000] = 0x0000000b00000000;          RAM[0xf001] = 0x000000000000fbd2;       //RAM[0xf000]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    
    //ff = registrador de topo da pilha
    //fe = registrador para base da pilha
    //fd = registrador para retorno
    //fb = registrador para incremento do topo e base
    //fa = registrador para decremento do topo e base
    //f9 = registrador para jump
    //fc = registrador de resultado
    
    //RET
    RAM[0xfbd2] = 0x0000000200000000;          RAM[0xfbd3] = 0xffffffffffffffff;       // RAM[0xfbd2]: LOAD  00 -1   // REG[0x00] <- -1
    RAM[0xfbd4] = 0x0000000500000000;          RAM[0xfbd5] = 0x000000fe00000000;       // RAM[0xfbd4]: ADD   00 fe00 // REG[0x00] <- REG[0xfe] + REG[0x00]
    RAM[0xfbd6] = 0x0000000300000000;          RAM[0xfbd7] = 0x000000000000fbe9;       // RAM[0xfbd6]: STORE 00 fbe9 // RAM[0xfbe9] <- REG[0x00]
    RAM[0xfbd8] = 0x00000003000000ff;          RAM[0xfbd9] = 0x000000000000fbdb;       // RAM[0xfbd8]: STORE ff fbdb // RAM[0xfbdb] <- REG[0xff]
    RAM[0xfbda] = 0x000000010000000f;                                                   // RAM[0xfbda]: LOAD  0f      // REG[0x0f] <- RAM[]
    RAM[0xfbdc] = 0x00000003000000fc;          RAM[0xfbdd] = 0x000000000000fbdf;       // RAM[0xfbdc]: STORE fc fbdf // RAM[0xfbdf] <- REG[0xfc]
    RAM[0xfbde] = 0x0000000300000004;                                                   // RAM[0xfbde]: STORE 04      // RAM[] <- REG[0x04]
    RAM[0xfbe0] = 0x00000005000000fe;          RAM[0xfbe1] = 0x000000fe000000fb;       // RAM[0xfbe0]: ADD   fe fefb // REG[0xfe] <- REG[0xfe] + REG[0xfb] // base
    RAM[0xfbe2] = 0x00000005000000f1;          RAM[0xfbe3] = 0x000000f1000000fb;       // RAM[0xfbe2]: ADD   f1 f1fb // REG[0xf1] <- REG[0xf1] + REG[0xfb] // parametro
    RAM[0xfbe4] = 0x00000005000000ff;          RAM[0xfbe5] = 0x000000ff000000fb;       // RAM[0xfbe4]: ADD   ff fffb // REG[0xff] <- REG[0xff] + REG[0xfb] // parametro
    RAM[0xfbe6] = 0x00000005000000fc;          RAM[0xfbe7] = 0x000000fc000000fb;       // RAM[0xfbe6]: ADD   fc fcfb // REG[0xfc] <- REG[0xfc] + REG[0xfb] // resultado
    RAM[0xfbe8] = 0x0000000b00000000;                                                  // RAM[0xfbe8]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    
    //INT
    RAM[0xfbea] = 0x0000000200000000;          RAM[0xfbeb] = 0x0000000000000000;       // RAM[0xfbea]: LOAD  00 00   // REG[0xf0] <- 00
    RAM[0xfbec] = 0x00000005000000fe;          RAM[0xfbed] = 0x000000fe000000fa;       // RAM[0xfbea]: ADD   fe fefa // REG[0xfe] <- REG[0xfe] + REG[0xfa] // base
    RAM[0xfbee] = 0x00000005000000f1;          RAM[0xfbef] = 0x000000f1000000fa;       // RAM[0xfbea]: ADD   f1 f1fa // REG[0xf1] <- REG[0xf1] + REG[0xfa] // parametro
    RAM[0xfbf0] = 0x00000005000000ff;          RAM[0xfbf1] = 0x000000ff000000fa;       // RAM[0xfbea]: ADD   ff fffa // REG[0xff] <- REG[0xff] + REG[0xfa] // parametro
    RAM[0xfbf2] = 0x00000005000000fc;          RAM[0xfbf3] = 0x000000fc000000fa;       // RAM[0xfbea]: ADD   fc fcfa // REG[0xfc] <- REG[0xfc] + REG[0xfa] // resultado
    RAM[0xfbf4] = 0x00000003000000fe;          RAM[0xfbf5] = 0x000000000000fc03;       // RAM[0xfbea]: STORE fe fc03 // RAM[0xfc03] <- REG[0x04] // return
    RAM[0xfbf6] = 0x00000003000000f1;          RAM[0xfbf7] = 0x000000000000fc01;       // RAM[0xfbea]: STORE f1 fc01 // RAM[0xfc01] <- REG[0x04] // parametro
    RAM[0xfbf8] = 0x00000003000000ff;          RAM[0xfbf9] = 0x000000000000fbff;       // RAM[0xfbea]: STORE ff fbff // RAM[0xfbff] <- REG[0x04] // parametro
    RAM[0xfbfa] = 0x00000003000000fc;          RAM[0xfbfb] = 0x000000000000fc05;       // RAM[0xfbea]: STORE fc fc05 // RAM[0xfc05] <- REG[0x04] // resultado
    RAM[0xfbfc] = 0x0000000b00000000;          RAM[0xfbfd] = 0x000000000000fbfe;       // RAM[0xfbea]: JUMP  00 fbfe // if (REG[0x00] == REG[0x00]) {p <- 0xfbfe;}
    
    //Save STACK
    RAM[0xfbfe] = 0x000000030000000f;                                          // RAM[0xfbfe]: STORE 0f      // RAM[0x] <- REG[0x0f]
    RAM[0xfc00] = 0x000000030000000e;                                          // RAM[0xfc00]: STORE 0e      // RAM[0x] <- REG[0x0e] 
    RAM[0xfc02] = 0x00000003000000fd;                                          // RAM[0xfc02]: STORE fd      // RAM[0x] <- REG[0xfd] 
    RAM[0xfc04] = 0x0000000300000000;                                          // RAM[0xfc04]: STORE 00      // RAM[0x] <- REG[0x00] 
    RAM[0xfc06] = 0x0000000b00000000;                                          // RAM[0xfc06]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    
    //STACK
  
    RAM[0xfc08] = 0x0000000b00000000;                                          // RAM[0xfc08]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc0d] = 0x0000000b00000000;                                          // RAM[0xfc0d]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc12] = 0x0000000b00000000;                                          // RAM[0xfc12]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc17] = 0x0000000b00000000;                                          // RAM[0xfc17]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc1c] = 0x0000000b00000000;                                          // RAM[0xfc1c]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc21] = 0x0000000b00000000;                                          // RAM[0xfc21]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc26] = 0x0000000b00000000;                                          // RAM[0xfc26]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc2b] = 0x0000000b00000000;                                          // RAM[0xfc2b]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc30] = 0x0000000b00000000;                                          // RAM[0xfc30]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc35] = 0x0000000b00000000;                                          // RAM[0xfc35]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc3a] = 0x0000000b00000000;                                          // RAM[0xfc3a]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc3f] = 0x0000000b00000000;                                          // RAM[0xfc3f]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc44] = 0x0000000b00000000;                                          // RAM[0xfc44]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc49] = 0x0000000b00000000;                                          // RAM[0xfc49]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc4e] = 0x0000000b00000000;
    RAM[0xfc53] = 0x0000000b00000000;
    RAM[0xfc58] = 0x0000000b00000000;
    RAM[0xfc5d] = 0x0000000b00000000;
    RAM[0xfc62] = 0x0000000b00000000;
    RAM[0xfc67] = 0x0000000b00000000;
    RAM[0xfc6c] = 0x0000000b00000000;
    RAM[0xfc71] = 0x0000000b00000000;
    RAM[0xfc76] = 0x0000000b00000000;
    RAM[0xfc7b] = 0x0000000b00000000;
    RAM[0xfc80] = 0x0000000b00000000;
    RAM[0xfc85] = 0x0000000b00000000;
    RAM[0xfc8a] = 0x0000000b00000000;
    RAM[0xfc8f] = 0x0000000b00000000;
    RAM[0xfc94] = 0x0000000b00000000;
    RAM[0xfc99] = 0x0000000b00000000;
    RAM[0xfc9e] = 0x0000000b00000000;
    RAM[0xfca3] = 0x0000000b00000000;
    RAM[0xfca8] = 0x0000000b00000000;
    RAM[0xfcad] = 0x0000000b00000000;
    RAM[0xfcb2] = 0x0000000b00000000;
    RAM[0xfcb7] = 0x0000000b00000000;
    RAM[0xfcbc] = 0x0000000b00000000;
    RAM[0xfcc1] = 0x0000000b00000000;
    RAM[0xfcc6] = 0x0000000b00000000;
    RAM[0xfccb] = 0x0000000b00000000;
    RAM[0xfcd0] = 0x0000000b00000000;
    RAM[0xfcd5] = 0x0000000b00000000;
    RAM[0xfcda] = 0x0000000b00000000;
    RAM[0xfcdf] = 0x0000000b00000000;
    RAM[0xfce4] = 0x0000000b00000000;
    RAM[0xfce9] = 0x0000000b00000000;
    RAM[0xfcee] = 0x0000000b00000000;
    RAM[0xfcf3] = 0x0000000b00000000;
    RAM[0xfcf8] = 0x0000000b00000000;
    RAM[0xfcfd] = 0x0000000b00000000;
    RAM[0xfd02] = 0x0000000b00000000;
    RAM[0xfd07] = 0x0000000b00000000;
    RAM[0xfd0c] = 0x0000000b00000000;
    RAM[0xfd11] = 0x0000000b00000000;
    RAM[0xfd16] = 0x0000000b00000000;
    RAM[0xfd1b] = 0x0000000b00000000;
    RAM[0xfd20] = 0x0000000b00000000;
    RAM[0xfd25] = 0x0000000b00000000;
    RAM[0xfd2a] = 0x0000000b00000000;
    RAM[0xfd2f] = 0x0000000b00000000;
    RAM[0xfd34] = 0x0000000b00000000;
    RAM[0xfd39] = 0x0000000b00000000;
    RAM[0xfd3e] = 0x0000000b00000000;
    RAM[0xfd43] = 0x0000000b00000000;
    RAM[0xfd48] = 0x0000000b00000000;
    RAM[0xfd4d] = 0x0000000b00000000;
    RAM[0xfd52] = 0x0000000b00000000;
    RAM[0xfd57] = 0x0000000b00000000;
    RAM[0xfd5c] = 0x0000000b00000000;
    RAM[0xfd61] = 0x0000000b00000000;
    RAM[0xfd66] = 0x0000000b00000000;
    RAM[0xfd6b] = 0x0000000b00000000;
    RAM[0xfd70] = 0x0000000b00000000;
    RAM[0xfd75] = 0x0000000b00000000;
    RAM[0xfd7a] = 0x0000000b00000000;
    RAM[0xfd7f] = 0x0000000b00000000;
    RAM[0xfd84] = 0x0000000b00000000;
    RAM[0xfd89] = 0x0000000b00000000;
    RAM[0xfd8e] = 0x0000000b00000000;
    RAM[0xfd93] = 0x0000000b00000000;
    RAM[0xfd98] = 0x0000000b00000000;
    RAM[0xfd9d] = 0x0000000b00000000;
    RAM[0xfda2] = 0x0000000b00000000;
    RAM[0xfda7] = 0x0000000b00000000;
    RAM[0xfdac] = 0x0000000b00000000;
    RAM[0xfdb1] = 0x0000000b00000000;
    RAM[0xfdb6] = 0x0000000b00000000;
    RAM[0xfdbb] = 0x0000000b00000000;
    RAM[0xfdc0] = 0x0000000b00000000;
    RAM[0xfdc5] = 0x0000000b00000000;
    RAM[0xfdca] = 0x0000000b00000000;
    RAM[0xfdcf] = 0x0000000b00000000;
    RAM[0xfdd4] = 0x0000000b00000000;
    RAM[0xfdd9] = 0x0000000b00000000;
    RAM[0xfdde] = 0x0000000b00000000;
    RAM[0xfde3] = 0x0000000b00000000;
    RAM[0xfde8] = 0x0000000b00000000;
    RAM[0xfded] = 0x0000000b00000000;
    RAM[0xfdf2] = 0x0000000b00000000;
    RAM[0xfdf7] = 0x0000000b00000000;
    RAM[0xfdfc] = 0x0000000b00000000;
    RAM[0xfe01] = 0x0000000b00000000;
    RAM[0xfe06] = 0x0000000b00000000;
    RAM[0xfe0b] = 0x0000000b00000000;
    RAM[0xfe10] = 0x0000000b00000000;
    RAM[0xfe15] = 0x0000000b00000000;
    RAM[0xfe1a] = 0x0000000b00000000;
    RAM[0xfe1f] = 0x0000000b00000000;
    RAM[0xfe24] = 0x0000000b00000000;
    RAM[0xfe29] = 0x0000000b00000000;
    RAM[0xfe2e] = 0x0000000b00000000;
    RAM[0xfe33] = 0x0000000b00000000;
    RAM[0xfe38] = 0x0000000b00000000;
    RAM[0xfe3d] = 0x0000000b00000000;
    RAM[0xfe42] = 0x0000000b00000000;
    RAM[0xfe47] = 0x0000000b00000000;
    RAM[0xfe4c] = 0x0000000b00000000;
    RAM[0xfe51] = 0x0000000b00000000;
    RAM[0xfe56] = 0x0000000b00000000;
    RAM[0xfe5b] = 0x0000000b00000000;
    RAM[0xfe60] = 0x0000000b00000000;
    RAM[0xfe65] = 0x0000000b00000000;
    RAM[0xfe6a] = 0x0000000b00000000;
    RAM[0xfe6f] = 0x0000000b00000000;
    RAM[0xfe74] = 0x0000000b00000000;
    RAM[0xfe79] = 0x0000000b00000000;
    RAM[0xfe7e] = 0x0000000b00000000;
    RAM[0xfe83] = 0x0000000b00000000;
    RAM[0xfe88] = 0x0000000b00000000;
    RAM[0xfe8d] = 0x0000000b00000000;
    RAM[0xfe92] = 0x0000000b00000000;
    RAM[0xfe97] = 0x0000000b00000000;
    RAM[0xfe9c] = 0x0000000b00000000;
    RAM[0xfea1] = 0x0000000b00000000;
    RAM[0xfea6] = 0x0000000b00000000;
    RAM[0xfeab] = 0x0000000b00000000;
    RAM[0xfeb0] = 0x0000000b00000000;
    RAM[0xfeb5] = 0x0000000b00000000;
    RAM[0xfeba] = 0x0000000b00000000;
    RAM[0xfebf] = 0x0000000b00000000;
    RAM[0xfec4] = 0x0000000b00000000;
    RAM[0xfec9] = 0x0000000b00000000;
    RAM[0xfece] = 0x0000000b00000000;
    RAM[0xfed3] = 0x0000000b00000000;
    RAM[0xfed8] = 0x0000000b00000000;
    RAM[0xfedd] = 0x0000000b00000000;
    RAM[0xfee2] = 0x0000000b00000000;
    RAM[0xfee7] = 0x0000000b00000000;
    RAM[0xfeec] = 0x0000000b00000000;
    RAM[0xfef1] = 0x0000000b00000000;
    RAM[0xfef6] = 0x0000000b00000000;
    RAM[0xfefb] = 0x0000000b00000000;
    RAM[0xff00] = 0x0000000b00000000;
    RAM[0xff05] = 0x0000000b00000000;
    RAM[0xff0a] = 0x0000000b00000000;
    RAM[0xff0f] = 0x0000000b00000000;
    RAM[0xff14] = 0x0000000b00000000;
    RAM[0xff19] = 0x0000000b00000000;
    RAM[0xff1e] = 0x0000000b00000000;
    RAM[0xff23] = 0x0000000b00000000;
    RAM[0xff28] = 0x0000000b00000000;
    RAM[0xff2d] = 0x0000000b00000000;
    RAM[0xff32] = 0x0000000b00000000;
    RAM[0xff37] = 0x0000000b00000000;
    RAM[0xff3c] = 0x0000000b00000000;
    RAM[0xff41] = 0x0000000b00000000;
    RAM[0xff46] = 0x0000000b00000000;
    RAM[0xff4b] = 0x0000000b00000000;
    RAM[0xff50] = 0x0000000b00000000;
    RAM[0xff55] = 0x0000000b00000000;
    RAM[0xff5a] = 0x0000000b00000000;
    RAM[0xff5f] = 0x0000000b00000000;
    RAM[0xff64] = 0x0000000b00000000;
    RAM[0xff69] = 0x0000000b00000000;
    RAM[0xff6e] = 0x0000000b00000000;
    RAM[0xff73] = 0x0000000b00000000;
    RAM[0xff78] = 0x0000000b00000000;
    RAM[0xff7d] = 0x0000000b00000000;
    RAM[0xff82] = 0x0000000b00000000;
    RAM[0xff87] = 0x0000000b00000000;
    RAM[0xff8c] = 0x0000000b00000000;
    RAM[0xff91] = 0x0000000b00000000;
    RAM[0xff96] = 0x0000000b00000000;
    RAM[0xff9b] = 0x0000000b00000000;
    RAM[0xffa0] = 0x0000000b00000000;
    RAM[0xffa5] = 0x0000000b00000000;
    RAM[0xffaa] = 0x0000000b00000000;
    RAM[0xffaf] = 0x0000000b00000000;
    RAM[0xffb4] = 0x0000000b00000000;
    RAM[0xffb9] = 0x0000000b00000000;
    RAM[0xffbe] = 0x0000000b00000000;
    RAM[0xffc3] = 0x0000000b00000000;
    RAM[0xffc4] = 0x0000000b00000000;
    RAM[0xffc8] = 0x0000000b00000000;
    RAM[0xffcd] = 0x0000000b00000000;
    RAM[0xffd2] = 0x0000000b00000000;
    RAM[0xffd7] = 0x0000000b00000000;
    RAM[0xffdc] = 0x0000000b00000000;
    RAM[0xffe1] = 0x0000000b00000000;
    RAM[0xffe6] = 0x0000000b00000000;
    RAM[0xffeb] = 0x0000000b00000000;
    RAM[0xfff0] = 0x0000000b00000000;
    RAM[0xfff5] = 0x0000000b00000000;
    RAM[0xfffa] = 0x0000000b00000000;
    RAM[0xffff] = 0x0000000b00000000;
    



    printf("%5s %5s %5s %5s %24s %24s %24s %24s %24s %24s","op","opr1","opr2","opr3", "ARI1", "ARI2", "ARI3", "ARI4", "ARI5", "ARI6");
    printf("\n");
    printf("----- ----- ----- -----");
    printf("\n");
    uint64_t p = 0;
    
    
    do {
        i = transformInstruction(RAM[p], RAM[p+1]);
        p+=2;
        switch (i.op) {
            
            case 1: reg[i.opr1] = RAM[trans(i.opr2, i.opr3)];                           break; // LOAD registrador <- RAM
            case 2: reg[i.opr1] = trans(i.opr2, i.opr3);                                break; // LOAD registrador <- constante
            case 3: RAM[trans(i.opr2, i.opr3)] = reg[i.opr1];                           break; // STORE
            case 4: reg[i.opr3] = reg[i.opr2];                                          break; // MOVE
            case 5: reg[i.opr1] = sum_comp2(reg[i.opr2], reg[i.opr3]);                  break; // ADD complemento de 2
            case 6: reg[i.opr1] = sum_flut(reg[i.opr2], reg[i.opr3]);                   break; // ADD ponto flutuante
            case 7: reg[i.opr1] = reg[i.opr2] | reg[i.opr3];                            break; // OR
            case 8: reg[i.opr1] = reg[i.opr2] & reg[i.opr3];                            break; // AND
            case 9: reg[i.opr1] = reg[i.opr2] ^ reg[i.opr3];                            break; // OR EXCLUSIVO
            case 0xA: reg[i.opr1] = rot(reg[i.opr2], i.opr3);                           break; // ROTACAO
            case 0xB: if(reg[i.opr1] == reg[0]) {p = trans(i.opr2, i.opr3);};           break; // JUMP
            case 0xC: p = 0;                                                            break; // HALT
        }
        
        printf("%5s %5x %5x %5x ", getInstructionName(i.op), i.opr1, i.opr2, i.opr3);
        uint64_t stop = reg[0xfc];
        if(p > 0xfbf2 && p <= 0xfc06){
                stop = stop - 5;
            }
        /*for(uint64_t h = 0x0000fc0e; h <= stop; h+=5){
            if(RAM[h]<=0x1c || (RAM[h]>=0x42 && RAM[h]<=0x54)){
                printf(" %5x %5x %5x %5x", RAM[h], RAM[h+1], RAM[h+2], RAM[h+3]);
            }
            
        }
        printf("\n");*/
        for (uint64_t h = 0; h < 16; h++) {
           /*uint64_t aux = reg[h];
            for(uint64_t j = 7; j > -1; j--) {
                if ( (aux/pow(2, j)) >= 1 ) { aux -= pow(2, j); printf("1"); }
                else { printf("0"); }
            }
            printf(" ");
            //*/printf(" %8ld", reg[h]);
        }
        printf("\n");
        
    } while (p != 0);
    printf("----- ----- ----- -----");
    
    printf("\n");
    printf("%5s %5s %5s %5s %24s %24s %24s %24s %24s %24s","op","opr1","opr2","opr3", "ARI1", "ARI2", "ARI3", "ARI4", "ARI5", "ARI6");
    printf("\nend                     \n");
}


uint64_t sum_comp2(uint64_t val1, uint64_t val2){
    uint64_t sinal1 = val1 >> 31;
    uint64_t sinal2 = val2 >> 31;
    uint64_t result;
    if(sinal1 == 0){
        if(sinal2 == 0){
            result = val1 + val2;
            if(result > (unsigned long long)9223372036854775807){
                result -= (unsigned long long)9223372036854775807;
            }
        }
        else{
            result = val1 - ((unsigned long long)18446744073709551615 - val2 + 1);
            if(result < 0){
                result *= -1;
                result = (unsigned long long)18446744073709551615 - result + 1;
            }
        }
    }
    else{
        if(sinal2 == 0){
            result =  val2 - ((unsigned long long)18446744073709551615 - val1 + 1);
            if(result < 0){
                result *= -1;
                result = (unsigned long long)18446744073709551615 - result + 1;
            }
        }
        else{
            result = ((unsigned long long)18446744073709551615 - val1 + 1) + ((unsigned long long)18446744073709551615 - val2 + 1);
            result = (unsigned long long)18446744073709551615 - result + 1;
        }
    }
    return result;
}
uint64_t sum_flut(uint64_t val1, uint64_t val2){
    uint64_t sinal1, sinal2, expv1, expv2, mant1, mant2, result, soma;
    sinal1 = val1>>63;
    sinal2 = val2>>63;
    expv1 = val1<<1; expv1 = expv1>>33;
    expv2 = val2<<1; expv2 = expv2>>33;
    mant1 = val1 & 0xffffffff;
    mant2 = val2 & 0xffffffff;
    
    if(expv1 != expv2){
        uint64_t aux;
        if(expv1 > expv2){
            aux = expv1-expv2;
            mant2>>aux;
        }
        else{
            aux = expv2-expv1;
            mant1>>aux;
        }
    }
    
    if(sinal1 == 0){
        if(sinal2 == 0){
            soma = mant1 + mant2;
            result = sinal1<<63;
            result += expv1<<32;
            result += soma;
            return result;
        }
        else{
            soma = abs(mant1 - mant2);
            if(mant2 > mant1) { result = sinal2<<63; }
            else { result = sinal1<<63;}
            result += expv1<<32;
            result += soma;
            return result;
        }
    }
    else{
        if(sinal2 == 0){
            soma = abs(mant1 - mant2);
            if(mant1 > mant2) { result = sinal1<<63; }
            else { result = sinal2<<63;}
            result += expv1<<32;
            result += soma;
            return result;
        }
        else{
            soma = abs(mant1 + mant2);
            result = sinal1<<63;
            result += expv1<<32;
            result += soma;
            return result;
        }
    }
}

uint64_t rot(uint64_t val1, uint64_t val2){
    uint64_t a = val1>>val2 ;
    uint64_t b = val1<<(64-val2);
    uint64_t c = a+b;
    return c;
}
uint64_t trans(uint64_t val1, uint64_t val2){
    uint64_t a1 = val1<<32;
    uint64_t b = a1 + val2;
    return b;
}


Tinstruction transformInstruction(uint64_t a, uint64_t b){
    Tinstruction result;
    result.op = a>>32;
    result.opr1 = a & (uint64_t)4294967295; 
    result.opr2 = b>>32;
    result.opr3 = b & (uint64_t)4294967295;
    return result;
}
char * getInstructionName(uint64_t inst){
    return instructionString[inst - 1];
}