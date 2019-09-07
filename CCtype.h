#ifndef _CCTYPE_H_
#define _CCTYPE_H_

#include <stdint.h>

// For compare list
typedef uint8_t cmp_t;
enum{
    CMP_CON,
    CMP_CMP
};

// For operators
typedef uint8_t opt_t;
enum {
    OPT_LPAR,
    OPT_RPAR,
    OPT_PLUS,
    OPT_MUL,
    OPT_BAND,
    OPT_BXOR,
    OPT_BOR
};

// For left value
typedef uint8_t lv_t;
enum {
    LV_ID,
    LV_PTR
};

// For statement 
typedef uint8_t str_t;
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
    STR_TOK,
    STR_LIST
};

// For variable type
typedef uint8_t vari_t;
enum {
    TYPE_INT = 1,
    TYPE_INT_PTR,
    TYPE_CHAR,
    TYPE_CHAR_PTR
};

// For token
typedef uint8_t tok_t;
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
