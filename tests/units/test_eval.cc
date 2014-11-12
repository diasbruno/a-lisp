#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <lisp/lisp.h>

lisp_env_t* local_env;

TEST_CASE("eval null.", "[eval]") {
  lisp_t* r = lisp_eval(NULL, NULL);
  REQUIRE(!r);
}

int main(int argc, char* const argv[])
{
  // initialize the local_env with lisp 'nil'.
  local_env = lisp_env((char*)"nil", nil);

  int result = Catch::Session().run( argc, argv );

  return result;
}
