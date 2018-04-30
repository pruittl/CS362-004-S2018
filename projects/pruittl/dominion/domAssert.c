//
// Test Assertion for dominion.c code
//Tailored assertion to prevent exit due to default C assert statement


#include "domAssert.h"


int domAssert(int value, char *description) {
    if(!value) {
        printf("TEST: \"%s\" [FAIL:]\n", description);
        return 1;
    }
    else {
        printf("TEST: \"%s\" [PASS:]\n", description);
        return 0;
    }
}
