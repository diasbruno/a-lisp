
#include "lisp/lisp.h"

lisp_t* lisp_eval(lisp_t* obj, lisp_env_t* env)
{
  if (obj == NULL)      { return NULL; }
  if (L_IS_NUMBER(obj)) { return obj; }
  if (L_IS_SYMBOL(obj)) {
    lisp_env_t* t = NULL;
    if (lisp_find_env(with_symbol(obj).name, env, &t)) {
      return with_env_obj(t);
    }
    return NULL;
  }
  if (L_IS_CONS(obj)) {
    lisp_t* a = with_car(obj);

    if (L_IS_SYMBOL(a)) {
      a = lisp_eval(a, env); // acquire the proc.
      lisp_t* b = with_cdr(obj);

      if (b != nil) {
        lisp_t*  worker     = lisp_worker();
        lisp_t** arg_walker = &with_cdr(worker);
        lisp_t*  push_arg = NULL;

        for (lisp_t* args = b; args != nil; args = with_cdr(args)) {
          lisp_t* h   = with_car(args);
          push_arg    = lisp_cons(lisp_eval(h, env), nil);
          *arg_walker = push_arg;
          arg_walker  = &with_cdr(push_arg);
        }

        lisp_t* s = with_proc(a).fn(worker);
        return s;
      }
      return with_proc(a).fn(nil);
    }
  }

  return obj;
}
