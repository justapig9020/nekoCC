#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct __Node {
    struct __Node *next;
    void *cont;
    int type;
} Node;

typedef struct __List {
    Node *head;
    Node *tail;
    int len;
} List;

typedef struct __Func {
    List *arg_list;
    List *state_list;
    List *vari_list;
    char *name;
    int ret_type;
}Func;

typedef struct {
    int type;
    char *name;
} Decl;

Decl *new_decl ();
List *new_list ();
void insert_tail (List*, void*, int);
Func *new_func ();
void show_list (List *l);

#endif
