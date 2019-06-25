#ifndef _CCTYPE_H_
#define _CCTYPE_H_

enum {
    STR_FUNC,
    STR_STATE,
    STR_DECL,
    STR_ASSI,
    STR_FUN_CAL,
    STR_SESS,
    STR_IF,
    STR_FOR,
    STR_RET
};

enum {
    TYPE_INT = 1,
    TYPE_INT_PTR,
    TYPE_CHAR,
    TYPE_CHAR_PTR
};

enum {
    ID = 1 ,
    NUM ,
    COLON ,
    OR , 
    AND ,
    MUL ,
    DIV ,
    PLUS ,
    MINU ,
    MOD ,
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

typedef struct {
    union { 
        char *s;
        int n;
    };
    int type;
} token;


#endif
