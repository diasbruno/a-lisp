#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <lisp/lisp.h>

lisp_env_t* local_env;

TEST_CASE("eval null.", "[eval]") {
  lisp_t* r = lisp_eval(NULL, NULL);
  REQUIRE(!r);
}

TEST_CASE("eval number.", "[eval]") {
  lisp_t* n = lisp_number(10);
  lisp_t* r = lisp_eval(n, NULL);

  REQUIRE(L_IS_NUMBER(n));
  REQUIRE(with_number(r).nvalue == 10);

  free((void*)n);
}

TEST_CASE("eval symbol.", "[eval]") {
  lisp_t* s = lisp_symbol((char*)"nil");
  lisp_t* r = lisp_eval(s, local_env);

  REQUIRE(r == nil);

  free((void*)s);
}

int main(int argc, char* const argv[])
{
  // initialize the local_env with lisp 'nil'.
  local_env = lisp_env((char*)"nil", nil);
  int result = Catch::Session().run( argc, argv );
  return result;
}
