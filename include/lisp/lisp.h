#ifndef __lisp_h_
#define __lisp_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum lisp_type
{
  LISP_ANY    = 0,
  LISP_SYMBOL = 1,
  LISP_NUMBER = 2,
  LISP_STRING = 3,
  LISP_CONS,
  LISP_PROC
};

struct lisp;

typedef struct lisp* (*lisp_fn_t)(struct lisp*);

/*! env structure. */
typedef struct {
  char* name;
  lisp_fn_t fn;
} lisp_proc_t;

/*! environment hash table list. */
typedef struct lisp_env
{
  char* name;
  struct lisp* obj;
  struct lisp_env* next;
} lisp_env_t;

/*! represents any lisp type. */
typedef struct lisp
{
  enum lisp_type type;
  union {
    /*! numbers. */
    union { long nvalue; double rvalue; } number;
    /*! simbols. */
    struct { char* name; int length; } symbol;
    /*! cons. */
    struct { struct lisp* car; struct lisp* cdr; } cons;
    /*! procedures. */
    lisp_proc_t proc;
  } cell;
} lisp_t;

#define lisp_alloc()  (lisp_t*)malloc(sizeof(lisp_t))

#define L_IS_NUMBER(t) ((t)->type == LISP_NUMBER)
#define L_IS_SYMBOL(t) ((t)->type == LISP_SYMBOL)
#define L_IS_CONS(t)   ((t)->type == LISP_CONS)
#define L_IS_PROC(t)   ((t)->type == LISP_PROC)

#define with_number(x)   (x)->cell.number
#define with_symbol(x)   (x)->cell.symbol
#define with_cons(x)     (x)->cell.cons
#define with_proc(x)     (x)->cell.proc
#define with_env_name(x) (x)->name
#define with_env_obj(x)  (x)->obj

#define with_car(x)    (with_cons((x)).car)
#define with_cdr(x)    (with_cons((x)).cdr)

#ifdef __cplusplus
extern "C" {
#endif

/*! global environment. */
lisp_t* lisp_global_env;
lisp_t* nil;

/*! create types. */
lisp_t*     lisp_number(int num);
lisp_t*     lisp_symbol(const char* name);
lisp_t*     lisp_cons(lisp_t* a, lisp_t* b);
lisp_t*     lisp_proc(const char* name, lisp_fn_t fn);
lisp_env_t* lisp_env(const char* name, lisp_t* obj);

/*! environment. */
lisp_env_t*  lisp_add_env(lisp_env_t* a, lisp_env_t* to);
unsigned int lisp_find_env(const char* name, lisp_env_t* in, lisp_env_t** out);

/*! evaluation. */
lisp_t* lisp_eval(lisp_t* obj, lisp_env_t* env);

#ifdef __cplusplus
}
#endif

#endif // __lisp_h_
