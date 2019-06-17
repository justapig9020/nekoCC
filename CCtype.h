#ifndef _CCTYPE_H_
#define _CCTYPE_H_

#define ID 1
#define NUM 2
#define COLON 3
#define AND 4
#define MUL 5
#define DIV 6
#define PLUS 7
#define MINU 8
#define APO 9
#define LPAR 10
#define RPAR 11
#define LBPAR 12
#define RBPAR 13
#define SEMI 14
#define COM 15
#define ASSI 16
#define EQU 17
#define EF 18

typedef struct {
    union { 
        char *s;
        int n;
    };
    int type;
} token;


#endif
