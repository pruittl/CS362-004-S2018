// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c function: whoseTurn
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
    
    int currentPlayer = whoseTurn(state);
    
    //save a value to check against later game states
    int p1handCount = state->handCount[0];
    int p2handCount = state->handCount[1];
    
    //check to see that whose turn changes when expected
    endTurn(state);
    
    int nextPlayer = whoseTurn(state);
    
    domAssert(currentPlayer != nextPlayer, "whoseTurn returns different player after turn ends");
    
    //check hands after change to ensure no unintended changes
    domAssert(p1handCount != state->handCount[0], "Number of cards in player 1's hand changes from gameplay turns.");
    domAssert(p2handCount != state->handCount[1], "Number of cards in player 2's hand changes from gameplay turns.");
}


