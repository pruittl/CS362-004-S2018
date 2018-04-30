// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c card: Smithy
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
    
    //save game states
    int handCountPrior = state->handCount[0];
    int p2handCount = state->handCount[1];
    int p1discardCount = state->discardCount[0];
    
    int cardChoices = 0;
    buyCard(smithy, state);
    int results = cardEffect(smithy, cardChoices, cardChoices, cardChoices, state, 0, NULL);
    domAssert(results == 0, "Testing smithy card...");
    
    //ensure hand count increased by 2 (three cards added, smithy card discarded = 2 total
    domAssert((state->handCount[0] - handCountPrior) == 2, "Hand count increased by three by smithy card.");
    
    //player 2 hand not affected by smithy card
    domAssert(state->handCount[1] == p2handCount, "Player 2 hand count not affected by smithy card.");
    
    //player 1 has one more card in discard pile
    domAssert((state->discardCount[0] - p1discardCount) == 1, "Player 1 discard pile increased by 1.");
    
}



