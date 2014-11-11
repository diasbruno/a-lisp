
#include "lisp/lisp.h"

static inline int str_cmp(const char* a, const char* b) { return strcmp(a,b) == 0; }

lisp_env_t* lisp_add_env(lisp_env_t* a, lisp_env_t* to)
// Add a new env to the list.
{
  if (a == NULL || to == NULL) { return NULL; }
  lisp_env_t* e = to;
  while (e->next) { e = e->next; }
  e->next = a;
  return to;
}


unsigned int lisp_find_env(const char* name, lisp_env_t* in, lisp_env_t** out)
// Find in the environment a name, 'in' a list,
// and place in this 'out'put.
{
  if (name == NULL || in == NULL) return 0;
  lisp_env_t* e = in;
  int ret = 0;
  while (e) {
    if (str_cmp(with_env_name(e), name)) { *out = e; ret = 1; break; }
    e = e->next;
  }
  return ret;
}
