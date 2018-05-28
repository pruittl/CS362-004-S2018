// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c function: updateCoins
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
    
    //Initial test hand setup
    int *testHand = malloc(sizeof(int) * 6);
    testHand[0] = gold;
    testHand[1] = silver;
    testHand[2] = gold;
    testHand[3] = adventurer;
    testHand[4] = smithy;
    testHand[5] = silver;
    
    //Now check updateCoins function for each player
    
    //give each player handCount of 6
    for(int i = 0; i < numPlayers; i++) {
        state->handCount[i] = 6;
    
    
    //deal cards
    for(int j = 0; j < state->handCount[i]; j++) {
        state->hand[i][j] = testHand[j];
    }
     
    //call updateCoins, should increase coin value by 3
    //current coin value for each player should be 10 before calling updateCoins
    //(gold = 3, silver = 2, copper = 1)
        
    updateCoins(i, state, 5);
        
    //coin value for each player should now be 15
        
    domAssert(state->coins == 15, "Test to add 5 coins with updateCoins");
    
    //test updateCoins with 0 add
    updateCoins(i, state, 0);
        
    //coin value for each player should be 10 if updateCoins is 0 since
    //updateCoins resets state coin count
        
    domAssert(state->coins == 10, "Test to add 0 coins with updateCoins");
    
    
    //test to ensure hand count not changed
    domAssert(state->handCount[i] == 6, "Hand count not changed from updateCoins.");
    }
    
    return 0;
}
