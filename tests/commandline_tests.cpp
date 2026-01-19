#include "catch.hpp"
#include "commandline.h"

TEST_CASE("constructor", "[commandline]")
{
  const char* args[] = { "atlas" };
  commandline c(1, args);
  REQUIRE(c.strings().size() == 1);
  REQUIRE(c.strings()[0] == "atlas");
}

TEST_CASE("contains", "[commandline]")
{
  const char* args[] = { "atlas" };
  commandline c(1, args);
  REQUIRE(c.contains("atlas"));
}

