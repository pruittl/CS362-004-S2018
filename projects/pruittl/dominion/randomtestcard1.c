//randomtestcard1.c
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c card: Cutpurse
// Random tester
// Problem solving sources:
//          1. https://www.geeksforgeeks.org/generating-random-number-range-c/
//          2. https://github.com/cs362sp16/cs362sp16_stallcui


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "domAssert.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, const char * argv[]) {
    
    //test result variables
    int initFailures = 0;
    int initSuccesses = 0;
    int cardFailures = 0;
    int cardSuccesses = 0;
    int coinAddFailures = 0;
    int coinAddSuccesses = 0;
    int coinSubtractFailures = 0;
    int coinSubtractSuccesses = 0;
    int discardFailures = 0;
    int discardSuccesses = 0;
    //int cardChoice = rand() % 3;
    int choice[3] = {1, 2, 3};
    srand(time(NULL));
    
    for (int i = 0; i < 1000; i++){
    
    //Initial game state and values setup
    struct gameState *state = newGame();
        
    //generate random number of players from 0 to 5 (valid num of players is 2 - 4)
    //average is weighted by pulling from array with uneven distribution
        int nPlayers[9] = {0, 1, 2, 2, 3, 3, 4, 4, 5};
        int numPlayers = nPlayers[(rand() % (9 - 0 + 1)) + 0];
    int seedRand = 74;
    int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    int gameStatus = initializeGame(numPlayers, kingdom, seedRand, state);
    //printf("\n");
    //domAssert(gameStatus == 0, "Game Initialized Successfully");
        
    //track number of times game initializes correctly or incorrectly
    if (gameStatus == 0)
        initSuccesses++;
    else
        initFailures++;
    
    
    //if game initialized correctly, begin to test card
    //could have been combined in if/else above for optimization, but retained in separate
    //statement for clarity
    if (gameStatus == 0){
        
        //assign hand sizes to players (0 - 16 are valid hand sizes)
        for (int i = 0; i < numPlayers; i++){
            state->handCount[i] = (rand() % 17);
            //printf("Hand count player %i: %i \n", i, state->handCount[i]);
                    //fill player's hand with cards
                    for (int i = 0; i < state->handCount[i]; i++){
                            drawCard(i, state);
                    }
        
        }
        


        //store game state items prior to test
        int p1discardCount = state->discardCount[0];
        int p1coinCount = countHandCoins(0, state);
        int nonP1CoinCounts[4];                         //max 5 players
        
        //store coin counts for players not player 1
         //begin at i = 1 to exclude player 1 (i = 0)
        for(int i = 1; i < numPlayers; i++){
            nonP1CoinCounts[i] = countHandCoins(i, state);
        }

        //check for function return correctly
        int results;
        results = cardEffect(cutpurse, choice[0], choice[1], choice[2], state, 0, 0);
        
        if (results == 0)
            cardSuccesses++;
        else if (results != 0)
            cardFailures++;
 
        //check for correct card functionality
        //testing functionality used from unit tests submitted for assignment 3
        
        
        //cutpurse should add 2 coppers to player 1 and subtract 1 copper from all other players
        if((countHandCoins(0, state) - p1coinCount) == 2)
            coinAddSuccesses++;
        else
            coinAddFailures++;
        
        //subtract coppers from all other players
        //begin at i = 1 to exclude player 1 (i = 0)
        for(int i = 1; i < numPlayers; i++){
            //first check to make sure deck was not void of coppers
            if((nonP1CoinCounts[i]) != 0){
                if((nonP1CoinCounts[i] - countHandCoins(i, state)) == 1)
                    coinSubtractSuccesses++;
                else
                    coinSubtractFailures++;
            }
        }
        
        //player 1 should have one more in discard pile
        //printf("discard count after: %i \n", state->discardCount[0]);
        //printf("discard count before: %i \n", p1discardCount);
        if((state->discardCount[0] - p1discardCount) == 1)
            discardSuccesses++;
        else
            discardFailures++;

            
    }
 
    }
    printf("The game initialized correctly %i times and failed to initiate correctly %i times.\n", initSuccesses, initFailures);
    
    printf("The card function returned correctly %i times and failed to return correctly %i times.\n", cardSuccesses, cardFailures);
    
     printf("The card correctly added coppers %i times and failed to correctly add coppers %i times.\n", coinAddSuccesses, coinAddFailures);
    
     printf("The card correctly subtracted coppers %i times and failed to correctly subtract coppers %i times.\n", coinSubtractSuccesses, coinSubtractFailures);
    
     printf("The card correctly incremented the discard pile %i times and failed to increment the discard pile correctly %i times.\n", discardSuccesses, discardFailures);
    
        
    
}
