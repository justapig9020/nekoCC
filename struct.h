#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct {
    union { 
        char *s;
        int n;
    };
    int type;
} token;

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
    List *vari_list;
    List *state_list;
    char *name;
    int ret_type;
} Func;

typedef struct {
    int type;
    char *name;
} Decl;

typedef struct {
    char *name;
    int type;
} Lv;
 
typedef struct {
    List *rval;
    Lv *lval;
} Assi;

typedef struct {
    List *argp_list;
    char *name;
} Fun_Cal;

typedef struct __If{
    List *cmp_list;
    List *state_list;
    struct __If *else_if;
} If;

typedef struct {
    List *init_list;
    List *cmp_list;
    List *step_list;
    List *state_list;
} For;

Decl *new_decl ();
List *new_list ();
Func *new_func ();
Lv *new_lv (char*, int);
Assi *new_assi (Lv *, List *);
Fun_Cal *new_fun_cal (List *, char *);
If *new_if (List*, List*);
For *new_for (List*, List*, List*, List*);

void insert_tail (List*, void*, int);
void insert_sym (List*, void*, char*, int);
char *type_2_string (int);
void show_list (List *);
void show_token (token *);
void show_lv (Lv*);
#endif
