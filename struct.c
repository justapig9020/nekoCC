#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


inline List *new_list ()
{
    List l = malloc (sizeof (List));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}

void inset_tail (List *l, void *c, int t)
{
    Node *n;
    n = malloc (sizeof (Node));
    n->cont = c;
    n->type = t;
    n->next = NULL;
    if (tail == NUll) {
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
    f = nalloc (sizeof (Func));
    f->arg_list = new_list ();
    f->state_list = new_list ();
    f->vari_list = new_list ();
    return f;
}
