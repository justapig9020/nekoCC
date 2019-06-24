#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct __Func {
    List *arg_list;
    List *state_list;
    List *vari_list;
    char *name;
    int ret_type;
}Func;

typedef struct __Node {
    struct __Node *nest;
    void *cont;
    int type;
} Node;

typedef struct __List {
    Node *head;
    Node *tail;
    int len;
} List;

#endif
