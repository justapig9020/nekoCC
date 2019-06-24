#ifndef _CCTYPE_H_
#define _CCTYPE_H_

enum {
    INT = 1,
    INT_PTR,
    CHAR,
    CHAR_PTR
};

enum {
    ID ,
    NUM ,
    COLON ,
    OR , 
    AND ,
    MUL ,
    DIV ,
    PLUS ,
    MINU ,
    CHAR ,
    STRING ,
    LPAR ,
    RPAR ,
    LBPAR ,
    RBPAR ,
    SEMI ,
    COM ,
    ASSI ,
    EQU ,
    SHIFT ,
    BOOL ,
    EF 
};

enum {
    
}

typedef struct {
    union { 
        char *s;
        int n;
    };
    int type;
} token;


#endif
