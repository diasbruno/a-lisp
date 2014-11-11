#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <lisp/lisp.h>

#define DEBUG_SIZE_OF 0

static inline int str_cmp(const char* a, const char* b) { return strcmp(a, b) == 0; }

static lisp_t* funct(lisp_t* proc) { return NULL; }

TEST_CASE("lisp number.", "[types]") {
  lisp_t* number = lisp_number(1);

  REQUIRE(L_IS_NUMBER(number));
  REQUIRE(with_number(number).nvalue == 1);

  free(number);
}

TEST_CASE("lisp symbol.", "[types]") {
  char* symbol_name = (char*)"+";
  lisp_t* symbol = lisp_symbol(symbol_name);

  REQUIRE(L_IS_SYMBOL(symbol));
  REQUIRE(str_cmp(with_symbol(symbol).name, symbol_name));

  free(symbol);
}

TEST_CASE("lisp cons - empty.", "[types]") {
  lisp_t* cons = lisp_cons(NULL, NULL);

  REQUIRE(L_IS_CONS(cons));
  REQUIRE(with_car(cons) == NULL);
  REQUIRE(with_cdr(cons) == NULL);

  free(cons);
}

TEST_CASE("lisp cons - with car.", "[types]") {
  char* symbol_name = (char*)"+";
  lisp_t* symbol = lisp_symbol(symbol_name);
  lisp_t* cons = lisp_cons(symbol, NULL);

  REQUIRE(L_IS_CONS(cons));
  REQUIRE(with_car(cons) == symbol);
  REQUIRE(with_cdr(cons) == NULL);

  free(symbol);
  free(cons);
}

TEST_CASE("lisp cons - with cdr.", "[types]") {
  char* symbol_name = (char*)"+";
  lisp_t* symbol = lisp_symbol(symbol_name);
  lisp_t* cons = lisp_cons(NULL, symbol);

  REQUIRE(L_IS_CONS(cons));
  REQUIRE(with_car(cons) == NULL);
  REQUIRE(with_cdr(cons) == symbol);

  free(symbol);
  free(cons);
}

TEST_CASE("lisp procedure." "[types]") {
  char* symbol_name = (char*)"+";
  lisp_t* procedure = lisp_proc(symbol_name, &funct);

  REQUIRE(L_IS_PROC(procedure));
  REQUIRE(str_cmp(with_proc(procedure).name, symbol_name));

  free(procedure);
}

TEST_CASE("lisp environment - empty.", "[types]") {
  char* symbol_name = (char*)"nil";
  lisp_env_t* env = lisp_env(symbol_name, NULL);

  REQUIRE(str_cmp(with_env_name(env), symbol_name));
  REQUIRE(with_env_obj(env) == NULL);

  free(env);
}

TEST_CASE("lisp environment - with an object.", "[types]") {
  char* symbol_name = (char*)"x";
  lisp_t* number = lisp_number(1);
  lisp_env_t* env = lisp_env(symbol_name, number);

  REQUIRE(str_cmp(with_env_name(env), symbol_name));
  REQUIRE(with_env_obj(env) == number);

  free(number);
  free(env);
}

int main(int argc, char* const argv[])
{
  int result = Catch::Session().run(argc, argv);

  return result;
}
