// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c card: Cutpurse
// Problem solving sources:
//      1. https://github.com/joneric/CS-362/blob/master/projects/cookjone
//      2. https://github.com/CS362-Winter-2016/cs362w16_wuzha
//      3. https://github.com/CS362-Winter-2016/cs362w16_rogersza


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "domAssert.h"
#include "interface.h"
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

    
    //Initial test hand setup
    int *testHand = malloc(sizeof(int) * 5);
    testHand[0] = gold;
    testHand[1] = silver;
    testHand[2] = gold;
    testHand[3] = copper;
    testHand[4] = copper;
    testHand[5] = gold;
    
    //Now check updateCoins function for each player
    
    //give each player handCount of 6
    for(int i = 0; i < numPlayers; i++) {
        state->handCount[i] = 6;
        
        
        //deal cards
        for(int j = 0; j < state->handCount[i]; j++) {
            state->hand[i][j] = testHand[j];
        }
    }
    
    //store game state items prior to test
    int p1handCount = state->handCount[0];
    int p1discardCount = state->discardCount[0];
    int p2handCount = state->handCount[1];
    int p1coinCount = countHandCoins(0, state);
    int p2coinCount = countHandCoins(1, state);
    
    //printf("Player 1 coins: %i \n", countHandCoins(0, state));
    //printf("Player 2 coins: %i \n", countHandCoins(1, state));
    //printf("Player 1 discard count: %i \n", state->discardCount[0]);
    
    //obtain cutpurse card
    int cardChoices = 0;
    buyCard(cutpurse, state);
    int results = cardEffect(cutpurse, cardChoices, cardChoices, cardChoices, state, 0, NULL);
    domAssert(results == 0, "Testing cutpurse card...");
    
    //cutpurse should add 2 coppers to player 1 and subtract 1 copper from player 2
    domAssert((countHandCoins(0, state) - p1coinCount) == 2, "Player 1 has 2 coppers added.");
    //printf("Player 1 coins: %i \n", countHandCoins(0, state));
    domAssert((p2coinCount - countHandCoins(1, state)) == 1, "Player 2 has 1 copper subtracted.");
    //printf("Player 2 coins: %i \n", countHandCoins(1, state));
    
    //player 1 should have 1 less in hand, 1 more in discard
    domAssert((state->discardCount[0] - p1discardCount) == 1, "Player 1 has one more card in discard pile.");
    //printf("Player 1 discard: %i \n", state->discardCount[0]);
    domAssert((p1handCount - state->handCount[0]) == 1, "Player 1 has one less card in hand.");

    //player 2 hand should be unaffected or have one less card
    domAssert(p2handCount == state->handCount[1] ||
              (p2handCount - state->handCount[1]) == 1, "Player 2 hand count unchanged or with one card less.");
}
