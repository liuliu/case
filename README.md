CASE: a Simple Test Framework for C
===================================

Unit test for C should be simple, because C is simple.

For now, this is just a weekend hack to put everything togather.

Thus, a test case can be written like:

	TEST_CASE("some test") { ..some code.. }

Simple, no mysterious overhead at all.

For an example, please checkout case.c for details. To compile,
use:

	gcc case.c

It may only works on Linux 64-bit environment, doesn't work in Windows for sure.
