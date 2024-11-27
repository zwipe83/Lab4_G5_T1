//////////////////////////////////////////////////////////////////////////
// <summary>
// Lab 4 Grade 5 Task, option 3
// Filename: main.c
// Created on: 2024-11-23 00:00:00
// Author: Samuel Jeffman
// Description: Main file for elf simulations.
// </summary>
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"



int main(void)
{
    int numOfRounds = 0, numOfMoves = 0;
    int rows = 250;
    int cols = 250;
	int coords = 2;
	int searchDirRows = 8;
	int searchDirCols = 2;
	int emptyTiles = 0;

    SimulationData* simData = NULL;

    simData = allocateSimulationData(rows, cols, coords, searchDirRows, searchDirCols);
    printf("Welcome to Elf Sim 2024\n");

	readFromFile(simData);
	//printGrid(simData);

    numOfRounds = userInput(numOfRounds);
    printf("You have chosen to simulate %d rounds\n", numOfRounds);
    //printf("%c", simData->grid[21][26]);
    //printf("%d", simData->searchDirections[4][1]);

    for (int roundCount = 1; roundCount <= numOfRounds; roundCount++)
    {
		printf("Starting round %d\n", roundCount);

		numOfMoves = startRound(simData);

		printf("Round %d completed with %d moves\n", roundCount, numOfMoves);

        if(numOfMoves == 0)
		{
			printf("No moves were made in round %d\n", roundCount);
			break;
		}

		shuffleOrder(simData);
    }

	printGrid(simData);

	emptyTiles = calculateEmptyTiles(simData);

	printf("There are %d empty tiles\n", emptyTiles);

    freeSimulationData(simData, rows, cols, searchDirRows);

    return 0;
}