#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>
#include<math.h>

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
Tinstruction transformInstruction(uint32_t a, uint32_t b);


int main(){
	uint32_t a = 0x00000005;
	uint32_t RAM[65536]; // ffff
    uint32_t reg[65536]; // registradores
    Tinstruction i;
    printf("start                   \n");
    // Parametros
    
    //operador&operando1        operando2&operando3

    //LEQ
    RAM[0xeef2] = 0x00020000;           RAM[0xeef3] = 0x0000eefa;       //RAM[0xeef2]: LOAD  00 eefa // REG[0x00] <- eefa
    RAM[0xeef4] = 0x00030000;           RAM[0xeef5] = 0x0000fc07;       //RAM[0xeef4]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xeef6] = 0x000200fd;           RAM[0xeef7] = 0x0000eefc;       //RAM[0xeef6]: LOAD  fd eefc // REG[0xfd] <- eefc
    RAM[0xeef8] = 0x000b0000;           RAM[0xeef9] = 0x0000fbea;       //RAM[0xeef8]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xeefa] = 0x000b0000;           RAM[0xeefb] = 0x0000efd8;       //RAM[0xeefa]: JUMP  00 efd8 // if (REG[0x00] == REG[0x00]) {p <- 0xefd8;} // GTR
    RAM[0xeefc] = 0x00020000;           RAM[0xeefd] = 0x00000000;       //RAM[0xeefc]: LOAD  00 00   // REG[0x00] <- 00
    RAM[0xeefe] = 0x000b0004;           RAM[0xeeff] = 0x0000ef12;       //RAM[0xeefe]: JUMP  04 ef12 // if (REG[0x00] == REG[0x04]) {p <- 0xef12;}
    RAM[0xef00] = 0x00020000;           RAM[0xef01] = 0x0000ef08;       //RAM[0xef00]: LOAD  00 ef08 // REG[0x00] <- ef08
    RAM[0xef02] = 0x00030000;           RAM[0xef03] = 0x0000fc07;       //RAM[0xef02]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef04] = 0x000200fd;           RAM[0xef05] = 0x0000ef0a;       //RAM[0xef04]: LOAD  fd ef0a // REG[0xfd] <- ef0a
    RAM[0xef06] = 0x000b0000;           RAM[0xef07] = 0x0000fbea;       //RAM[0xef06]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef08] = 0x000b0000;           RAM[0xef09] = 0x0000ef70;       //RAM[0xef08]: JUMP  00 ef70 // if (REG[0x00] == REG[0x00]) {p <- 0xef70;} // EQL
    RAM[0xef0a] = 0x00020000;           RAM[0xef0b] = 0x00000001;       //RAM[0xef0a]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xef0c] = 0x000b0004;           RAM[0xef0d] = 0x0000ef12;       //RAM[0xef0c]: JUMP  04 ef12 // if (REG[0x00] == REG[0x04]) {p <- 0xef12;}
    RAM[0xef0e] = 0x00020004;           RAM[0xef0f] = 0x00000000;       //RAM[0xef0e]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef10] = 0x000b0000;           RAM[0xef11] = 0x0000fbd2;       //RAM[0xef10]: JUMP  00 fdb2 // if (REG[0x00] == REG[0x00]) {p <- 0xfdb2;}
    RAM[0xef12] = 0x00020004;           RAM[0xef13] = 0x00000001;       //RAM[0xef12]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef14] = 0x000b0000;           RAM[0xef15] = 0x0000fbd2;       //RAM[0xef14]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    
    //LSS
    RAM[0xef16] = 0x00020000;           RAM[0xef17] = 0x0000ef1e;       //RAM[0xef16]: LOAD  00 ef1e // REG[0x00] <- 0xef1e
    RAM[0xef18] = 0x00030000;           RAM[0xef19] = 0x0000fc07;       //RAM[0xef18]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef1a] = 0x000200fd;           RAM[0xef1b] = 0x0000ef20;       //RAM[0xef1a]: LOAD  fd ef20 // REG[0xfd] <- ef20
    RAM[0xef1c] = 0x000b0000;           RAM[0xef1d] = 0x0000fbea;       //RAM[0xef1c]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef1e] = 0x000b0000;           RAM[0xef1f] = 0x0000eece;       //RAM[0xef1e]: JUMP  00 eece // if (REG[0x00] == REG[0x00]) {p <- 0xeece;} // GEQ
    RAM[0xef20] = 0x00020000;           RAM[0xef21] = 0x00000000;       //RAM[0xef20]: LOAD  00 00   // REG[0x00] <- 00
    RAM[0xef22] = 0x000b0004;           RAM[0xef23] = 0x0000ef28;       //RAM[0xef22]: JUMP  04 ef28 // if (REG[0x00] == REG[0x04]) {p <- 0xef28;}
    RAM[0xef24] = 0x00020004;           RAM[0xef25] = 0x00000000;       //RAM[0xef24]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef26] = 0x000b0000;           RAM[0xef27] = 0x0000fbd2;       //RAM[0xef26]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xef28] = 0x00020004;           RAM[0xef29] = 0x00000001;       //RAM[0xef28]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef2a] = 0x000b0000;           RAM[0xef2b] = 0x0000fbd2;       //RAM[0xef2a]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    

    //MOD
    RAM[0xef2c] = 0x0003000f;          RAM[0xef2d] = 0x0000fbd0;       //RAM[0xef2c]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef2e] = 0x0001000c;          RAM[0xef2f] = 0x0000fbd0;       //RAM[0xef2e]: LOAD  0c fbd0 // REG[0x0c] <- RAM[0xf6]
    RAM[0xef30] = 0x00020000;          RAM[0xef31] = 0x0000ef38;       //RAM[0xef30]: LOAD  00 ef38 // REG[0x00] <- ef38
    RAM[0xef32] = 0x00030000;          RAM[0xef33] = 0x0000fc07;       //RAM[0xef32]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef34] = 0x000200fd;          RAM[0xef35] = 0x0000ef3a;       //RAM[0xef34]: LOAD  fd ef3a // REG[0xfd] <- ef3a
    RAM[0xef36] = 0x000b0000;          RAM[0xef37] = 0x0000fbea;       //RAM[0xef36]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef38] = 0x000b0000;          RAM[0xef39] = 0x0000efa6;       //RAM[0xef38]: JUMP  00 efa6 // if (REG[0x00] == REG[0x00]) {p <- 0xefa6;} // DIV
    RAM[0xef3a] = 0x0003000c;          RAM[0xef3b] = 0x0000fbd0;       //RAM[0xef3a]: STORE 0c fbd0 // RAM[0xf6] <- REG[0x0c]
    RAM[0xef3c] = 0x0001000f;          RAM[0xef3d] = 0x0000fbd0;       //RAM[0xef3c]: LOAD  0f fbd0 // REG[0x0f] <- RAM[0xf6]
    RAM[0xef3e] = 0x0003000e;          RAM[0xef3f] = 0x0000fbcf;       //RAM[0xef3e]: STORE 0e fbcf // RAM[0xf5] <- REG[0x0e]
    RAM[0xef40] = 0x00030004;          RAM[0xef41] = 0x0000fbd1;       //RAM[0xef40]: STORE 04 fbd1 // RAM[0xf7] <- REG[0x04]
    RAM[0xef42] = 0x0001000e;          RAM[0xef43] = 0x0000fbd1;       //RAM[0xef42]: LOAD  0e fbd1 // REG[0x0e] <- RAM[0xf7]
    RAM[0xef44] = 0x00020000;          RAM[0xef45] = 0x0000ef4c;       //RAM[0xef44]: LOAD  00 ef4c // REG[0x00] <- ef4c
    RAM[0xef46] = 0x00030000;          RAM[0xef47] = 0x0000fc07;       //RAM[0xef46]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef48] = 0x000200fd;          RAM[0xef49] = 0x0000ef4e;       //RAM[0xef48]: LOAD  fd ef4e // REG[0xfd] <- ef4e
    RAM[0xef4a] = 0x000b0000;          RAM[0xef4b] = 0x0000fbea;       //RAM[0xef4a]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef4c] = 0x000b0000;          RAM[0xef4d] = 0x0000ef8e;       //RAM[0xef4c]: JUMP  00 ef8e // if (REG[0x00] == REG[0x00]) {p <- 0xef8e;} // MULT
    RAM[0xef4e] = 0x00030004;          RAM[0xef4f] = 0x0000fbd1;       //RAM[0xef4e]: STORE 04 fbd1 // RAM[0xf7] <- REG[0x04]
    RAM[0xef50] = 0x0001000f;          RAM[0xef51] = 0x0000fbd1;       //RAM[0xef50]: LOAD  0f fbd1 // REG[0x0f] <- RAM[0xf7]
    RAM[0xef52] = 0x00020000;          RAM[0xef53] = 0x0000ef5a;       //RAM[0xef52]: LOAD  00 ef5a // REG[0x00] <- ef5a
    RAM[0xef54] = 0x00030000;          RAM[0xef55] = 0x0000fc07;       //RAM[0xef54]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xef56] = 0x000200fd;          RAM[0xef57] = 0x0000ef5c;       //RAM[0xef56]: LOAD  fd ef5c // REG[0xfd] <- ef5c
    RAM[0xef58] = 0x000b0000;          RAM[0xef59] = 0x0000fbea;       //RAM[0xef58]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    RAM[0xef5a] = 0x000b0000;          RAM[0xef5b] = 0x0000ef84;       //RAM[0xef5a]: JUMP  00 ef84 // if (REG[0x00] == REG[0x00]) {p <- 0xef84;} // NEG
    RAM[0xef5c] = 0x0001000f;          RAM[0xef5d] = 0x0000fbcf;       //RAM[0xef5c]: LOAD  0f fbcf // REG[0x0f] <- RAM[0xf5]
    RAM[0xef5e] = 0x00050004;          RAM[0xef5f] = 0x000f0004;       //RAM[0xef5e]: ADD   04 f4   // REG[0x04] <- REG[0x0f] + REG[0x04]
    RAM[0xef60] = 0x000b0000;          RAM[0xef61] = 0x0000fbd2;       //RAM[0xef60]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x0f]) {p <- 0xfbd2;}
    
    //NEQ
    RAM[0xef62] = 0x0003000f;           RAM[0xef63] = 0x0000fbd0;      //RAM[0xef62]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef64] = 0x00010000;           RAM[0xef65] = 0x0000fbd0;      //RAM[0xef64]: LOAD  00 fbd0 // REG[0x00] <- RAM[0xf6]
    RAM[0xef66] = 0x000b000e;           RAM[0xef67] = 0x0000ef68;      //RAM[0xef66]: JUMP  0e ef68 // if (REG[0x00] == REG[0x0e]) {p <- 0xef68;}
    RAM[0xef68] = 0x00020004;           RAM[0xef69] = 0x00000001;      //RAM[0xef68]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef6a] = 0x000b0000;           RAM[0xef6b] = 0x0000fbd2;      //RAM[0xef6a]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xef6c] = 0x00020004;           RAM[0xef6d] = 0x00000000;      //RAM[0xef6c]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef6e] = 0x000b0000;           RAM[0xef6f] = 0x0000fbd2;      //RAM[0xef6e]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    
    //EQL
    RAM[0xef70] = 0x0003000f;           RAM[0xef71] = 0x0000fbd0;      //RAM[0xef70]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xef72] = 0x00010000;           RAM[0xef73] = 0x0000fbd0;      //RAM[0xef72]: LOAD  00 fbd0 // REG[0x00] <- RAM[0xf6]
    RAM[0xef74] = 0x000b000e;           RAM[0xef75] = 0x0000ef7a;      //RAM[0xef74]: JUMP  0e ef7a // if (REG[0x00] == REG[0x0e]) {p <- 0xef7a;}
    RAM[0xef76] = 0x00020004;           RAM[0xef77] = 0x00000000;      //RAM[0xef76]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xef78] = 0x000b0000;           RAM[0xef79] = 0x0000fbd2;      //RAM[0xef78]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xef7a] = 0x00020004;           RAM[0xef7b] = 0x00000001;      //RAM[0xef7a]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xef7c] = 0x000b0000;           RAM[0xef7d] = 0x0000fbd2;      //RAM[0xef7c]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}

    //ODD
    RAM[0xef7e] = 0x0002000e;          RAM[0xef7f] = 0x00000001;       //RAM[0xef7e]: LOAD  0e 01   // REG[0x0e] <- 01
    RAM[0xef80] = 0x00080004;          RAM[0xef81] = 0x000e000f;       //RAM[0xef80]: AND   04 ef   // REG[0x04] <- REG[0x0e] && REG[0x0f]
    RAM[0xef82] = 0x000b0000;          RAM[0xef83] = 0x0000fbd2;       //RAM[0xef82]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    
    //NEG
    RAM[0xef84] = 0x0002000e;          RAM[0xef85] = 0x00000001;       //RAM[0xef84]: LOAD  0e 01   // REG[0x0e] <- 01
    RAM[0xef86] = 0x00020002;          RAM[0xef87] = 0xffffffff;       //RAM[0xef86]: LOAD  02 -1   // REG[0x02] <- -1
    RAM[0xef88] = 0x00090004;          RAM[0xef89] = 0x0002000f;       //RAM[0xef88]: XOR   04 2f   // REG[0x04] <- REG[0x02] XOR REG[0x0f]
    RAM[0xef8a] = 0x00050004;          RAM[0xef8b] = 0x0004000e;       //RAM[0xef8a]: ADD   04 4e   // REG[0x04] <- REG[0x04] + REG[0x0e]
    RAM[0xef8c] = 0x000b0000;          RAM[0xef8d] = 0x0000fbd2;       //RAM[0xef8c]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x0f]) {p <- 0xfbd2;}
    
    //MULT
    RAM[0xef8e] = 0x0003000f;          RAM[0xef8f] = 0x0000fbd1;       //RAM[0xef8e]: STORE 0f fbd1 // RAM[0xf7] <- REG[0x0f]
    RAM[0xef90] = 0x0003000e;          RAM[0xef91] = 0x0000fbd0;       //RAM[0xef90]: STORE 0e fbd0 // RAM[0xf6] <- REG[0x0e]
    RAM[0xef92] = 0x00020002;          RAM[0xef93] = 0x00000001;       //RAM[0xef92]: LOAD  02 01   // REG[0x02] <- 01
    RAM[0xef94] = 0x00020003;          RAM[0xef95] = 0x00000001;       //RAM[0xef94]: LOAD  03 01   // REG[0x03] <- 01
    RAM[0xef96] = 0x00010004;          RAM[0xef97] = 0x0000fbd0;       //RAM[0xef96]: LOAD  04 fbd0 // REG[0x04] <- RAM[0xf6]
    RAM[0xef98] = 0x00010000;          RAM[0xef99] = 0x0000fbd1;       //RAM[0xef98]: LOAD  00 fbd1 // REG[0x00] <- RAM[0xf7]
    RAM[0xef9a] = 0x00010001;          RAM[0xef9b] = 0x0000fbd0;       //RAM[0xef9a]: LOAD  01 fbd0 // REG[0x01] <- RAM[0xf6]
    RAM[0xef9c] = 0x000b0002;          RAM[0xef9d] = 0x0000fbd2;       //RAM[0xef9c]: JUMP  02 fbd2 // if (REG[0x00] == REG[0x02]) {p <- 0xfbd2;}
    RAM[0xef9e] = 0x00050004;          RAM[0xef9f] = 0x00040001;       //RAM[0xef9e]: ADD   04 41   // REG[0x04] <- REG[0x04] + REG[0x01]
    RAM[0xefa0] = 0x00050002;          RAM[0xefa1] = 0x00020003;       //RAM[0xefa0]: ADD   02 23   // REG[0x02] <- REG[0x02] + REG[0x03]
    RAM[0xefa2] = 0x00020000;          RAM[0xefa3] = 0x00000001;       //RAM[0xefa2]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xefa4] = 0x000b0003;          RAM[0xefa5] = 0x0000ef98;       //RAM[0xefa4]: JUMP  03 ef98 // if (REG[0x00] == REG[0x03]) {p <- 0xef98;}

    //DIV
    RAM[0xefa6] = 0x0003000f;          RAM[0xefa7] = 0x0000fbd0;       //RAM[0xefa6]: STORE 0f fbd0 // RAM[0xf6] <- REG[0x0f]
    RAM[0xefa8] = 0x0003000e;          RAM[0xefa9] = 0x0000fbd1;       //RAM[0xefa8]: STORE 0e fbd1 // RAM[0xf7] <- REG[0x0e]
    RAM[0xefaa] = 0x00020001;          RAM[0xefab] = 0x00000001;       //RAM[0xefaa]: LOAD  01 01   // REG[0x01] <- 01
    RAM[0xefac] = 0x00020003;          RAM[0xefad] = 0x00000001;       //RAM[0xefac]: LOAD  03 01   // REG[0x03] <- 01
    RAM[0xefae] = 0x00010002;          RAM[0xefaf] = 0x0000fbd0;       //RAM[0xefae]: LOAD  02 fbd0 // REG[0x02] <- RAM[0xf6]
    RAM[0xefb0] = 0x0005000f;          RAM[0xefb1] = 0x000f0002;       //RAM[0xefb0]: ADD   0f f2   // REG[0x0f] <- REG[0x0f] + REG[0x02] 
    RAM[0xefb2] = 0x00020000;          RAM[0xefb3] = 0x0000efba;       //RAM[0xefb2]: LOAD  00 efba // REG[0x00] <- efba
    RAM[0xefb4] = 0x00030000;          RAM[0xefb5] = 0x0000fc07;       //RAM[0xefb4]: STORE 00 fc07 // RAM[0xfc07] <- REG[0x00]
    RAM[0xefb6] = 0x000200fd;          RAM[0xefb7] = 0x0000efbc;       //RAM[0xefb6]: LOAD  fd efbc // REG[0xfd] <- efbc
    RAM[0xefb8] = 0x000b0000;          RAM[0xefb9] = 0x0000fbea;       //RAM[0xefb8]: JUMP  00 fbea // if (REG[0x00] == REG[0x00]) {p <- 0xfbea;}
    
    RAM[0xefba] = 0x000b0000;          RAM[0xefbb] = 0x0000efd8;       //RAM[0xefba]: JUMP  00 efd8 // if (REG[0x00] == REG[0x00]) {p <- 0xefd8;} // GTR
    RAM[0xefbc] = 0x00020000;          RAM[0xefbd] = 0x00000000;       //RAM[0xefbc]: LOAD  00 00   // REG[0x00] <- 00
    RAM[0xefbe] = 0x000b0004;          RAM[0xefbf] = 0x0000efc4;       //RAM[0xefbe]: JUMP  04 efc4 // if (REG[0x00] == REG[0x04]) {p <- 0xefc4;}
    RAM[0xefc0] = 0x00050003;          RAM[0xefc1] = 0x00030001;       //RAM[0xefc0]: ADD   03 31   // REG[0x03] <- REG[0x03] + REG[0x01] 
    RAM[0xefc2] = 0x000b0000;          RAM[0xefc3] = 0x0000efae;       //RAM[0xefc2]: JUMP  00 efae // if (REG[0x00] == REG[0x00]) {p <- 0xefa2;}
    RAM[0xefc4] = 0x00010000;          RAM[0xefc5] = 0x0000fbd1;       //RAM[0xefc4]: LOAD  00 fbd1 // REG[0x00] <- RAM[0xf7]
    RAM[0xefc6] = 0x000b000f;          RAM[0xefc7] = 0x0000efce;       //RAM[0xefc6]: JUMP  0f efce // if (REG[0x00] == REG[0x0f]) {p <- 0xefce;}
    RAM[0xefc8] = 0x00030003;          RAM[0xefc9] = 0x0000fbd1;       //RAM[0xefc8]: STORE 03 fbd1 // RAM[0xf7] <- REG[0x03]
    RAM[0xefca] = 0x00010004;          RAM[0xefcb] = 0x0000fbd1;       //RAM[0xefca]: LOAD  04 fbd1 // REG[0x04] <- RAM[0xf7]
    RAM[0xefcc] = 0x000b0000;          RAM[0xefcd] = 0x0000fbd2;       //RAM[0xefcc]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xefce] = 0x00050003;          RAM[0xefcf] = 0x00030001;       //RAM[0xefce]: ADD   03 31   // REG[0x03] <- REG[0x03] + REG[0x01] 
    RAM[0xefd0] = 0x00030003;          RAM[0xefd1] = 0x0000fbd1;       //RAM[0xefd0]: STORE 03 fbd1 // RAM[0xf7] <- REG[0x03]
    RAM[0xefd2] = 0x00010004;          RAM[0xefd3] = 0x0000fbd1;       //RAM[0xefd2]: LOAD  04 fbd1 // REG[0x04] <- RAM[0xf7]
    RAM[0xefd4] = 0x000b0000;          RAM[0xefd5] = 0x0000fbd2;       //RAM[0xefd4]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x0f]) {p <- 0xfbd2;}


    //GTR
    RAM[0xefd8] = 0x0003000f;          RAM[0xefd9] = 0x0000fbcf;       //RAM[0xefd8]: STORE 0f fbcf // RAM[0xf5] <- REG[0x0f]
    RAM[0xefda] = 0x00010000;          RAM[0xefdb] = 0x0000fbcf;       //RAM[0xefda]: LOAD  00 fbcf // REG[0x00] <- RAM[0xf5]
    RAM[0xefdc] = 0x0003000e;          RAM[0xefdd] = 0x0000fbd1;       //RAM[0xefdc]: STORE 0e fbd1 // RAM[0xf7] <- REG[0x0e]
    RAM[0xefde] = 0x000b000e;          RAM[0xefdf] = 0x0000effa;       //RAM[0xefde]: JUMP  0e effa // if (REG[0x00] == REG[0x0e]) {p <- 0xeffa;}
    RAM[0xefe0] = 0x00020000;          RAM[0xefe1] = 0x00000001;       //RAM[0xefe0]: LOAD  00 01   // REG[0x00] <- 01
    RAM[0xefe2] = 0x000a000f;          RAM[0xefe3] = 0x000f001f;       //RAM[0xefe2]: ROT   0f 0f1f // REG[0x0f] <- REG[0x0f] >> 1f 
    RAM[0xefe4] = 0x000a000e;          RAM[0xefe5] = 0x000e001f;       //RAM[0xefe4]: ROT   0e 0e1f // REG[0x0e] <- REG[0x0e] >> 1f 
    RAM[0xefe6] = 0x00080002;          RAM[0xefe7] = 0x0000000f;       //RAM[0xefe6]: AND   02 0f   // REG[0x02] <- REG[0x00] && REG[0x0f]
    RAM[0xefe8] = 0x00080004;          RAM[0xefe9] = 0x0000000e;       //RAM[0xefe8]: AND   04 0e   // REG[0x04] <- REG[0x00] && REG[0x0e]
    RAM[0xefea] = 0x0009000d;          RAM[0xefeb] = 0x00020004;       //RAM[0xefea]: XOR   0d 24   // REG[0x0d] <- REG[0x02] XOR REG[0x04]
    
    RAM[0xefec] = 0x000b000d;          RAM[0xefed] = 0x0000eff0;       //RAM[0xefec]: JUMP  0d eff0 // if (REG[0x00] == REG[0x02]) {p <- 0xeff0;}
    RAM[0xefee] = 0x000b0000;          RAM[0xefef] = 0x0000efe2;       //RAM[0xefee]: JUMP  00 efe2 // if (REG[0x00] == REG[0x00]) {p <- 0xefe2;}
    RAM[0xeff0] = 0x000b0002;          RAM[0xeff1] = 0x0000effa;       //RAM[0xeff0]: JUMP  02 efea // if (REG[0x00] == REG[0x02]) {p <- 0xefea;}
    RAM[0xeff2] = 0x00020004;          RAM[0xeff3] = 0x00000001;       //RAM[0xeff2]: LOAD  04 01   // REG[0x04] <- 01
    RAM[0xeff4] = 0x0001000f;          RAM[0xeff5] = 0x0000fbcf;       //RAM[0xeff4]: LOAD  0f fbcf // REG[0x0f] <- RAM[0xf5]
    RAM[0xeff6] = 0x0001000e;          RAM[0xeff7] = 0x0000fbd1;       //RAM[0xeff6]: LOAD  0e fbd1 // REG[0x0e] <- RAM[0xf7]
    RAM[0xeff8] = 0x000b0000;          RAM[0xeff9] = 0x0000fbd2;       //RAM[0xeff8]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}
    RAM[0xeffa] = 0x00020004;          RAM[0xeffb] = 0x00000000;       //RAM[0xeffa]: LOAD  04 00   // REG[0x04] <- 00
    RAM[0xeffc] = 0x0001000f;          RAM[0xeffd] = 0x0000fbcf;       //RAM[0xeffc]: LOAD  0f fbcf // REG[0x0f] <- RAM[0xf5]
    RAM[0xeffe] = 0x0001000e;          RAM[0xefff] = 0x0000fbd1;       //RAM[0xeffe]: LOAD  0e fbd1 // REG[0x0e] <- RAM[0xf7]
    RAM[0xf000] = 0x000b0000;          RAM[0xf001] = 0x0000fbd2;       //RAM[0xf000]: JUMP  00 fbd2 // if (REG[0x00] == REG[0x00]) {p <- 0xfbd2;}

    
    //RET
    RAM[0xfbd2] = 0x00020000;          RAM[0xfbd3] = 0xffffffff;       // RAM[0xfbd2]: LOAD  00 -1   // REG[0x00] <- -1
    RAM[0xfbd4] = 0x00050000;          RAM[0xfbd5] = 0x00fe0000;       // RAM[0xfbd4]: ADD   00 fe00 // REG[0x00] <- REG[0xfe] + REG[0x00]
    RAM[0xfbd6] = 0x00030000;          RAM[0xfbd7] = 0x0000fbe9;       // RAM[0xfbd6]: STORE 00 fbe9 // RAM[0xfbe9] <- REG[0x00]
    RAM[0xfbd8] = 0x000300ff;          RAM[0xfbd9] = 0x0000fbdb;       // RAM[0xfbd8]: STORE ff fbdb // RAM[0xfbdb] <- REG[0xff]
    RAM[0xfbda] = 0x0001000f;                                          // RAM[0xfbda]: LOAD  0f      // REG[0x0f] <- RAM[]
    RAM[0xfbdc] = 0x000300fc;          RAM[0xfbdd] = 0x0000fbdf;       // RAM[0xfbdc]: STORE fc fbdf // RAM[0xfbdf] <- REG[0xfc]
    RAM[0xfbde] = 0x00030004;                                          // RAM[0xfbde]: STORE 04      // RAM[] <- REG[0x04]
    RAM[0xfbe0] = 0x000500fe;          RAM[0xfbe1] = 0x00fe00fb;       // RAM[0xfbe0]: ADD   fe fefb // REG[0xfe] <- REG[0xfe] + REG[0xfb] // base
    RAM[0xfbe2] = 0x000500f1;          RAM[0xfbe3] = 0x00f100fb;       // RAM[0xfbe2]: ADD   f1 f1fb // REG[0xf1] <- REG[0xf1] + REG[0xfb] // parametro
    RAM[0xfbe4] = 0x000500ff;          RAM[0xfbe5] = 0x00ff00fb;       // RAM[0xfbe4]: ADD   ff fffb // REG[0xff] <- REG[0xff] + REG[0xfb] // parametro
    RAM[0xfbe6] = 0x000500fc;          RAM[0xfbe7] = 0x00fc00fb;       // RAM[0xfbe6]: ADD   fc fcfb // REG[0xfc] <- REG[0xfc] + REG[0xfb] // resultado
    RAM[0xfbe8] = 0x000b0000;                                          // RAM[0xfbe8]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    
    //INT
    RAM[0xfbea] = 0x00020000;          RAM[0xfbeb] = 0x00000000;       // RAM[0xfbea]: LOAD  00 00   // REG[0xf0] <- 00
    RAM[0xfbec] = 0x000500fe;          RAM[0xfbed] = 0x00fe00fa;       // RAM[0xfbea]: ADD   fe fefa // REG[0xfe] <- REG[0xfe] + REG[0xfa] // base
    RAM[0xfbee] = 0x000500f1;          RAM[0xfbef] = 0x00f100fa;       // RAM[0xfbea]: ADD   f1 f1fa // REG[0xf1] <- REG[0xf1] + REG[0xfa] // parametro
    RAM[0xfbf0] = 0x000500ff;          RAM[0xfbf1] = 0x00ff00fa;       // RAM[0xfbea]: ADD   ff fffa // REG[0xff] <- REG[0xff] + REG[0xfa] // parametro
    RAM[0xfbf2] = 0x000500fc;          RAM[0xfbf3] = 0x00fc00fa;       // RAM[0xfbea]: ADD   fc fcfa // REG[0xfc] <- REG[0xfc] + REG[0xfa] // resultado
    RAM[0xfbf4] = 0x000300fe;          RAM[0xfbf5] = 0x0000fc03;       // RAM[0xfbea]: STORE fe fc03 // RAM[0xfc03] <- REG[0x04] // return
    RAM[0xfbf6] = 0x000300f1;          RAM[0xfbf7] = 0x0000fc01;       // RAM[0xfbea]: STORE f1 fc01 // RAM[0xfc01] <- REG[0x04] // parametro
    RAM[0xfbf8] = 0x000300ff;          RAM[0xfbf9] = 0x0000fbff;       // RAM[0xfbea]: STORE ff fbff // RAM[0xfbff] <- REG[0x04] // parametro
    RAM[0xfbfa] = 0x000300fc;          RAM[0xfbfb] = 0x0000fc05;       // RAM[0xfbea]: STORE fc fc05 // RAM[0xfc05] <- REG[0x04] // resultado
    RAM[0xfbfc] = 0x000b0000;          RAM[0xfbfd] = 0x0000fbfe;       // RAM[0xfbea]: JUMP  00 fbfe // if (REG[0x00] == REG[0x00]) {p <- 0xfbfe;}
    
    //Save STACK
    RAM[0xfbfe] = 0x0003000f;                                          // RAM[0xfbfe]: STORE 0f      // RAM[0x] <- REG[0x0f]
    RAM[0xfc00] = 0x0003000e;                                          // RAM[0xfc00]: STORE 0e      // RAM[0x] <- REG[0x0e] 
    RAM[0xfc02] = 0x000300fd;                                          // RAM[0xfc02]: STORE fd      // RAM[0x] <- REG[0xfd] 
    RAM[0xfc04] = 0x00030000;                                          // RAM[0xfc04]: STORE 00      // RAM[0x] <- REG[0x00] 
    RAM[0xfc06] = 0x000b0000;                                          // RAM[0xfc06]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    
    //STACK
  
    RAM[0xfc08] = 0x000b0000;                                          // RAM[0xfc08]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc0d] = 0x000b0000;                                          // RAM[0xfc0d]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc12] = 0x000b0000;                                          // RAM[0xfc12]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc17] = 0x000b0000;                                          // RAM[0xfc17]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc1c] = 0x000b0000;                                          // RAM[0xfc1c]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc21] = 0x000b0000;                                          // RAM[0xfc21]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc26] = 0x000b0000;                                          // RAM[0xfc26]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc2b] = 0x000b0000;                                          // RAM[0xfc2b]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc30] = 0x000b0000;                                          // RAM[0xfc30]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc35] = 0x000b0000;                                          // RAM[0xfc35]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc3a] = 0x000b0000;                                          // RAM[0xfc3a]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc3f] = 0x000b0000;                                          // RAM[0xfc3f]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc44] = 0x000b0000;                                          // RAM[0xfc44]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc49] = 0x000b0000;                                          // RAM[0xfc49]: JUMP  00      // if (REG[0x00] == REG[0x00]) {p <- 0x;}
    RAM[0xfc4e] = 0x000b0000;
    RAM[0xfc53] = 0x000b0000;
    RAM[0xfc58] = 0x000b0000;
    RAM[0xfc5d] = 0x000b0000;
    RAM[0xfc62] = 0x000b0000;
    RAM[0xfc67] = 0x000b0000;
    RAM[0xfc6c] = 0x000b0000;
    RAM[0xfc71] = 0x000b0000;
    RAM[0xfc76] = 0x000b0000;
    RAM[0xfc7b] = 0x000b0000;
    RAM[0xfc80] = 0x000b0000;
    RAM[0xfc85] = 0x000b0000;
    RAM[0xfc8a] = 0x000b0000;
    RAM[0xfc8f] = 0x000b0000;
    RAM[0xfc94] = 0x000b0000;
    RAM[0xfc99] = 0x000b0000;
    RAM[0xfc9e] = 0x000b0000;
    RAM[0xfca3] = 0x000b0000;
    RAM[0xfca8] = 0x000b0000;
    RAM[0xfcad] = 0x000b0000;
    RAM[0xfcb2] = 0x000b0000;
    RAM[0xfcb7] = 0x000b0000;
    RAM[0xfcbc] = 0x000b0000;
    RAM[0xfcc1] = 0x000b0000;
    RAM[0xfcc6] = 0x000b0000;
    RAM[0xfccb] = 0x000b0000;
    RAM[0xfcd0] = 0x000b0000;
    RAM[0xfcd5] = 0x000b0000;
    RAM[0xfcda] = 0x000b0000;
    RAM[0xfcdf] = 0x000b0000;
    RAM[0xfce4] = 0x000b0000;
    RAM[0xfce9] = 0x000b0000;
    RAM[0xfcee] = 0x000b0000;
    RAM[0xfcf3] = 0x000b0000;
    RAM[0xfcf8] = 0x000b0000;
    RAM[0xfcfd] = 0x000b0000;
    RAM[0xfd02] = 0x000b0000;
    RAM[0xfd07] = 0x000b0000;
    RAM[0xfd0c] = 0x000b0000;


    printf("%5s %5s %5s %5s %24s %24s %24s %24s %24s %24s","op","opr1","opr2","opr3", "ARI1", "ARI2", "ARI3", "ARI4", "ARI5", "ARI6");
    printf("\n");
    printf("----- ----- ----- -----");
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
        int stop = reg[0xfc];
        if(p > 0xfbf2 && p <= 0xfc06){
                stop = stop - 5;
            }
        for(int h = 0x0000fc0e; h <= stop; h+=5){
            if(RAM[h]<=0x1c || (RAM[h]>=0x42 && RAM[h]<=0x54)){
                printf(" %5x %5x %5x %5x", RAM[h], RAM[h+1], RAM[h+2], RAM[h+3]);
            }
            
        }
        printf("\n");
        
    } while (p != 0);
    printf("----- ----- ----- -----");
    
    printf("\n");
    printf("%5s %5s %5s %5s %24s %24s %24s %24s %24s %24s","op","opr1","opr2","opr3", "ARI1", "ARI2", "ARI3", "ARI4", "ARI5", "ARI6");
    printf("\nend                     \n");
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
    sinal1 = val1>>31;
    sinal2 = val2>>31;
    expv1 = val1<<1; expv1 = expv1>>17;
    expv2 = val2<<1; expv2 = expv2>>17;
    mant1 = val1 & 0xffff;
    mant2 = val2 & 0xffff;
    
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
            result = sinal1<<31;
            result += expv1<<16;
            result += soma;
            return result;
        }
        else{
            soma = abs(mant1 - mant2);
            if(mant2 > mant1) { result = sinal2<<31; }
            else { result = sinal1<<31;}
            result += expv1<<16;
            result += soma;
            return result;
        }
    }
    else{
        if(sinal2 == 0){
            soma = abs(mant1 - mant2);
            if(mant1 > mant2) { result = sinal1<<31; }
            else { result = sinal2<<31;}
            result += expv1<<16;
            result += soma;
            return result;
        }
        else{
            soma = abs(mant1 + mant2);
            result = sinal1<<31;
            result += expv1<<16;
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