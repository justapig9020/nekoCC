#ifndef _CCTYPE_H_
#define _CCTYPE_H_

enum {
    OPT_LPAR,
    OPT_RPAR,
    OPT_PLUS,
    OPT_MUL,
    OPT_BAND,
    OPT_BXOR,
    OPT_BOR
};

enum {
    LV_ID,
    LV_PTR
};

enum {
    STR_FUNC,
    STR_STATE,
    STR_DECL,
    STR_ASSI,
    STR_FUN_CAL,
    STR_SESS,
    STR_IF,
    STR_FOR,
    STR_RET,
    STR_GOTO,
    STR_TOK
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
    XOR ,
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
    EF ,
    ADDR ,
    REFE
};

#endif
