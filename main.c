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

int main (void)
{
    int numOfRounds = 0, numOfMoves = 0, emptyTiles = 0;

    GridInfo gridInfo;

    int *gridSize = getGridSize ();
    gridInfo.factor = 3;
    gridInfo.rows = gridSize[0] * gridInfo.factor;
    gridInfo.cols = gridSize[1] * gridInfo.factor;
    gridInfo.coords = 2;
    gridInfo.searchDirRows = 8;
    gridInfo.searchDirCols = 2;

    SimulationData *simData = NULL;
    simData = allocateSimulationData (gridInfo);

    printf ("Welcome to Elf Sim 2024\n");

    readFromFile (simData);

    numOfRounds = userInput (numOfRounds);
    printf ("You have chosen to simulate %d rounds\n", numOfRounds);

    for (int roundCount = 1; roundCount <= numOfRounds; roundCount++)
	{
	    system ("cls");
	    printf ("Starting round %d\n", roundCount);

	    numOfMoves = startRound (simData);

	    printf ("Round %d completed with %d moves\n", roundCount, numOfMoves);

	    if (numOfMoves == 0)
		{
		    printf ("No moves were made in round %d\n", roundCount);
		    break;
		}

	    shuffleOrder (simData);
	    if (roundCount % 10 == 0)
		{
		    printGrid(simData);
		}
	}

    printGrid (simData);

    emptyTiles = checkEmptyTiles (simData);

    printf ("There are %d empty tiles\n", emptyTiles);

    freeSimulationData(simData, gridInfo);

	system ("pause");

    return 0;
}