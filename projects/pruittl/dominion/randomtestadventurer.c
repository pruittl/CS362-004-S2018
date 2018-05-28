//randomtestadventurer.c
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
    int cardTreasureFailures = 0;
    int cardTreasureSuccesses = 0;
    int handFailures = 0;
    int handSuccesses = 0;
    int discardFailures = 0;
    int discardSuccesses = 0;
    int preTreasureCount = 0;
    int preTreasureDeckCount = 0;
    int postTreasureCount = 0;
    int preHandCount = 0;
    int preDiscardCount = 0;
    
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
            
            //count number of treasures in each player's hand, store as treasure count
            for(int i = 0; i < numPlayers; i++){
                preTreasureCount = 0;
                for(int j = 0; j < state->handCount[i]; j++){
                    if(state->hand[i][j] == copper ||
                        state->hand[i][j] == silver ||
                        state->hand[i][j] == gold)
                        
                        //starting treasure count for player i
                        preTreasureCount++;
                }
                
                    //get number of treasures in each player's deck
                    //only players with 2 or more treasures in deck will have 2 treasures added to hand
                    //if 1 treasure in deck, 1 treasure added to hand
                    preTreasureDeckCount = 0;
                    for(int j = 0; j < state->deckCount[i]; j++){
                        if(state->deck[i][j] == copper ||
                           state->deck[i][j] == silver ||
                           state->deck[i][j] == gold)
                            
                            //starting treasure count for player i
                            preTreasureDeckCount++;
                    }
                
            preHandCount = state->handCount[i];
            preDiscardCount = state->discardCount[i];
            
            //play card
            int result = cardEffect(adventurer, cardChoices, cardChoices, cardChoices, state, 0, NULL);
            
            //check for correct return of the function
            if (result == 0)
                cardSuccesses++;
            else if (result != 0)
                cardFailures++;
            
            //get number of treasures after playing card (for players with 2 or more treasures in deck)
            postTreasureCount = 0;
            for(int j = 0; j < state->handCount[i]; j++){
                if(state->hand[i][j] == copper ||
                   state->hand[i][j] == silver ||
                   state->hand[i][j] == gold)
                    
                    //starting treasure count for player i
                    postTreasureCount++;
            }
            
            
            //check for correct execution of the card
            //check for addition of two treasures to hand
            if ((preTreasureDeckCount >= 2) && (postTreasureCount - preTreasureCount == 2))
                cardTreasureSuccesses++;
            //check for addition of one treasure to hand from one treasure in deck
            else if((preTreasureDeckCount == 1) && (postTreasureCount - preTreasureCount == 1))
                cardTreasureSuccesses++;
            //check for addition of zero treasures to hand from zero treasures in deck
            else if((preTreasureDeckCount == 0) && (postTreasureCount - preTreasureCount == 0))
                cardTreasureSuccesses++;
            else
                cardTreasureFailures++;
            
            //check for increase in hand count due to addition of treasures
            if((preTreasureDeckCount >=2) && state->handCount[i] - preHandCount> 0)
                handSuccesses++;
            //if only one treasure added, net hand count is zero
            else if((preTreasureDeckCount == 1) && state->handCount[i] - preHandCount == 0)
                handSuccesses++;
            //if no treasures in deck, net hand count is -1
            else if((preTreasureDeckCount == 0) && state->handCount[i] - preHandCount == -1)
                handSuccesses++;
            else
                handFailures++;
                
                //printf("Pre hand: %i \n", preHandCount);
                //printf("Post hand: %i \n", state->handCount[i]);
                
            if(state->discardCount[i] - preDiscardCount > 0)
                discardSuccesses++;
            else
                discardFailures++;
                
                //printf("Pre discard: %i \n", preDiscardCount);
                //printf("Post discard: %i \n", state->discardCount[i]);
                
                
                endTurn(state);
            }
        }


    }
    
    printf("The game initialized correctly %i times and failed to initiate correctly %i times.\n", initSuccesses, initFailures);
    
    printf("The card returned correctly %i times and failed to return correctly %i times.\n", cardSuccesses, cardFailures);
    
    printf("The card added two treasures correctly %i times and failed to add two treasures correctly %i times.\n", cardTreasureSuccesses, cardTreasureFailures);

    printf("The card increased hand count correctly %i times and failed to increase hand count correctly %i times.\n", handSuccesses, handFailures);
    
    printf("The card increased discard count correctly %i times and failed to increase discard count correctly %i times.\n", handSuccesses, handFailures);

}

