#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>
#include<math.h>
#include<time.h>

typedef struct{     
    uint32_t op;        // operacao
    uint32_t opr1;      // operando1
    uint32_t opr2;      // operando2
    uint32_t opr3;      // operando3
} Tinstruction;     

// List of available instructions
char * instructionString[] = { "LOAD", "LOAD", "STORE", "MOVE", "ADD", "ADD", "OR", "AND", "EXCLS", "ROTAT", "JUMP", "HALT", "NEG", "MULT"};
// Prototypes 
char * getInstructionName(int inst);
uint32_t sum_comp2(uint32_t val1, int val2);
uint32_t sum_flut(uint32_t val1, int val2);
uint32_t rot(uint32_t val1, uint32_t val2);
uint32_t trans(uint32_t val1, uint32_t val2);
uint32_t neg(uint32_t val1);
uint32_t mult(uint32_t val1, uint32_t val2);
uint32_t divide(uint32_t val1, uint32_t val2);
uint32_t mod(uint32_t val1, uint32_t val2);
void fibonacci_it(uint32_t a);
Tinstruction transformInstruction(uint32_t a, uint32_t b);

int main(){
    FILE *times;
    times = fopen("seconds.txt", "w");
    uint32_t f = 0;
    time_t t_ini, t_fim;
    float trec = 0;
    while(f < 50){
        t_ini = time(NULL); 
        fibonacci_it(f);
        t_fim = time(NULL);
        trec = difftime(t_fim, t_ini);
        fprintf(times, "%d\t%f\n", f, trec );
        f++;
    }
    printf("%d", f);
    fflush(times);
    fclose(times);
    return 0;
}

void fibonacci_it(uint32_t a){
    uint32_t RAM[65536]; // ffff
    uint32_t reg[65536];  // registradores
    Tinstruction i;
    printf("start                   registradores\n");
    // Parametros
    
    //operador&operando1        operando2&operando3
    
    RAM[ 0x0] = 0x000200fa;           RAM[ 0x1] = 0x00000004;       //RAM[ 0x0]: 2a02 LOAD  0a 02 //2
    RAM[ 0x2] = 0x000200fb;           RAM[ 0x3] = 0xfffffffc;       //RAM[ 0x2]: 2bfe LOAD  0b fe //-2
    RAM[ 0x4] = 0x000200fe;           RAM[ 0x5] = 0x0000fc07;       //RAM[ 0x4]: 29aa LOAD  09 aa //base
    RAM[ 0x6] = 0x000200f1;           RAM[ 0x7] = 0x0000fc08;       //RAM[ 0x4]: 29aa LOAD  09 aa //base
    RAM[ 0x8] = 0x000200ff;           RAM[ 0x9] = 0x0000fc09;       //RAM[ 0x6]: 2ddc LOAD  0d dc //topo
    RAM[ 0xa] = 0x0002000f;           RAM[ 0xb] = a;                //RAM[ 0x8]: 2f02 LOAD  0f 02 //Parametros
    RAM[ 0xc] = 0x0002000e;           RAM[ 0xd] = 0x00000001;       //RAM[ 0xa]: 2e07 LOAD  0e 07 //Parametros
    RAM[ 0xe] = 0x00020000;           RAM[ 0xf] = 0x00000016;       //RAM[0x4c]: 2054 LOAD  00 54 // REG[0x00] <- 54
    RAM[0x10] = 0x00030000;           RAM[0x11] = 0x0000fc05;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0x12] = 0x000200fd;           RAM[0x13] = 0x00000018;       //RAM[0x50]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0x14] = 0x000b0000;           RAM[0x15] = 0x0000fbec;       //RAM[0x52]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0x16] = 0x000b0000;           RAM[0x17] = 0x0000eece;       //RAM[0x58]: b05a JUMP  00 5a // GEQ
    RAM[0x18] = 0x00020000;           RAM[0x19] = 0x00000001;       //RAM[ 0xa]: 2e07 LOAD  0e 07 //Parametros
    RAM[0x1a] = 0x000b0004;           RAM[0x1b] = 0x00000038;       //RAM[0x1a]: b088 JUMP  00 88 //00
    RAM[0x1c] = 0x00020001;           RAM[0x1d] = 0x00000002;       //RAM[ 0xa]: 2e07 LOAD  0e 07 //Parametros
    RAM[0x1e] = 0x00020002;           RAM[0x1f] = 0x00000000;       //RAM[ 0xa]: 2e07 LOAD  0e 07 //Parametros
    RAM[0x20] = 0x00020003;           RAM[0x21] = 0x00000001;       //RAM[ 0xa]: 2e07 LOAD  0e 07 //Parametros
    //01
    RAM[0x22] = 0x00050009;           RAM[0x23] = 0x00020003;       //RAM[ 0xc]: 2c1c LOAD  0c 16 
    RAM[0x24] = 0x00040000;           RAM[0x25] = 0x0001000e;
    RAM[0x26] = 0x00020000;           RAM[0x27] = 0x0000002e;       //RAM[0x4c]: 2054 LOAD  00 54 // REG[0x00] <- 54
    RAM[0x28] = 0x00030000;           RAM[0x29] = 0x0000fc05;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0x2a] = 0x000200fd;           RAM[0x2b] = 0x00000030;       //RAM[0x50]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0x2c] = 0x000b0000;           RAM[0x2d] = 0x0000fbec;       //RAM[0x52]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0x2e] = 0x000b0000;           RAM[0x2f] = 0x0000eece;       //RAM[0x58]: b05a JUMP  00 5a // GEQ
    RAM[0x30] = 0x00020000;           RAM[0x31] = 0x00000000;       //RAM[ 0xa]: 2e07 LOAD  0e 07 //Parametros
    RAM[0x32] = 0x000b0004;           RAM[0x33] = 0x0000003c;       //RAM[0x1a]: b088 JUMP  00 88 //02
    RAM[0x34] = 0x00040000;           RAM[0x35] = 0x00090004;
    RAM[0x36] = 0x000c0000;           RAM[0x37] = 0x00000000;       //RAM[0x1c]: c000 HALT  00 00
    RAM[0x38] = 0x00040000;           RAM[0x39] = 0x000f0004;       //RAM[ 0xc]: 2c1c LOAD  0c 16 //00
    RAM[0x3a] = 0x000c0000;           RAM[0x3b] = 0x00000000;       //RAM[0x1c]: c000 HALT  00 00
    RAM[0x3c] = 0x00040000;           RAM[0x3d] = 0x00030002;       //02
    RAM[0x3e] = 0x00040000;           RAM[0x3f] = 0x00090003;
    RAM[0x40] = 0x00020009;           RAM[0x41] = 0x00000001;       //RAM[ 0xe]: 2016 LOAD  00 14
    RAM[0x42] = 0x00050001;           RAM[0x43] = 0x00010009;
    RAM[0x44] = 0x000b0000;           RAM[0x45] = 0x00000022;       //RAM[0x1a]: b088 JUMP  00 88 //01
    
    
    //FIBONACCI
    RAM[0xee90] = 0x00020001;           RAM[0xee91] = 0xffffffff;       //RAM[0x4c]: 21ff LOAD  01 ff // REG[0x01] <- ff
    RAM[0xee92] = 0x0002000e;           RAM[0xee93] = 0x00000001;       //RAM[0x4c]: 2e01 LOAD  0e 01 // REG[0x0e] <- 01
    RAM[0xee94] = 0x00020000;           RAM[0xee95] = 0x0000ee9c;       //RAM[0x4c]: 2054 LOAD  00 54 // REG[0x00] <- 54
    RAM[0xee96] = 0x00030000;           RAM[0xee97] = 0x0000fc05;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xee98] = 0x000200fd;           RAM[0xee99] = 0x0000ee9e;       //RAM[0x50]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xee9a] = 0x000b0000;           RAM[0xee9b] = 0x0000fbec;       //RAM[0x52]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xee9c] = 0x000b0000;           RAM[0xee9d] = 0x0000eece;       //RAM[0x58]: b05a JUMP  00 5a // GEQ
    RAM[0xee9e] = 0x00020000;           RAM[0xee9f] = 0x00000000;       //RAM[0x4c]: 2001 LOAD  00 00 // REG[0x00] <- 00
    RAM[0xeea0] = 0x000b0004;           RAM[0xeea1] = 0x0000eeac;       //RAM[0x52]: b4a0 JUMP  00 a0 // if (REG[0x00] == REG[0x04]) {p <- 0xeeae;}
    RAM[0xeea2] = 0x00010009;           RAM[0xeea3] = 0x000000f4;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xeea4] = 0x00040000;           RAM[0xeea5] = 0x000f0004;       //RAM[0x4c]: 2001 LOAD  00 00 // REG[0x00] <- 00
    RAM[0xeea6] = 0x00050004;           RAM[0xeea7] = 0x00040009;       //RAM[0x42]: 5ff1 ADD   0f f1 // REG[0x0f] <- REG[0x0f] + REG[0x01] 
    RAM[0xeea8] = 0x00030004;           RAM[0xeea9] = 0x000000f4;
    RAM[0xeeaa] = 0x000b0000;           RAM[0xeeab] = 0x0000fbda;       //RAM[0x84]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xeeac] = 0x0005000f;           RAM[0xeead] = 0x000f0001;       //RAM[0x42]: 5ff1 ADD   0f f1 // REG[0x0f] <- REG[0x0f] + REG[0x01] 
    RAM[0xeeae] = 0x00020000;           RAM[0xeeaf] = 0x0000eeb6;       //RAM[0x4c]: 2054 LOAD  00 54 // REG[0x00] <- 54
    RAM[0xeeb0] = 0x00030000;           RAM[0xeeb1] = 0x0000fc05;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xeeb2] = 0x000200fd;           RAM[0xeeb3] = 0x0000eeb8;       //RAM[0x50]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xeeb4] = 0x000b0000;           RAM[0xeeb5] = 0x0000fbec;       //RAM[0x52]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xeeb6] = 0x000b0000;           RAM[0xeeb7] = 0x0000ee90;       //RAM[0x58]: b05a JUMP  00 5a // FIBONACCI
    
    RAM[0xeeb8] = 0x0005000f;           RAM[0xeeb9] = 0x000f0001;       //RAM[0x42]: 5ff1 ADD   0f f1 // REG[0x0f] <- REG[0x0f] + REG[0x01] 
    RAM[0xeeba] = 0x00020000;           RAM[0xeebb] = 0x0000eec2;       //RAM[0x4c]: 2054 LOAD  00 54 // REG[0x00] <- 54
    RAM[0xeebc] = 0x00030000;           RAM[0xeebd] = 0x0000fc05;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xeebe] = 0x000200fd;           RAM[0xeebf] = 0x0000eec4;       //RAM[0x50]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xeec0] = 0x000b0000;           RAM[0xeec1] = 0x0000fbec;       //RAM[0x52]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xeec2] = 0x000b0000;           RAM[0xeec3] = 0x0000ee90;       //RAM[0x58]: b05a JUMP  00 5a // FIBONACCI
    RAM[0xeec4] = 0x00010009;           RAM[0xeec5] = 0x000000f4;       //RAM[0x4c]: 1cf6 LOAD  02 f6 // REG[0x0c] <- RAM[0xf6]
    RAM[0xeec6] = 0x00040000;           RAM[0xeec7] = 0x00090004;       //RAM[0x42]: 5ff1 ADD   0f f1 // REG[0x0f] <- REG[0x0f] + REG[0x01] 
    RAM[0xeec8] = 0x000b0000;           RAM[0xeec9] = 0x0000fbda;       //RAM[0x84]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}

    //GEQ
    RAM[0xeece] = 0x00020000;           RAM[0xeecf] = 0x0000eed6;       //RAM[0x4c]: 2054 LOAD  00 54 // REG[0x00] <- 54
    RAM[0xeed0] = 0x00030000;           RAM[0xeed1] = 0x0000fc05;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xeed2] = 0x000200fd;           RAM[0xeed3] = 0x0000eed8;       //RAM[0x50]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xeed4] = 0x000b0000;           RAM[0xeed5] = 0x0000fbec;       //RAM[0x52]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xeed6] = 0x000b0000;           RAM[0xeed7] = 0x0000efd8;       //RAM[0x58]: b05a JUMP  00 5a // GTR
    RAM[0xeed8] = 0x00020000;           RAM[0xeed9] = 0x00000001;       //RAM[0x60]: 2001 LOAD  00 01 // REG[0x00] <- 01
    RAM[0xeeda] = 0x000b0004;           RAM[0xeedb] = 0x0000eeee;       //RAM[0x62]: b482 JUMP  04 82 // if (REG[0x00] == REG[0x04]) {p <- 0x82;}
    RAM[0xeedc] = 0x00020000;           RAM[0xeedd] = 0x0000eee4;       //RAM[0x66]: 206e LOAD  00 6e // REG[0x00] <- 6e
    RAM[0xeede] = 0x00030000;           RAM[0xeedf] = 0x0000fc05;       //RAM[0x68]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xeee0] = 0x000200fd;           RAM[0xeee1] = 0x0000eee6;       //RAM[0x6a]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xeee2] = 0x000b0000;           RAM[0xeee3] = 0x0000fbec;       //RAM[0x6c]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xeee4] = 0x000b0000;           RAM[0xeee5] = 0x0000ef70;       //RAM[0x72]: b024 JUMP  00 24 // EQL
    RAM[0xeee6] = 0x00020000;           RAM[0xeee7] = 0x00000001;       //RAM[0x7a]: 2001 LOAD  00 01 // REG[0x00] <- 01
    RAM[0xeee8] = 0x000b0004;           RAM[0xeee9] = 0x0000eeee;       //RAM[0x7c]: b482 JUMP  04 82 // if (REG[0x00] == REG[0x04]) {p <- 0x82;}
    RAM[0xeeea] = 0x00020004;           RAM[0xeeeb] = 0x00000000;       //RAM[0x7e]: 2400 LOAD  04 00 // REG[0x04] <- 00
    RAM[0xeeec] = 0x000b0000;           RAM[0xeeed] = 0x0000fbda;       //RAM[0x80]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xeeee] = 0x00020004;           RAM[0xeeef] = 0x00000001;       //RAM[0x82]: 2401 LOAD  04 01 // REG[0x04] <- 01
    RAM[0xeef0] = 0x000b0000;           RAM[0xeef1] = 0x0000fbda;       //RAM[0x84]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}

    //LEQ
    RAM[0xeef2] = 0x00020000;           RAM[0xeef3] = 0x0000eefa;       //RAM[0x4c]: 2054 LOAD  00 54 // REG[0x00] <- 54
    RAM[0xeef4] = 0x00030000;           RAM[0xeef5] = 0x0000fc05;       //RAM[0x4e]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xeef6] = 0x000200fd;           RAM[0xeef7] = 0x0000eefc;       //RAM[0x50]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xeef8] = 0x000b0000;           RAM[0xeef9] = 0x0000fbec;       //RAM[0x52]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xeefa] = 0x000b0000;           RAM[0xeefb] = 0x0000efd8;       //RAM[0x58]: b074 JUMP  00 74 // GTR
    RAM[0xeefc] = 0x00020000;           RAM[0xeefd] = 0x00000000;       //RAM[0x60]: 2000 LOAD  00 00 // REG[0x00] <- 00
    RAM[0xeefe] = 0x000b0004;           RAM[0xeeff] = 0x0000ef12;       //RAM[0x62]: b482 JUMP  04 82 // if (REG[0x00] == REG[0x04]) {p <- 0x82;}
    RAM[0xef00] = 0x00020000;           RAM[0xef01] = 0x0000ef08;       //RAM[0x66]: 206e LOAD  00 6e // REG[0x00] <- 6e
    RAM[0xef02] = 0x00030000;           RAM[0xef03] = 0x0000fc05;       //RAM[0x68]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xef04] = 0x000200fd;           RAM[0xef05] = 0x0000ef0a;       //RAM[0x6a]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xef06] = 0x000b0000;           RAM[0xef07] = 0x0000fbec;       //RAM[0x6c]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xef08] = 0x000b0000;           RAM[0xef09] = 0x0000ef70;       //RAM[0x72]: b024 JUMP  00 2a // EQL
    RAM[0xef0a] = 0x00020000;           RAM[0xef0b] = 0x00000001;       //RAM[0x7a]: 2001 LOAD  00 01 // REG[0x00] <- 01
    RAM[0xef0c] = 0x000b0004;           RAM[0xef0d] = 0x0000ef12;       //RAM[0x7c]: b482 JUMP  04 82 // if (REG[0x00] == REG[0x04]) {p <- 0x82;}
    RAM[0xef0e] = 0x00020004;           RAM[0xef0f] = 0x00000000;       //RAM[0x7e]: 2400 LOAD  04 00 // REG[0x04] <- 00
    RAM[0xef10] = 0x000b0000;           RAM[0xef11] = 0x0000fbda;       //RAM[0x80]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xef12] = 0x00020004;           RAM[0xef13] = 0x00000001;       //RAM[0x82]: 2401 LOAD  04 01 // REG[0x04] <- 01
    RAM[0xef14] = 0x000b0000;           RAM[0xef15] = 0x0000fbda;       //RAM[0x84]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    
    //LSS
    RAM[0xef16] = 0x00020000;           RAM[0xef17] = 0x0000ef1e;       //RAM[0x66]: 206e LOAD  00 6e // REG[0x00] <- 0xef28
    RAM[0xef18] = 0x00030000;           RAM[0xef19] = 0x0000fc05;       //RAM[0x68]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xef1a] = 0x000200fd;           RAM[0xef1b] = 0x0000ef20;       //RAM[0x6a]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xef1c] = 0x000b0000;           RAM[0xef1d] = 0x0000fbec;       //RAM[0x6c]: b0a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xef1e] = 0x000b0000;           RAM[0xef1f] = 0x0000eece;       //RAM[0x72]: b074 JUMP  00 74 // GEQ
    RAM[0xef20] = 0x00020000;           RAM[0xef21] = 0x00000000;       //RAM[0x7a]: 2000 LOAD  00 00 // REG[0x00] <- 00
    RAM[0xef22] = 0x000b0004;           RAM[0xef23] = 0x0000ef28;       //RAM[0x7c]: b482 JUMP  04 82 // if (REG[0x00] == REG[0x04]) {p <- 0x82;}
    RAM[0xef24] = 0x00020004;           RAM[0xef25] = 0x00000000;       //RAM[0x7e]: 2400 LOAD  04 00 // REG[0x04] <- 00
    RAM[0xef26] = 0x000b0000;           RAM[0xef27] = 0x0000fbda;       //RAM[0x80]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xef28] = 0x00020004;           RAM[0xef29] = 0x00000001;       //RAM[0x82]: 2401 LOAD  04 01 // REG[0x04] <- 01
    RAM[0xef2a] = 0x000b0000;           RAM[0xef2b] = 0x0000fbda;       //RAM[0x84]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    

    //MOD
    RAM[0xef2c] = 0x0003000f;          RAM[0xef2d] = 0x000000f6;       //RAM[0x4a]: 3ff6 STORE 0f f6 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef2e] = 0x0001000c;          RAM[0xef2f] = 0x000000f6;       //RAM[0x4c]: 1cf6 LOAD  02 f6 // REG[0x0c] <- RAM[0xf6]
    RAM[0xef30] = 0x00020000;          RAM[0xef31] = 0x0000ef38;       //RAM[0x50]: 2058 LOAD  00 58 // REG[0x00] <- 58
    RAM[0xef32] = 0x00030000;          RAM[0xef33] = 0x0000fc05;       //RAM[0x52]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xef34] = 0x000200fd;          RAM[0xef35] = 0x0000ef3a;       //RAM[0x54]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xef36] = 0x000b0000;          RAM[0xef37] = 0x0000fbec;       //RAM[0x56]: 30a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xef38] = 0x000b0000;          RAM[0xef39] = 0x0000efa6;       //RAM[0x5c]: b038 JUMP  00 38 // DIV
    RAM[0xef3a] = 0x0003000c;          RAM[0xef3b] = 0x000000f6;       //RAM[0x64]: 3cf6 STORE 0c f6 // RAM[0xf6] <- REG[0x0c]
    RAM[0xef3c] = 0x0001000f;          RAM[0xef3d] = 0x000000f6;       //RAM[0x66]: 1ff6 LOAD  0f f6 // REG[0x0f] <- RAM[0xf6]
    RAM[0xef3e] = 0x0003000e;          RAM[0xef3f] = 0x000000f5;       //RAM[0x64]: 3ef6 STORE 0e f5 // RAM[0xf5] <- REG[0x0e]
    RAM[0xef40] = 0x00030004;          RAM[0xef41] = 0x000000f7;       //RAM[0x68]: 34f7 STORE 04 f7 // RAM[0xf7] <- REG[0x04]
    RAM[0xef42] = 0x0001000e;          RAM[0xef43] = 0x000000f7;       //RAM[0x6a]: 1ef7 LOAD  0e f7 // REG[0x0e] <- RAM[0xf7]
    RAM[0xef44] = 0x00020000;          RAM[0xef45] = 0x0000ef4c;       //RAM[0x6e]: 2076 LOAD  00 76 // REG[0x00] <- 76
    RAM[0xef46] = 0x00030000;          RAM[0xef47] = 0x0000fc05;       //RAM[0x70]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xef48] = 0x000200fd;          RAM[0xef49] = 0x0000ef4e;       //RAM[0x72]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xef4a] = 0x000b0000;          RAM[0xef4b] = 0x0000fbec;       //RAM[0x74]: 30a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xef4c] = 0x000b0000;          RAM[0xef4d] = 0x0000ef8e;       //RAM[0x7a]: b05a JUMP  00 64 // MULT
    RAM[0xef4e] = 0x00030004;          RAM[0xef4f] = 0x000000f7;       //RAM[0x64]: 34f6 STORE 04 f5 // RAM[0xf5] <- REG[0x04]
    RAM[0xef50] = 0x0001000f;          RAM[0xef51] = 0x000000f7;       //RAM[0x66]: 1ff5 LOAD  0f f5 // REG[0x0e] <- RAM[0xf5]
    RAM[0xef52] = 0x00020000;          RAM[0xef53] = 0x0000ef5a;       //RAM[0x6e]: 2076 LOAD  00 76 // REG[0x00] <- 76
    RAM[0xef54] = 0x00030000;          RAM[0xef55] = 0x0000fc05;       //RAM[0x70]: 30a7 STORE 00 a7 // RAM[0xa7] <- REG[0x00]
    RAM[0xef56] = 0x000200fd;          RAM[0xef57] = 0x0000ef5c;       //RAM[0x72]: 29a1 LOAD 09 a1 // RAM[0xa1] <- REG[0x09]
    RAM[0xef58] = 0x000b0000;          RAM[0xef59] = 0x0000fbec;       //RAM[0x74]: 30a0 JUMP  00 a0 // if (REG[0x00] == REG[0x00]) {p <- 0xa0;}
    RAM[0xef5a] = 0x000b0000;          RAM[0xef5b] = 0x0000ef84;       //RAM[0x7a]: b05a JUMP  00 64 // NEG
    RAM[0xef5c] = 0x0001000f;          RAM[0xef5d] = 0x000000f5;       //RAM[0x66]: 1ff5 LOAD  0f f5 // REG[0x0e] <- RAM[0xf5]
    RAM[0xef5e] = 0x00050004;          RAM[0xef5f] = 0x000f0004;       //RAM[0x30]: 5441 ADD   04 f4 // REG[0x04] <- REG[0x0f] + REG[0x04]
    RAM[0xef60] = 0x000b0000;          RAM[0xef61] = 0x0000fbda;       //RAM[0x84]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x0f]) {p <- 0xf8;}
    
    //NEQ
    RAM[0xef62] = 0x0003000f;           RAM[0xef63] = 0x000000f6;      //RAM[0x2a]: 3ff6 STORE 0f f6 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef64] = 0x00010000;           RAM[0xef65] = 0x000000f6;      //RAM[0x2c]: 10f6 LOAD  00 f6 // REG[0x00] <- RAM[0xf6]
    RAM[0xef66] = 0x000b000e;           RAM[0xef67] = 0x0000ef68;      //RAM[0x2e]: be30 JUMP  0e 30 // if (REG[0x00] == REG[0x0e]) {p <- 0x30;}
    RAM[0xef68] = 0x00020004;           RAM[0xef69] = 0x00000001;      //RAM[0x30]: 2401 LOAD  04 01 // REG[0x04] <- 01
    RAM[0xef6a] = 0x000b0000;           RAM[0xef6b] = 0x0000fbda;      //RAM[0x32]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xef6c] = 0x00020004;           RAM[0xef6d] = 0x00000000;      //RAM[0x34]: 2400 LOAD  04 00 // REG[0x04] <- 00
    RAM[0xef6e] = 0x000b0000;           RAM[0xef6f] = 0x0000fbda;      //RAM[0x36]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    
    //EQL
    RAM[0xef70] = 0x0003000f;           RAM[0xef71] = 0x000000f6;      //RAM[0x2a]: 3fF6 STORE 0f f6 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef72] = 0x00010000;           RAM[0xef73] = 0x000000f6;      //RAM[0x2c]: 10f6 LOAD  00 f6 // REG[0x00] <- RAM[0xf6]
    RAM[0xef74] = 0x000b000e;           RAM[0xef75] = 0x0000ef7a;      //RAM[0x2e]: be34 JUMP  0e 34 // if (REG[0x00] == REG[0x0e]) {p <- 0x34;}
    RAM[0xef76] = 0x00020004;           RAM[0xef77] = 0x00000000;      //RAM[0x30]: 2400 LOAD  04 00 // REG[0x04] <- 00
    RAM[0xef78] = 0x000b0000;           RAM[0xef79] = 0x0000fbda;      //RAM[0x32]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xef7a] = 0x00020004;           RAM[0xef7b] = 0x00000001;      //RAM[0x34]: 2400 LOAD  04 01 // REG[0x04] <- 01
    RAM[0xef7c] = 0x000b0000;           RAM[0xef7d] = 0x0000fbda;      //RAM[0x36]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}

    //ODD
    RAM[0xef7e] = 0x0002000e;          RAM[0xef7f] = 0x00000001;       //RAM[0x32]: 2e01 LOAD  0e 01 // REG[0x0e] <- 01
    RAM[0xef80] = 0x00080004;          RAM[0xef81] = 0x000e000f;       //RAM[0x34]: 84ef AND   04 ef // REG[0x04] <- REG[0x0e] && REG[0x0f]
    RAM[0xef82] = 0x000b0000;          RAM[0xef83] = 0x0000fbda;       //RAM[0x36]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    
    //NEG
    RAM[0xef84] = 0x0002000e;          RAM[0xef85] = 0x00000001;       //RAM[0x2e]: 2e01 LOAD  0e 01 // REG[0x0e] <- 01
    RAM[0xef86] = 0x00020002;          RAM[0xef87] = 0xffffffff;       //RAM[0x30]: 22ff LOAD  02 ff // REG[0x02] <- ff
    RAM[0xef88] = 0x00090004;          RAM[0xef89] = 0x0002000f;       //RAM[0x32]: 942f XOR   04 2f // REG[0x04] <- REG[0x02] XOR REG[0x0f]
    RAM[0xef8a] = 0x00050004;          RAM[0xef8b] = 0x0004000e;       //RAM[0x34]: 544e ADD   04 4e // REG[0x04] <- REG[0x04] + REG[0x0e]
    RAM[0xef8c] = 0x000b0000;          RAM[0xef8d] = 0x0000fbda;       //RAM[0x36]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x0f]) {p <- 0xf8;}
    
    //MULT
    RAM[0xef8e] = 0x0003000f;          RAM[0xef8f] = 0x000000f7;       //RAM[0x20]: 3ff7 STORE 0f f7 // RAM[0xf7] <- REG[0x0f]
    RAM[0xef90] = 0x0003000e;          RAM[0xef91] = 0x000000f6;       //RAM[0x22]: 3ef6 STORE 0e f6 // RAM[0xf6] <- REG[0x0e]
    RAM[0xef92] = 0x00020002;          RAM[0xef93] = 0x00000001;       //RAM[0x24]: 2201 LOAD  02 01 // REG[0x02] <- 01
    RAM[0xef94] = 0x00020003;          RAM[0xef95] = 0x00000001;       //RAM[0x26]: 2301 LOAD  03 01 // REG[0x03] <- 01
    RAM[0xef96] = 0x00010004;          RAM[0xef97] = 0x000000f6;       //RAM[0x28]: 14f6 LOAD  04 f6 // REG[0x04] <- RAM[0xf6]
    RAM[0xef98] = 0x00010000;          RAM[0xef99] = 0x000000f7;       //RAM[0x2a]: 10f7 LOAD  00 f7 // REG[0x00] <- RAM[0xf7]
    RAM[0xef9a] = 0x00010001;          RAM[0xef9b] = 0x000000f6;       //RAM[0x2c]: 11f6 LOAD  01 f6 // REG[0x01] <- RAM[0xf6]
    RAM[0xef9c] = 0x000b0002;          RAM[0xef9d] = 0x0000fbda;       //RAM[0x2e]: b2f8 JUMP  02 f8 // if (REG[0x00] == REG[0x02]) {p <- 0xf8;}
    RAM[0xef9e] = 0x00050004;          RAM[0xef9f] = 0x00040001;       //RAM[0x30]: 5441 ADD   04 41 // REG[0x04] <- REG[0x04] + REG[0x01]
    RAM[0xefa0] = 0x00050002;          RAM[0xefa1] = 0x00020003;       //RAM[0x32]: 5223 ADD   02 23 // REG[0x02] <- REG[0x02] + REG[0x03]
    RAM[0xefa2] = 0x00020000;          RAM[0xefa3] = 0x00000001;       //RAM[0x34]: 2001 LOAD  00 01 // REG[0x00] <- 01
    RAM[0xefa4] = 0x000b0003;          RAM[0xefa5] = 0x0000ef98;       //RAM[0x36]: b32a JUMP  03 2a // if (REG[0x00] == REG[0x03]) {p <- 0x2a;}

    //DIV
    RAM[0xefa6] = 0x0003000f;          RAM[0xefa7] = 0x000000f6;       //RAM[0x38]: 3ff6 STORE 0f f6 // RAM[0xf6] <- REG[0x0f]
    RAM[0xefa8] = 0x0003000e;          RAM[0xefa9] = 0x000000f7;       //RAM[0x3a]: 3ef7 STORE 0e f7 // RAM[0xf7] <- REG[0x0e]
    RAM[0xefaa] = 0x00020001;          RAM[0xefab] = 0x00000001;       //RAM[0x3c]: 2101 LOAD  01 01 // REG[0x01] <- 01
    RAM[0xefac] = 0x00020003;          RAM[0xefad] = 0x00000001;       //RAM[0x3e]: 2301 LOAD  03 01 // REG[0x03] <- 01
    RAM[0xefae] = 0x00010002;          RAM[0xefaf] = 0x000000f6;       //RAM[0x40]: 12f6 LOAD  02 f6 // REG[0x02] <- RAM[0xf6]
    RAM[0xefb0] = 0x0005000f;          RAM[0xefb1] = 0x000f0002;       //RAM[0x42]: 5ff2 ADD   0f f2 // REG[0x0f] <- REG[0x0f] + REG[0x02] 
    RAM[0xefb2] = 0x00020000;          RAM[0xefb3] = 0x0000efba;       //RAM[0x46]: 20efb0 LOAD  00 efb0 // REG[0x00] <- efb0
    RAM[0xefb4] = 0x00030000;          RAM[0xefb5] = 0x0000fc05;       //RAM[0x48]: 30fc05 STORE 00 fc05 // RAM[0xfc05] <- REG[0x00]
    RAM[0xefb6] = 0x000200fd;          RAM[0xefb7] = 0x0000efbc;       //RAM[ 0xc]: 2c1c LOAD  0c 16 //retorno
    RAM[0xefb8] = 0x000b0000;          RAM[0xefb9] = 0x0000fbec;       //RAM[0x4c]: b0fbe8 JUMP  00 fbe8 // if (REG[0x00] == REG[0x00]) {p <- 0xfbe8;}
    
    RAM[0xefba] = 0x000b0000;          RAM[0xefbb] = 0x0000efd8;       //RAM[0x52]: b0efd6 JUMP  00 efd6 // GTR
    RAM[0xefbc] = 0x00020000;          RAM[0xefbd] = 0x00000000;       //RAM[0x5a]: 2000 LOAD  00 00 // REG[0x00] <- 00
    RAM[0xefbe] = 0x000b0004;          RAM[0xefbf] = 0x0000efc4;       //RAM[0x5c]: b4efc4 JUMP  04 efc4 // if (REG[0x00] == REG[0x04]) {p <- 0xefc4;}
    RAM[0xefc0] = 0x00050003;          RAM[0xefc1] = 0x00030001;       //RAM[0x5e]: 5331 ADD   03 31 // REG[0x03] <- REG[0x03] + REG[0x01] 
    RAM[0xefc2] = 0x000b0000;          RAM[0xefc3] = 0x0000efae;       //RAM[0x60]: b0efae JUMP  00 efae // if (REG[0x00] == REG[0x00]) {p <- 0xefa2;}
    RAM[0xefc4] = 0x00010000;          RAM[0xefc5] = 0x000000f7;       //RAM[0x62]: 10f7 LOAD  00 f7 // REG[0x00] <- RAM[0xf7]
    RAM[0xefc6] = 0x000b000f;          RAM[0xefc7] = 0x0000efce;       //RAM[0x64]: bfefce JUMP  0f efce // if (REG[0x00] == REG[0x0f]) {p <- 0xefce;}
    RAM[0xefc8] = 0x00030003;          RAM[0xefc9] = 0x000000f7;       //RAM[0x66]: 33f7 STORE 03 f7 // RAM[0xf7] <- REG[0x03]
    RAM[0xefca] = 0x00010004;          RAM[0xefcb] = 0x000000f7;       //RAM[0x68]: 14f7 LOAD  02 f7 // REG[0x04] <- RAM[0xf7]
    RAM[0xefcc] = 0x000b0000;          RAM[0xefcd] = 0x0000fbda;       //RAM[0x6a]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xefce] = 0x00050003;          RAM[0xefcf] = 0x00030001;       //RAM[0x6c]: 5331 ADD   03 31 // REG[0x03] <- REG[0x03] + REG[0x01] 
    RAM[0xefd0] = 0x00030003;          RAM[0xefd1] = 0x000000f7;       //RAM[0x6e]: 33f7 STORE 03 f7 // RAM[0xf7] <- REG[0x03]
    RAM[0xefd2] = 0x00010004;          RAM[0xefd3] = 0x000000f7;       //RAM[0x70]: 14f7 LOAD  04 f7 // REG[0x04] <- RAM[0xf7]
    RAM[0xefd4] = 0x000b0000;          RAM[0xefd5] = 0x0000fbda;       //RAM[0x72]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x0f]) {p <- 0xf8;}


    //GTR
    RAM[0xefd8] = 0x0003000f;          RAM[0xefd9] = 0x000000f5;       //RAM[0x74]: 3ff5 STORE 0f f5 // RAM[0xf5] <- REG[0x0f]
    RAM[0xefda] = 0x00010000;          RAM[0xefdb] = 0x000000f5;       //RAM[0x76]: 10f5 LOAD  00 f5 // REG[0x00] <- RAM[0xf5]
    RAM[0xefdc] = 0x0003000e;          RAM[0xefdd] = 0x000000f7;       //RAM[0x7a]: 3ef7 STORE 0e f7 // RAM[0xf8] <- REG[0x0e]
    RAM[0xefde] = 0x000b000e;          RAM[0xefdf] = 0x0000effa;       //RAM[0x78]: be JUMP  0e  // if (REG[0x00] == REG[0x0e]) {p <- 0xeff6;}
    RAM[0xefe0] = 0x00020000;          RAM[0xefe1] = 0x00000001;       //RAM[0x7c]: 2001 LOAD  00 01 // REG[0x00] <- 01
    RAM[0xefe2] = 0x000a000f;          RAM[0xefe3] = 0x000f001f;       //RAM[0x7e]: aff7 ROT   0f f7 
    RAM[0xefe4] = 0x000a000e;          RAM[0xefe5] = 0x000e001f;       //RAM[0x80]: aff7 ROT   0f e7 
    RAM[0xefe6] = 0x00080002;          RAM[0xefe7] = 0x0000000f;       //RAM[0x82]: 820f AND   02 0f // REG[0x02] <- REG[0x00] && REG[0x0f]
    RAM[0xefe8] = 0x00080004;          RAM[0xefe9] = 0x0000000e;       //RAM[0x86]: 820e AND   04 0e // REG[0x04] <- REG[0x00] && REG[0x0e]
    RAM[0xefea] = 0x0009000d;          RAM[0xefeb] = 0x00020004;       //RAM[0x32]: 9d24 XOR   0d 24 // REG[0x0d] <- REG[0x02] XOR REG[0x04]
    
    RAM[0xefec] = 0x000b000d;          RAM[0xefed] = 0x0000eff0;       //RAM[0x84]: bdeff6 JUMP  0d eff6 // if (REG[0x00] == REG[0x02]) {p <- 0xeff6;}
    RAM[0xefee] = 0x000b0000;          RAM[0xefef] = 0x0000efe2;       //RAM[0x8a]: b0efe0 JUMP  00 efe2 // if (REG[0x00] == REG[0x00]) {p <- 0xefe0;}
    RAM[0xeff0] = 0x000b0002;          RAM[0xeff1] = 0x0000effa;       //RAM[0x88]: b2efee JUMP  02 efee // if (REG[0x00] == REG[0x02]) {p <- 0xefee;}
    RAM[0xeff2] = 0x00020004;          RAM[0xeff3] = 0x00000001;       //RAM[0x8c]: 2401 LOAD  04 01 // REG[0x04] <- 01
    RAM[0xeff4] = 0x0001000f;          RAM[0xeff5] = 0x000000f5;       //RAM[0x8e]: 1ff5 LOAD  0f f5 // REG[0x0f] <- RAM[0xf5]
    RAM[0xeff6] = 0x0001000e;          RAM[0xeff7] = 0x000000f7;       //RAM[0x90]: 1ef7 LOAD  0e f7 // REG[0x0e] <- RAM[0xf7]
    RAM[0xeff8] = 0x000b0000;          RAM[0xeff9] = 0x0000fbda;       //RAM[0x92]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    RAM[0xeffa] = 0x00020004;          RAM[0xeffb] = 0x00000000;       //RAM[0x98]: 2400 LOAD  04 00 // REG[0x04] <- 00
    RAM[0xeffc] = 0x0001000f;          RAM[0xeffd] = 0x000000f5;       //RAM[0x9a]: 1ff5 LOAD  0f f5 // REG[0x0f] <- RAM[0xf5]
    RAM[0xeffe] = 0x0001000e;          RAM[0xefff] = 0x000000f7;       //RAM[0x9c]: 1ef7 LOAD  0e f7 // REG[0x0e] <- RAM[0xf7]
    RAM[0xf000] = 0x000b0000;          RAM[0xf001] = 0x0000fbda;       //RAM[0x9e]: b0f8 JUMP  00 f8 // if (REG[0x00] == REG[0x00]) {p <- 0xf8;}
    
    //ff = registrador de topo da pilha
    //fe = registrador para base da pilha
    //fd = registrador para retorno
    //fb = registrador para incremento do topo e base
    //fa = registrador para decremento do topo e base
    //f9 = registrador para jump
    
    //RET
    RAM[0xfbda] = 0x00020000;          RAM[0xfbdb] = 0xffffffff;       //RAM[0x74]: 3ff5 STORE 0f f5 // RAM[0xf5] <- REG[0x0f]
    RAM[0xfbdc] = 0x00050000;          RAM[0xfbdd] = 0x00fe0000;       //RAM[0x74]: 3ff5 STORE 0f f5 // RAM[0xf5] <- REG[0x0f]
    RAM[0xfbde] = 0x00030000;          RAM[0xfbdf] = 0x0000fbeb;       //RAM[0x84]: b2eff6 JUMP  02 eff6 // if (REG[0x00] == REG[0x02]) {p <- 0xeff6;}
    RAM[0xfbe0] = 0x000300f1;          RAM[0xfbe1] = 0x0000fbe3;
    RAM[0xfbe2] = 0x0001000f;
    RAM[0xfbe4] = 0x000500fe;          RAM[0xfbe5] = 0x00fe00fb;        // reg[fe] <- reg[fe] + reg[fb] // base
    RAM[0xfbe6] = 0x000500f1;          RAM[0xfbe7] = 0x00f100fb;        // reg[f1] <- reg[f1] + reg[f8] // parametro
    RAM[0xfbe8] = 0x000500ff;          RAM[0xfbe9] = 0x00ff00fb;        // reg[ff] <- reg[ff] + reg[fb] // topo
    RAM[0xfbea] = 0x000b0000;              // return
    
    //INT
    RAM[0xfbec] = 0x00020000;          RAM[0xfbed] = 0x0000fc07;       //RAM[0x74]: 3ff5 STORE 0f f5 // RAM[0xf5] <- REG[0x0f]
    RAM[0xfbee] = 0x000b00ff;          RAM[0xfbef] = 0x0000fbf4;       //RAM[0x84]: b2eff6 JUMP  02 eff6 // if (REG[0x00] == REG[0x02]) {p <- 0xeff6;}
    RAM[0xfbf0] = 0x000500fe;          RAM[0xfbf1] = 0x00fe00fa;        // reg[fe] <- reg[fe] + reg[fb] // base
    RAM[0xfbf2] = 0x000500f1;          RAM[0xfbf3] = 0x00f100fa;        // reg[f1] <- reg[f1] + reg[f8] // parametro
    RAM[0xfbf4] = 0x000500ff;          RAM[0xfbf5] = 0x00ff00fa;        // reg[ff] <- reg[ff] + reg[fb] // topo
    RAM[0xfbf6] = 0x000300fe;          RAM[0xfbf7] = 0x0000fc03;        //return
    RAM[0xfbf8] = 0x000300f1;          RAM[0xfbf9] = 0x0000fbff;        //parametroo
    RAM[0xfbfa] = 0x000300ff;          RAM[0xfbfb] = 0x0000fc01;        //parametroo
    RAM[0xfbfc] = 0x000b0000;          RAM[0xfbfd] = 0x0000fbfe;        //save stack
    
    //Save STACK
    RAM[0xfbfe] = 0x0003000f;            //RAM[0x2c]: 3cdf STORE 0c parametroo
    RAM[0xfc00] = 0x0003000e;            //RAM[0x2c]: 3cdf STORE 0c parametroo
    RAM[0xfc02] = 0x000300fd;            //RAM[0x2c]: 3cdf STORE 0c retorno
    RAM[0xfc04] = 0x000b0000;           //posicao funcao      //JUMP funcao
    
    //STACK
  
    RAM[0xfc06] = 0x000b0000;
    RAM[0xfc0a] = 0x000b0000;
    RAM[0xfc0e] = 0x000b0000;
    RAM[0xfc12] = 0x000b0000;
    RAM[0xfc16] = 0x000b0000;
    RAM[0xfc1a] = 0x000b0000;
    RAM[0xfc1e] = 0x000b0000;
    RAM[0xfc12] = 0x000b0000;
    RAM[0xfc16] = 0x000b0000;
    RAM[0xfc1a] = 0x000b0000;
    RAM[0xfc1e] = 0x000b0000;
    RAM[0xfc22] = 0x000b0000;
    RAM[0xfc26] = 0x000b0000;
    RAM[0xfc2a] = 0x000b0000;


    printf("%5s %5s %5s %5s","op","opr1","opr2","opr3");
    for(int h = 0; h <16; h++) {
        printf(" %8x", h);
    }
    printf("\n");
    printf("----- ----- ----- -----");
    for(int h = 0; h <16; h++) {
        printf(" --------");
    }
    printf("\n");
    int p = 0;
    
    
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
        for (int h = 0; h < 16; h++) {
            int aux = reg[h];
            /*for(int j = 7; j > -1; j--) {
                if ( (aux/pow(2, j)) >= 1 ) { aux -= pow(2, j); printf("1"); }
                else { printf("0"); }
            }
            printf(" ");
            //*/printf(" %8d", reg[h]);
        }
        printf("\n");
        
    } while (p != 0);
    printf("----- ----- ----- -----");
    for(int h = 0; h <16; h++) {
        printf(" --------");
    }
    printf("\n");
    printf("%5s %5s %5s %5s","op","opr1","opr2","opr3");
    for(int h = 0; h <16; h++) {
        printf(" %8x", h);
    }
    printf("\nend                     registradores\n");
}

uint32_t sum_comp2(uint32_t val1, int val2){
    uint32_t sinal1 = val1 >> 31;
    uint32_t sinal2 = val2 >> 31;
    int result;
    if(sinal1 == 0){
        if(sinal2 == 0){
            result = val1 + val2;
            if(result > 2147483647){
                result -= 2147483647;
            }
        }
        else{
            result = val1 - (4294967296 - val2 );
            if(result < 0){
                result *= -1;
                result = 4294967296 - result;
            }
        }
    }
    else{
        if(sinal2 == 0){
            result =  val2 - (4294967296 - val1);
            if(result < 0){
                result *= -1;
                result = 4294967296 - result;
            }
        }
        else{
            result = (4294967296 - val1) + (4294967296 - val2);
            result = 4294967296 - result;
        }
    }
    return result;
}
uint32_t sum_flut(uint32_t val1, int val2){
    uint16_t sinal1, sinal2, expv1, expv2, mant1, mant2, result, soma;
    sinal1 = val1>>15;
    sinal2 = val2>>15;
    expv1 = val1<<1; expv1 = expv1>>5;
    expv2 = val2<<1; expv2 = expv2>>5;
    mant1 = val1<<4; mant1 = mant1>>4;
    mant2 = val2<<4; mant2 = mant2>>4;
    
    if(expv1 != expv2){
        int aux;
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
            result = sinal1<<7;
            result += expv1<<4;
            result += soma;
            return result;
        }
        else{
            soma = abs(mant1 - mant2);
            if(mant2 > mant1) { result = sinal2<<7; }
            else { result = sinal1<<7;}
            result += expv1<<4;
            result += soma;
            return result;
        }
    }
    else{
        if(sinal2 == 0){
            soma = abs(mant1 - mant2);
            if(mant1 > mant2) { result = sinal1<<7; }
            else { result = sinal2<<7;}
            result += expv1<<4;
            result += soma;
            return result;
        }
        else{
            soma = abs(mant1 + mant2);
            result = sinal1<<7;
            result += expv1<<4;
            result += soma;
            return result;
        }
    }
}

uint32_t rot(uint32_t val1, uint32_t val2){
    uint32_t a = val1>>val2 ;
    uint32_t b = val1<<(32-val2);
    uint32_t c = a+b;
    return c;
}
uint32_t trans(uint32_t val1, uint32_t val2){
    uint32_t a1 = val1<<16;
    uint32_t b = a1 + val2;
    return b;
}


Tinstruction transformInstruction(uint32_t a, uint32_t b){
    Tinstruction result;
    result.op = a>>16;
    result.opr1 = a & 65535; 
    result.opr2 = b>>16;
    result.opr3 = b & 65535;
    return result;
}
char * getInstructionName(int inst){
    return instructionString[inst - 1];
}