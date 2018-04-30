#Resource: https://github.com/CS362-Winter-2016/cs362w16_rogersza

CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

adventurer: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c domAssert.o -o randomtestadventurer -lm -g

runAdventurer: adventurer
	rm randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out 2>&1
	gcov dominion.c >> randomtestadventurer.out 2>&1
	cat dominion.c.gcov >> randomtestadventurer.out 2>&1

randomcard: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard.c rngs.c domAssert.o -o randomtestcard -lm -g

runRandomCard: randomcard
	rm randomtestcard.out
	./randomtestcard >> randomtestcard.out 2>&1
	gcov dominion.c >> randomtestcard.out 2>&1
	cat dominion.c.gcov >> randomtestcard.out 2>&1

testdom: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c testdominion.c rngs.c domAssert.o -o testdom -lm -g

runTestDom: testdom
	rm testdominion.out
	rm gameResults.out
	./testdom >> gameResults.out 2>&1
	gcov dominion.c >> testdominion.out 2>&1
	cat dominion.c.gcov >> testdominion.out 2>&1

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

playdom2: dominion.o playdom2.c
	gcc -o playdom2 playdom2.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

domAssert.o: domAssert.h domAssert.c
	gcc -c domAssert.c -g $(CFLAGS)

unit1: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c domAssert.o -o unittest1 -lm -g

unit2: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c domAssert.o -o unittest2 -lm -g

unit3: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c domAssert.o -o unittest3 -lm -g

unit4: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c domAssert.o -o unittest4 -lm -g

card1: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c domAssert.o -o cardtest1 -lm -g

card2: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c domAssert.o -o cardtest2 -lm -g

card3: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c domAssert.o -o cardtest3 -lm -g

card4: domAssert.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c interface.c rngs.c domAssert.o -o cardtest4 -lm -g


dominionTest: unit1 unit2 unit3 unit4 card1 card2 card3 card4
	rm unittestresults.out
	./unittest1 >> unittestresults.out 2>&1
	./unittest2 >> unittestresults.out 2>&1
	./unittest3 >> unittestresults.out 2>&1
	./unittest4 >> unittestresults.out 2>&1
	./cardtest1 >> unittestresults.out 2>&1
	./cardtest2 >> unittestresults.out 2>&1
	./cardtest3 >> unittestresults.out 2>&1
	./cardtest4 >> unittestresults.out 2>&1
	gcov dominion.c -b >> unittestresults.out 2>&1
	cat dominion.c.gcov >> unittestresults.out 2>&1

unittestresults.out: dominionTest

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unit1 unit2 unit3 unit4 card1 card2 card3 card4

clean:
	rm -rf *.o *.dSYM testdom playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe badTestDrawCard testDrawCard randomtestadventurer randomtestcard *.gcov *.gcda *.gcno *.so
