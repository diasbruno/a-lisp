
#include "lisp/lisp.h"

//! Utilities

static inline char* cpy_str(const char* str)
{
  unsigned long s = strlen(str) + 1;
  char* cp = malloc(s);
  memcpy(cp, str, s);
  return cp;
}

static char* itoa(int num)
{
  int size = 1;
  int l10 = num;
  do { ++size; l10 = l10/10; } while(l10);
  char* x = malloc(size);
  snprintf(x, size, "%d", num);
  return x;
}

//! Lisp

lisp_t* lisp_number(int num)
{
  lisp_t* obj = lisp_alloc();
  obj->type = LISP_NUMBER;
  with_number(obj).nvalue = num;
  return obj;
}

lisp_t* lisp_symbol(const char* name)
{
  lisp_t* obj = lisp_alloc();
  obj->type = LISP_SYMBOL;
  with_symbol(obj).name = cpy_str(name);
  return obj;
}

lisp_t* lisp_cons(lisp_t* a, lisp_t* b)
{
  lisp_t* obj = lisp_alloc();
  obj->type = LISP_CONS;
  obj->cell.cons.car = a;
  obj->cell.cons.cdr = b;
  return obj;
}

lisp_t* lisp_proc(const char* name, lisp_fn_t fn)
{
  lisp_t* obj = lisp_alloc();
  obj->type = LISP_PROC;
  with_proc(obj).name = cpy_str(name);
  with_proc(obj).fn = fn;
  return obj;
}

lisp_env_t* lisp_env(const char* name, lisp_t* obj)
{
  lisp_env_t* e = (lisp_env_t*)malloc(sizeof(lisp_env_t));
  with_env_name(e) = cpy_str(name);
  with_env_obj(e) = obj;
  e->next = NULL;
  return e;
}
