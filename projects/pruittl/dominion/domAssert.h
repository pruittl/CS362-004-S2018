//
// domAssert function
// Test Assertion for dominion.c code
//Tailored assertion to prevent exit due to default C assert statement

#ifndef domAssert_h
#define domAssert_h

#include <stdio.h>
#include <stdlib.h>

int domAssert(int value, char *description);

#endif /* domAssert_h */
