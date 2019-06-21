#include <stdio.h>
#include <stdlib.h>
#include "CCtype.h"

extern token *next_token ();
void print_token (token *t)
{
    if (t->type == NUM) {
        printf ("\n+++++\ntype = NUM\nnum = %d\n", t->n);
    } else {
        printf ("\n+++++\ntype = %d\nstring = %s\n", t->type, t->s);
    }
}

int  main ()
{
    token *t;
    while (1) {
        t = next_token ();
        if (!t) {
            puts ("NULL!");
            break;
        }
        if (t->type == EF) {
            puts ("EOF!");
            break;
        }
        print_token (t);
        free (t);
    }
    free (t);
    t = NULL;
    return 0;
}
