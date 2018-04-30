// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c function: numHandCards
// Problem solving sources:
//      1. https://github.com/joneric/CS-362/blob/master/projects/cookjone
//      2. https://github.com/CS362-Winter-2016/cs362w16_wuzha
//      3. https://github.com/CS362-Winter-2016/cs362w16_rogersza


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "domAssert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main(int argc, const char * argv[]) {
    
    //Initial game state and values setup
    struct gameState *state = newGame();
    int numPlayers = 2;
    int seedRand = 74;
    int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    int gameStatus = initializeGame(numPlayers, kingdom, seedRand, state);
    printf("\n");
    domAssert(gameStatus == 0, "Game Initialized Successfully");
    
    //manually set cards to five
    state->handCount[0] = 5;
    
    //check number of cards using function. should return 5
    int numCards = numHandCards(state);
    
    domAssert(numCards == 5, "numCards function returns the correct value.");
    
    //manually set cards back to zero
    state->handCount[0] = 0;
    numCards = numHandCards(state);
    domAssert(numCards == 0, "numCards correctly reset to zero.");
}
