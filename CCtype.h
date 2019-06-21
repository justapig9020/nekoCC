#ifndef _CCTYPE_H_
#define _CCTYPE_H_

enum {
 ID ,
 NUM ,
 COLON ,
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
