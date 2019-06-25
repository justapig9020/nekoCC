#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "CCtype.h"
#include "struct.h"
#include "alert.h"

extern token *next_token ();


token *utoken = NULL;

void untoken (token *t)
{
    puts ("untoken");
    if (utoken) {
        free (t);
        free (utoken);
        alert ("Already have token in buffer");
    }
    utoken = t;
}

token *get_token () 
{
    if (utoken) {
        puts ("get untoken");
        token *buf;
        buf = utoken;
        utoken = NULL;
        return buf;
    }
    return next_token ();                
}

bool is_id (token *t, char *c) 
{
    //printf ("%s, %s\n", t->s, c);
    return (t->type == ID) && !(strcmp (c, t->s));
}

bool is_token (int y)
{
    token *t = get_token ();
    bool r = false;
    //printf ("type:%d, %d", t->type, y);
    if (t->type == y) {
        r = true;
        if (t->type != NUM)
            free (t->s);
        free (t);
    } else {
        untoken (t);
    }
    return r;
}

int is_type (token *t)
{
    if (is_id (t, "int"))
        return TYPE_INT;
    else if (is_id (t, "char"))
        return TYPE_CHAR;
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
        if (t->type == MUL) {
            type += 1;
            free (t);
        } else {
            untoken (t);
        }
    } else {
        untoken (t);
    }
    return type;
}

bool is_res (token *t)
{
    if (t->type == ID) {
        if (is_id (t, "int") ||
            is_id (t, "char") ||
            is_id (t, "for") ||
            is_id (t, "if") ||
            is_id (t, "goto") ||
            is_id (t, "return") ||
            is_id (t, "else") ||
            is_id (t, "void"))
            return true;
    }
    return false;
}

char *get_name ()
{
    char *s;
    token *t;
    t = get_token ();
    //printf ("type: %d", t->type);
    if (t->type == ID && !is_res (t)) {
        s = t->s;
        free (t);
        return s;   
    }
    return NULL;
}

List *get_decl_list (int y)
{
    List *l;
    token *t;
    Decl *d;
    int type;
    l = new_list ();
    while (1) {
        type = get_type ();
        if (type) {
            d = new_decl ();
            d->type = type;
            d->name = get_name ();
            if (!d->name) {
                free (d);
                alert ("wrong variable name");
            }
            insert_tail (l, (void*)d, STR_DECL);
        } else {
            return l;
        }
        if (!is_token (y)) {
            return l;
        }
    }
    return NULL;
}

Func *get_func ()
{
    Func *f;
    f = new_func ();
    f->ret_type = get_type ();
    if (f->ret_type == 0) { 
        free (f);
        alert ("wrong function type");
    }
    puts ("get type");
    f->name = get_name ();
    if (!f->name) {
        free (f);
        alert ("wrong function name");
    }
    puts ("get name");
    if (!is_token (LPAR)) {
        alert ("Unexpected token, not LPAR");
    }
    f->arg_list = get_decl_list (COM);
    if (!f->vari_list) {
        free (f);
        alert ("Wrong function args");
    }
    puts ("get arg_list");
    if (!is_token (RPAR)) {
        alert ("Unexpected token, not RPAR");
    }
    if (!is_token (LBPAR)) {
        alert ("Unexpected token, not LBPAR");
    }
    if (!is_token (RBPAR)) {
        alert ("Unexpected token, not RBPAR");
    }
    puts ("func done");
    return f;
}

List *get_program ()
{
    List *l;
    Func *f;
    l = new_list ();
    while (1) {
        f = get_func ();
        puts ("get func");
        if (!f)
            return l;
        insert_tail (l, (void*)f, STR_FUNC);
        return l;
    }
    return NULL;
}
