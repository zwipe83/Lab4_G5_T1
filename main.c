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
	// Initialize variables
    int numOfRounds = 0, numOfMoves = 0, emptyTiles = 0;

	GridInfo gridInfo = { 0,0,2,8,2,1 }; // Initialize gridInfo struct
	Size fileSize;

    int *gridSize = getGridSize ();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3; // Increase this to make the grid bigger
    gridInfo.rows = gridSize[0] * gridInfo.factor;
    gridInfo.cols = gridSize[1] * gridInfo.factor;

    SimulationData *simData = NULL;
    simData = allocateSimulationData (gridInfo, fileSize);
	readFromFile(simData);

    printf ("Welcome to Elf Sim 2024\n");

    numOfRounds = userInput (numOfRounds);
    printf ("You have chosen to simulate %d rounds\n", numOfRounds);

	// Start the simulation
    for (int roundCount = 1; roundCount <= numOfRounds; roundCount++)
	{
	    system ("cls");
	    printf ("Starting round %d\n", roundCount);

	    numOfMoves = startRound (simData);

	    printf ("Round %d completed with %d moves\n", roundCount, numOfMoves);

	    if (numOfMoves == 0)
		{
		    printf ("No moves were made in round %d\n", roundCount);
			break; // Break out of the loop if no moves were made
		}

	    shuffleOrder (simData);
	}

	printGrid(simData); // Print the grid

	emptyTiles = checkEmptyTiles(simData); // Check for empty tiles

    printf ("There are %d empty tiles\n", emptyTiles);

	freeSimulationData(simData); // Free the memory

	system ("pause");

    return 0;
}