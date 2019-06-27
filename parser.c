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
   // puts ("untoken");
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
    //    puts ("get untoken");
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
    //show_token (t);
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
    //puts ("get_type");
    //show_token (t);
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
            is_id (t, "break") ||
            is_id (t, "void"))
            return true;
    }
    return false;
}

bool is_EOF ()
{
    token *t;
    t = get_token ();
    if (t->type == EF) { 
        free (t->s);
        free (t);
        return true;
    } else {
        untoken (t);
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

void get_next_id (List *r, int type)
{
    token *t;
    t = get_token ();
    if (t->type != ID && t->type != NUM )
        alert ("Wrong right value1");
    switch (type)
    {
        case AND:
        case MUL:
            t->type = ADDR + type - AND;
            break;
        case MINU:
            //printf ("minu\n");
            if (t->type != NUM)
                alert ("Wrong right value2");
            t->n *= -1;
            break;
        case PLUS:
            if (t->type != NUM)
                alert ("Wrong right value3");
            break;
    }
    insert_tail (r, t, STR_TOK);
}

int get_opt_lv (token *t)
{
    switch (t->type) {
        case LPAR:
            return OPT_LPAR;
        case RPAR:
            return OPT_RPAR;
        case PLUS:
        case MINU:
            return OPT_PLUS;
        case MUL:
        case DIV:
            return OPT_MUL;
        case AND:
            return OPT_BAND;
        case XOR:
            return OPT_BXOR;
        case OR:
            return OPT_BOR;
    }
    alert ("Unexecped operator");
}

void get_opt (List *r, List *l, token *t)
{
    Node *n, *ptr;
    int type = get_opt_lv (t);
    n = malloc (sizeof (Node));
    n->next = NULL;
    n->type = type;
    n->cont = (void*)t;
    while (l->head) {
        ptr = l->head;
        if (ptr->type >= n->type) {
            insert_tail (r, ptr->cont, STR_TOK);
            l->head = ptr->next;
            free (ptr);
            ptr = NULL;
        } else {
            break;
        }
	}
	if (n->type == RPAR) {
		free ((token*)n->cont);
        free (n);
		ptr = l->head;
        if (((token*)l->head->cont)->type != LPAR)
            alert ("Unexecpted RPAR");
		l->head = ptr->next;
        free ((token*)ptr->cont);
		free (ptr);
	} else { 
        n->next = l->head;
    	l->head = n;
	}
}

List *get_rv ()
{
    List *stk, *rv;
    int lt;
    token *t;
	Node *ptr, *buf;
    rv = new_list ();
    stk = new_list ();
    lt = -1;
    while (1) {
        t = get_token ();
        switch (t->type) {
            case SEMI:
                ptr = (stk->head);
	            while (ptr) {
		            buf = ptr;
                    insert_tail (rv, ptr->cont, STR_TOK);
		            ptr = ptr->next;
		            free (buf);
	            }
                return rv;
            case ID:
            case NUM:
                insert_tail (rv, (void*)t, STR_TOK);
                break;
            case AND:
            case MUL:
            case PLUS:
            case MINU:
                //printf ("lt: %d\n", lt);
                switch (lt) {
                    case ID:
                    case NUM:
                    case ADDR:
                    case REFE:
                        get_opt (rv, stk, t);
                        break;
                    default:
                        get_next_id (rv, t->type);
                        break;
                }
                break;
            case XOR:
            case OR:
            case DIV:
            case MOD:
            case RPAR:
            case LPAR:
                get_opt (rv, stk, t);
                break;
            default:
                alert ("Wrong right-value2");
        }
        if ((token*)rv->tail)
            lt = ((token*)rv->tail->cont)->type;
    }
    return NULL;
}

Assi *get_assi (token *t)
{
    Assi *a;
    Lv *lv;
    int type;
    List *rv;
    type = LV_ID;
    if (t->type != ID && t->type == MUL) {
        type = LV_PTR;
        free (t);
        t = get_token ();
        if (t->type != ID)
            alert ("Wrong left-value");
    }
    lv = new_lv (t->s, type);
    if (!lv)
        alert ("Wrong left-value");
    if (!is_token (ASSI))
        alert ("Unexecpt token!!");
    rv = get_rv ();
    if (!rv)
        alert ("Wrong right-value1");
    a = new_assi (lv, rv);
    return a;
}

char *get_goto ()
{

}

If *get_if ()
{

}

For *get_for ()
{

}

List *get_ret ()
{

}

Fun_Cal *get_fun_call (token *t)
{

}

char *get_sess ()
{

}

List *get_state_list ()
{
    List *l;
    token *t, *nt;
    l = new_list ();
    while (1) {
        t = get_token ();
        //show_token (t);
        switch (t->type) {
            case MUL:
            case AND:
                insert_tail (l, (void*)get_assi (t), STR_ASSI);
                break;
            case ID:
                nt = get_token ();
                //show_token (t);
                untoken (nt);
                if (is_id (t, "goto"))
                    insert_tail (l, (void*)get_goto (), STR_GOTO);
                if (is_id (t, "if"))
                    insert_tail (l, (void*)get_if (), STR_IF);
                if (is_id (t, "return"))
                    insert_tail (l, (void*)get_ret (), STR_RET);
                switch (nt->type) {
                    case LPAR:
                        insert_tail (l, (void*)get_fun_call(t), STR_FUN_CAL);
                        break;
                    case COLON:
                        insert_tail (l, (void*)get_sess (t), STR_SESS);
                        break;
                    default:
                        insert_tail (l, (void*)get_assi (t), STR_ASSI);
                    break;
                }
                break;
            case RBPAR:
                untoken (t);
                return l;
        }
    }
}

void sym_chk (List *l1, List *l2)
{
    Node **ptr1, **ptr2, **buf;
    ptr1 = &(l1->head);
    ptr2 = &(l2->head);
    buf = ptr2;
    while (*ptr1) {
        while (*ptr2) {
            //printf ("%s, %s\n", ((Decl*)(*ptr1)->cont)->name, ((Decl*)(*ptr2)->cont)->name);
            if (strcmp (((Decl*)(*ptr1)->cont)->name,
                        ((Decl*)(*ptr2)->cont)->name) == 0)
                alert ("Same symbol name");
            ptr2 = &((*ptr2)->next);
        }
        ptr1 = &((*ptr1)->next);
        ptr2 = buf;
    }
}

Func *get_func ()
{
    Func *f;
    f = new_func ();
    if (is_EOF ()) {
        free(f);
        return NULL;
    }
    //puts ("========");
    //puts ("get func");
    f->ret_type = get_type ();
    if (f->ret_type == 0) { 
        free (f);
        alert ("Wrong function type");
    }
    //puts ("get type");
    f->name = get_name ();
    if (!f->name) {
        free (f);
        alert ("Wrong function name");
    }
    //puts ("get name");
    if (!is_token (LPAR)) {
        alert ("Unexpected token, not LPAR");
    }
    f->arg_list = get_decl_list (COM);
    if (!f->arg_list) {
        free (f);
        alert ("Wrong function args");
    }
    //puts ("get arg_list");
    if (!is_token (RPAR)) {
        alert ("Unexpected token, not RPAR");
    }
    if (!is_token (LBPAR)) {
        alert ("Unexpected token, not LBPAR");
    }
    f->vari_list = get_decl_list (SEMI);
    if (!f->vari_list) {
        free (f);
        alert ("Wrong function varis");
    }
    sym_chk(f->arg_list, f->vari_list);
    f->state_list = get_state_list ();
    if (!is_token (RBPAR)) {
        alert ("Unexpected token, not RBPAR!");
    }
    //puts ("func done");
    return f;
}

List *get_program ()
{
    List *l;
    Func *f;
    l = new_list ();
    while (1) {
        f = get_func ();
//        puts ("get func");
        if (!f)
            return l;
        insert_tail (l, (void*)f, STR_FUNC);
    }
    return NULL;
}
