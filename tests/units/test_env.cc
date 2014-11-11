#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <lisp/lisp.h>

#define DEBUG_SIZE_OF 0

lisp_env_t* local_env;

static inline int str_cmp(const char* a, const char* b) { return strcmp(a, b) == 0; }
static lisp_t* lisp_id(lisp_t* proc) { return NULL; }

TEST_CASE("require 'nil' to be the first in env list.", "[env]") {
  REQUIRE(str_cmp(with_env_name(local_env), (char*)"nil"));
  REQUIRE(with_env_obj(local_env) == nil);
}

TEST_CASE("add a lisp object to the env.", "[env]") {
  lisp_env_t* e;
  unsigned int i = 1;

  // adding more.
  lisp_t* p = lisp_proc((char*)"id", &lisp_id);
  e = lisp_env(with_proc(p).name, p);
  e = lisp_add_env(e, local_env);
  do { ++i; e = e->next; } while (e);

  REQUIRE(i > 1);
}

TEST_CASE("find by name a lisp object in env.", "[env]") {
  lisp_t* symbol = lisp_symbol((char*)"id");
  const char* symbol_name = with_symbol(symbol).name;
  lisp_env_t* e = NULL;
  unsigned int found = lisp_find_env(symbol_name, local_env, &e);
  REQUIRE(found);
  REQUIRE(e);
  REQUIRE(L_IS_PROC(with_env_obj(e)));
  REQUIRE(str_cmp(with_env_name(e), symbol_name));
  free((void*)symbol);
}

TEST_CASE("looking for missing proc in env.", "[env]") {
  lisp_t* symbol = lisp_symbol((char*)"nid");
  const char* symbol_name = with_symbol(symbol).name;
  lisp_env_t* e = NULL;
  unsigned int not_found = lisp_find_env(symbol_name, local_env, &e);
  REQUIRE(not_found == 0);
  free((void*)symbol);
}

int main(int argc, char* const argv[])
{
  // initialize the local_env with lisp 'nil'.
  local_env = lisp_env((char*)"nil", nil);

  int result = Catch::Session().run( argc, argv );

  return result;
}
