#include <stdio.h>
#include <stdlib.h>
#include "CCtype.h"
#include "struct.h"

inline Decl *new_decl ()
{
    Decl *d;
    d = malloc (sizeof (Decl));
    d->type = 0;
    d->name = NULL;
    return d;
}

inline List *new_list ()
{
    List *l;
    l = malloc (sizeof (List));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

void insert_tail (List *l, void *c, int t)
{
    Node *n;
    n = malloc (sizeof (Node));
    n->cont = c;
    n->type = t;
    n->next = NULL;
    if (l->tail == NULL) {
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = n;
    }
    l->len ++;
}

inline Func *new_func () 
{
    Func *f;
    f = malloc (sizeof (Func));
    f->arg_list = new_list ();
    f->state_list = new_list ();
    f->vari_list = new_list ();
    return f;
}

char *type_2_string (int y)
{
    switch (y) {
        case TYPE_INT:
            return "int";
            break;
        case TYPE_INT_PTR:
            return "int*";
            break;
        case TYPE_CHAR:
            return "char";
            break;
        case TYPE_CHAR_PTR:
            return "char*";
            break;
    }
}

void show_list (List *l)
{
    Node **ptr;
    ptr = &(l->head);
    while (*ptr != NULL) {
       // printf ("type: %d\n", (*ptr)->type);
        switch ((*ptr)->type) {
            case STR_FUNC:
                printf ("Function: %s\n", ((Func*)(*ptr)->cont)->name);
                puts ("arg_list:");
                show_list (((Func*)(*ptr)->cont)->arg_list);
                break;
            case STR_STATE:
                break;
            case STR_DECL:
                printf ("%s %s\n", type_2_string(((Decl*)(*ptr)->cont)->type),((Decl*)(*ptr)->cont)->name);
                break;
            case STR_ASSI:
                break;
            case STR_FUN_CAL:
                break;
            case STR_SESS:
                break;
            case STR_IF:
                break;
            case STR_FOR:
                break;
            case STR_RET:
                break;

        }
        ptr = &((*ptr)->next);
    }
}
