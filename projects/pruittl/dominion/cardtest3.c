// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c card: Sea Hag
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
    
    //store game state items prior to test
    //int p2deckCount = state->deckCount[1];
    int p2discardCount = state->discardCount[1];
    //int p1handCount = state->handCount[0];
    int p1discardCount = state->discardCount[0];
    //printf("P1 hand: %i \n", p1handCount);
    //printf("P1 discard: %i \n", p1discardCount);
    
    //obtain sea hag card
    int cardChoices = 0;
    buyCard(sea_hag, state);
    int results = cardEffect(sea_hag, cardChoices, cardChoices, cardChoices, state, 0, NULL);
    domAssert(results == 0, "Testing sea hag card...");
    
    //check if sea hag causes card to be discarded
    //deck count does not change since discarded card is replaced with curse
    domAssert((state->discardCount[1] - p2discardCount) == 1, "Sea hag causes discard of one card from opponent's deck.");
    
    //player 2 should now draw curse
    drawCard(1, state);
    int topDeck = state->hand[1][state->handCount[1]];
    
    //sea hag causes curse to be on top of opponent's deck
    domAssert(topDeck == curse, "Sea hag causes top of opponent's deck to become a curse.");
    
    //printf("P1 hand: %i \n", state->handCount[0]);
    //printf("P1 discard: %i \n", state->discardCount[0]);
    
    
    //player 1 discard pile increased by 1
    domAssert((state->discardCount[0] - p1discardCount) == 1, "Player 1 discard pile increased by 1.");
    
    
}
