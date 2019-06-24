#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "struct.h"

extern token *next_token ();

token *utoken = NULL;

void untoken (token *t)
{
    if (utoken) {
        puts ("Already have token in buffer");
        exit (-1)
    }
    utoken = t;
}

token *get_token () 
{
    if (utoken) {
        token *buf;
        buf = utoken;
        utoken = NULL;
        return buf;
    }
    return next_token ();                
}

bool is_id (token *t, char *c) 
{
    return (t->type == ID) && (strcmp (c, t->s));
}

int is_type (token *t)
{
    if (is_id (t, "int"))
        return INT;
    else if (is_id (t, "char"))
        return CHAR;
    return 0;
}

int get_type () 
{
    token *t;
    int type;
    t = get_token ();
    type = is_type (t);
    if (type) {
        free (t);
        t = get_token ();
        if (t->type = MUL) {
            type += 1;
            free (t);
        } else {
            untoken (t);
        }
    }
    return type;
}

bool is_res (token *t)
{
    char *s;
    if (t->type == ID) {
        s = t->s;
        if (is_id (s, "int") ||
            is_id (s, "char") ||
            is_id (s, "for") ||
            is_id (s, "if") ||
            is_id (s, "goto") ||
            is_id (s, "return") ||
            is_id (s, "else") ||
            is_id (s, "void"))
            return true;
    }
    return false;
}

char *get_name ()
{
    char *s;
    token *t;
    t = get_token ();
    if (t->type == ID && !is_res (t)) {
        s = t->s;
        free (t);
        return s;   
    }
    return NULL;
}

List *get_decl ()
{
    List *l;
    token *t;
    Node *n;
    int type;
    while (1) {
        type = get_type ();
        if (type) {
            n = malloc (sizeof (Node));
            
        } else {
            return l;
        }
    }
    return l;
}

Func *getfunc ()
{
    Func *f;
    f = new_func ();
    f->ret_type = get_type ();
    f->name = get_name ();
    
    f->vari_list = get_decl ();
    return f;
}

List *get_program ()
{
    List *l;
    Func *f;
    l = new_list ();
    while (1) {
        f = get_func ();
        if (!f)
            return l;
        insert_tail (l, (void*)f);  
    }
    return NULL;
}
