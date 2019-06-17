#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CCtype.h"

//extern void alert (char *s);

int get_anno () {
    char c = getchar ();
    if (c == '/') {
        while ((c = getchar ()) != '\n');
    } else if (c == '*'){
        while (1) {
            while ((c = getchar ()) != '*');
            if (getchar () == '/')
                break;
        }
    } else {
        ungetc (c, stdin);
    }
    return 0;
}

int get_garbage (char c)
{
    switch (c) {
        case ' ':
        case '\t':
        case '\n':
            return 1;
            break;
        case '/':
            return get_anno (c);
            break;
    }
    ungetc (c, stdin);
    return 0;
}

token *get_id (char c)
{
    token *t;
    char *s;
    int  i = 0;
    t = malloc (sizeof (token));
    s = malloc (255);
    do {
        s [i++] = c;
        c = getchar ();
    } while ( (c>='a' && c<='z') ||
              (c>='A' && c<='Z') ||
              (c>='0' && c<='9') ||
               c=='_');
    ungetc(c, stdin);
    if (i>=255) {
        free (t);
        t = NULL;
        free (s);
        s = NULL;
        return t;
        //alert ("id too long");
    }
    t->s = s;
    t->type = ID;
    s = NULL;
    return t;
}

token *get_num (char c)
{
    token *t;
    t = malloc (sizeof (token));
    t->n = 0;
    do {
        t->n *= 10;
        t->n += (c - '0');
        c = getchar ();
    } while ( c>='0' && c<='9');
    ungetc (c, stdin);
    t->type = NUM;
    return t;
}

token *get_sym (char c)
{
    token *t;
    t = malloc (sizeof (token));
    t->s = malloc (1);
    t->s[0] = c;
    switch (c) {
        case ':':
            t->type = COLON;
            break;
        case '&':
            t->type = AND;
            break;
        case '*':
            t->type = MUL;
            break;
        case '/':
            t->type = DIV;
            break;
        case '+':
            t->type = PLUS;
            break;
        case '-':
            t->type = MINU;
            break;
        case '\'':
            t->type = APO;
            break;
        case '(':
            t->type = LPAR;
            break;
        case ')':
            t->type = RPAR;
            break;
        case '{':
            t->type = LBPAR;
            break;
        case '}':
            t->type = RBPAR;
            break;
        case ';':
            t->type = SEMI;
            break;
        case ',':
            t->type = COM;
            break;
        case EOF:
            t->type = EF;
            break;
        default:
            return NULL;
            break;
    }
    return t;
}

token *get_equ (char c)
{
    token *t;
    char *s;
    t = malloc (sizeof (token));
    s = malloc (3);
    s[0] = c;
    switch (c) {
        case '=':
            c = getchar();
            if (c == '=') {
                s[1] = c;
                s[2] = '\0';
                t->s = s;
                t->type = EQU;
            } else {
                s[1] = '\0';
                t->s = s;
                t->type = ASSI;
                ungetc (c, stdin);
            }
            break;
        case '!':
            c = getchar ();
            if (c == '=') {
                s[1] = '=';
                s[2] = '\0';
                t->type = EQU;
            } else {
                ungetc (c, stdin);
                free (t);
                t = NULL;
            }
            break;
        case '>':
        case '<':
            c = getchar ();
            if (c == '=') {
                s[1] = '=';
                s[2] = '\0';
            } else {
                s[1] = '\0';
                ungetc (c, stdin);
            }
            t->s = s;
            t->type = EQU;
            break;
    }
    free (s);
    s = NULL;
    return t;
}

token *next_token ()
{
    char c;
    do {
        c = getchar();
    } while (get_garbage (c));
    c = getchar ();
    switch (c) {
        case 'a'...'z':
        case 'A'...'Z':
        case '_':
            return get_id (c);
            break;
        case '0'...'9':
            return get_num (c);
            break;
        case '>':
        case '=':
        case '<':
        case '!':
            return get_equ (c);
        default:
            return get_sym (c);
            break;
    }
    return NULL;
}
