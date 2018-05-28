// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c card: Adventurer
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
    
    //hand size before adventurer card
    int handSize = state->handCount[0];
    int initTreasureCount = 0;
    
    for (int i = 0; i < state->handCount[0]; i++){
        if(state->hand[0][i] == copper ||
           state->hand[0][i] == gold ||
           state->hand[0][i] == silver)
            initTreasureCount++;
    }
    
    //save game states
    int p2handCount = state->handCount[1];
    int p1discardCount = state->discardCount[0];
    
    int cardChoices = 0;
    buyCard(adventurer, state);
    int results = cardEffect(adventurer, cardChoices, cardChoices, cardChoices, state, 0, NULL);
    domAssert(results == 0, "Testing adventurer card...");
    
    domAssert((state->handCount[0] - handSize) == 2, "Hand count now two greater than before adventurer card.");
    
    int afterTreasureCount = 0;
    for (int i = 0; i < state->handCount[0]; i++){
        if(state->hand[0][i] == copper ||
           state->hand[0][i] == gold ||
           state->hand[0][i] == silver)
            afterTreasureCount++;
    }
    
    //ensure that cards added are treasure cards
    domAssert((afterTreasureCount - initTreasureCount) == 2, "Two treasure cards added to hand.");
    
    //ensure player 2's hand not manipulated
    domAssert(state->handCount[1] == p2handCount, "Player 2 hand count not altered.");
    
    //ensure discard pile equal or greater than before
    domAssert(state->discardCount[0] >= p1discardCount, "Player 1 discard pile equal to or larger than before playing adventurer card.");
    
    
}


