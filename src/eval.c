
#include "lisp/lisp.h"

lisp_t* lisp_eval(lisp_t* obj, lisp_env_t* env)
{
  if (obj == NULL)      { return NULL; }
  if (L_IS_NUMBER(obj)) { return obj; }

  return obj;
}
