#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CCtype.h"
#include "struct.h"
#include "alert.h"

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

inline Func *new_func () 
{
    Func *f;
    f = malloc (sizeof (Func));
    f->arg_list = new_list ();
    f->state_list = new_list ();
    f->vari_list = new_list ();
    return f;
}

inline Lv *new_lv (char *n, int t)
{
    Lv *l;
    l = malloc (sizeof (Lv));
    l->name = n;
    l->type = t;
    return l;
}

inline Assi *new_assi (Lv *l, List *r)
{
    Assi *a;
    a = malloc (sizeof (Assi));
    a->rval = r;
    a->lval = l;
    return a;
}

inline Fun_Cal *new_fun_cal (List *arg, char *n)
{
    Fun_Cal *f;
    f = malloc (sizeof (Fun_Cal));
    f->argp_list = arg;
    f->name = n;
    return f;
}

inline If *new_if (List *c, List* s)
{
    If *i;
    i = malloc (sizeof (If));
    i->cmp_list = c;
    i->state_list = s;
    i->else_if = NULL;
    return i;
}

inline For *new_for (List *i, List *c, List *s, List *t) 
{
    For *f;
    f = malloc (sizeof (For));
    f->init_list = i;
    f->cmp_list = c;
    f->step_list = s;
    f->state_list = t;
    return f;
}

void insert_head (List *l, void *c, int t)
{
    Node *n;
    n = malloc (sizeof (Node));
    n->cont = c;
    n->type = t;
    n->next = l->head;
    l->head = n;
    l->len ++;
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

void insert_sym (List *l, void *c, char *s, int t)
{
    Node  **ptr;
    ptr = &(l->head);
    while (*ptr) {
        switch ((*ptr)->type) {
            case STR_DECL:
                if (strcmp(((Decl*)(*ptr)->cont)->name, s) == 0)
                    alert ("Same variable name");
                break;
            case STR_FUNC:
                if (strcmp(((Func*)(*ptr)->cont)->name, s) == 0)
                    alert ("Same Function name");
                break;
        }
        ptr = &((*ptr)->next);
    }
    insert_tail (l, c, t);
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
                printf ("ret type: %s\n", type_2_string(((Func*)(*ptr)->cont)->ret_type));
                puts ("arg list:");
                show_list (((Func*)(*ptr)->cont)->arg_list);
                puts ("--");
                puts ("vari list:");
                show_list (((Func*)(*ptr)->cont)->vari_list);
                puts ("--");
                puts ("state list:");
                show_list (((Func*)(*ptr)->cont)->state_list);
                puts ("================");
                break;
            case STR_STATE:
                break;
            case STR_DECL:
                printf ("%s %s\n", type_2_string(((Decl*)(*ptr)->cont)->type),((Decl*)(*ptr)->cont)->name);
                break;
            case STR_ASSI:
                puts ("Assign:");
                show_lv (((Assi*)(*ptr)->cont)->lval);
                printf (" = ");
                show_list (((Assi*)(*ptr)->cont)->rval);
                puts (" ");
                break;
            case STR_FUN_CAL:
                puts ("------");
                puts ("Function call:");
                printf ("name: %s\n", ((Fun_Cal*)(*ptr)->cont)->name);
                puts ("arg pass list:");
                show_list (((Fun_Cal*)(*ptr)->cont)->argp_list);
                puts ("------");
                break;
            case STR_SESS:
                printf ("Session: %s\n", (char*)((*ptr)->cont));
                break;
            case STR_IF:
                break;
            case STR_FOR:
                break;
            case STR_RET:
                printf ("Return:");
                show_list ((List*)(*ptr)->cont);
                puts (" ");
                break;
            case STR_GOTO:
                printf ("Goto: %s\n", ((char*)(*ptr)->cont));
                break;
            case STR_TOK:
                //printf ("%d", ((token*)(*ptr)->cont)->type);
                if (((token*)(*ptr)->cont)->type == NUM)
                    printf ("%d ", ((token*)(*ptr)->cont)->n);
                else if (((token*)(*ptr)->cont)->type == ADDR)
                    printf ("*%s ", ((token*)(*ptr)->cont)->s);
                else if (((token*)(*ptr)->cont)->type == REFE)
                    printf ("&%s ", ((token*)(*ptr)->cont)->s);
                else
                    printf ("%s ", ((token*)(*ptr)->cont)->s);
                break;
            case STR_LIST:
                show_list (((List*)(*ptr)->cont));
                puts (" ");
                break;
        }
        ptr = &((*ptr)->next);
    }
}

void show_token (token *t)
{
    char *s;
    switch  (t->type) {
        case ID:
            s = "ID";
            break;
        case NUM:
            s = "NUM";
            break;
        case COLON:
            s = "COLON";
            break;
        case XOR:
            s = "XOR";
            break;
        case OR:
            s = "OR";
            break; 
        case AND:
            s = "AND";
            break;
        case MUL:
            s = "MUL";
            break;
        case DIV:
            s = "DIV";
            break;
        case PLUS:
            s = "PLUS";
            break;
        case MINU:
            s = "MINU";
            break;
        case MOD:
            s = "MOD";
            break;
        case CHAR:
            s = "CHAR";
            break;
        case STRING:
            s = "STRING";
            break;
        case LPAR:
            s = "LPAR";
            break;
        case RPAR:
            s = "RPAR";
            break;
        case LBPAR:
            s = "LBPAR";
            break;
        case RBPAR:
            s = "RBPAR";
            break;
        case SEMI:
            s = "SEMI";
            break;
        case COM:
            s = "COM";
            break;
        case ASSI:
            s = "ASSI";
            break;
        case EQU:
            s = "EQU";
            break;
        case SHIFT:
            s = "SHIFT";
            break;
        case BOOL:
            s = "BOOL";
            break;
        case EF:
            s = "EOF";
            break;
        case ADDR:
            s = "ADDR";
            break;
        case REFE:
            s = "REFE";
            break;
    }
    printf ("%s: ", s);
    if (t->type == NUM)
        printf ("%d\n", t->n);
    else
        printf ("%s\n", t->s);
}

void show_lv (Lv *l) {
    switch (l->type) {
        case LV_PTR:
            printf ("*");
            break;
    }
    printf ("%s", l->name);
}
