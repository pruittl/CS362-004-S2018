// Assignment 3
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c function: discardCard
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
    
    //test discardCard
    
    //Initial test hand setup
    int *testHand = malloc(sizeof(int) * 3);
    testHand[0] = gold;
    testHand[1] = adventurer;
    testHand[2] = smithy;

    
    //give each player handCount of 3
    for(int i = 0; i < numPlayers; i++) {
        state->handCount[i] = 3;
        
        
        //deal cards
        for(int j = 0; j < state->handCount[i]; j++) {
            state->hand[i][j] = testHand[j];
        }
    }
    
    //discard each card for player 1
    for(int i = 0; i < 3; i++){
        discardCard(1, 1, state, 0);
        domAssert(state->handCount[1] == (2 - i) , "Removal of card from hand");
    }
    
    //player 2 hand count should now be zero
    domAssert(state->handCount[1] == 0, "Player 2 hand count zero after discarding all cards");
    
    //player 1's hand count should still be 3
    domAssert(state->handCount[0] == 3, "Player 1's hand count remains unchanged.");

}

