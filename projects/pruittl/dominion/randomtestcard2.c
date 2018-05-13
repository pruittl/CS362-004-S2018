//randomtestcard2.c
// CS 362 - 400
// Leigh Ann Pruitt
// Testing dominion.c card: Smithy
// Random tester



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
    int cardCountFailures = 0;
    int cardCountSuccesses = 0;
    
    int cardChoices = 0;
    
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
            
            //whose turn = 0, then change turn at end of logic
            for(int i = 0; i < numPlayers; i++){
                int preCards = state->handCount[i];
                
                //play card
                int result = cardEffect(smithy, cardChoices, cardChoices, cardChoices, state, 0, NULL);
                
                //printf("Result: %i \n", result);
                
                //check for correct return of the function
                if (result == 0)
                    cardSuccesses++;
                else if (result != 0)
                    cardFailures++;
                
                //printf("Result: %i \n", result);
                
                //check for correct execution of the card
                if (state->handCount[i] - preCards == 2)
                    cardCountSuccesses++;
                else if (state->handCount[i] - preCards != 2)
                    cardCountFailures++;
                
                //move to next player
                endTurn(state);

            }
            
        }
        
        
    }
    
    printf("The game initialized correctly %i times and failed to initiate correctly %i times.\n", initSuccesses, initFailures);

    printf("The card returned correctly %i times and failed to return correctly %i times.\n", cardSuccesses, cardFailures);
    
    printf("The card correctly added three cards %i times and failed to add cards correctly %i times.\n", cardCountSuccesses, cardCountFailures);
    
}



