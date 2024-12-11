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
#include <time.h>
#include "functions.h"
#include "tests.h"

//#define DEBUG // Remove this on release

int main (void)
{
#ifdef DEBUG
	runTests();
#endif
	// Initialize variables
    int numOfRounds = 0, numOfMoves = 0, emptyTiles = 0, mode = 0;
	unsigned long totalNumOfMoves = 0;

	GridInfo gridInfo = { 0,0,2,8,2,1 }; // Initialize gridInfo struct
	Size fileSize = {0,0};

    int *gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3; // Increase this to make the grid bigger
    gridInfo.rows = gridSize[0] * gridInfo.factor;
    gridInfo.cols = gridSize[1] * gridInfo.factor;

	//Set minimum grid size
	if (gridInfo.rows < 75)
	{
		gridInfo.rows = 75;
	}
	if (gridInfo.cols < 75)
	{
		gridInfo.cols = 75;
	}

	//Init sim data
    SimulationData *simData = NULL;
    simData = allocateSimulationData(gridInfo, fileSize);

	readFromFile(simData);

    printf("Welcome to Elf Sim 2024\n");

    numOfRounds = userInput(numOfRounds);
	mode = userInputMode(mode);
    printf("You have chosen to simulate %d rounds\n", numOfRounds);

	clock_t simStart = clock(); // Start the clock
	// Start the simulation
    for (int roundCount = 1; roundCount <= numOfRounds; roundCount++)
	{
		clock_t roundStart = clock();
	    system("cls");
	    printf("Starting round %d\n", roundCount);

	    numOfMoves = startRound (simData);
		totalNumOfMoves += numOfMoves;

	    printf("Round %d completed with %d moves\n", roundCount, numOfMoves);
		
		clock_t roundEnd = clock();

		double timeTaken = ((double)(roundEnd - roundStart)) / CLOCKS_PER_SEC; // Calculate the time taken

		int movesPerSecond = numOfMoves / timeTaken; // Calculate the moves per second

		printf("Moves per second, last round: %d\n", movesPerSecond);

	    if (numOfMoves == 0)
		{
		    printf ("No moves were made in round %d\n", roundCount);
			break; // Break out of the loop if no moves were made
		}

		if (mode == 0) //Slow and steady mode
		{
			printGrid(simData); // Print the grid to screen
			system("pause");
		}

	    shuffleOrder (simData);
	}

	clock_t simEnd = clock(); // End the clock
	double timeTaken = ((double)(simEnd - simStart)) / CLOCKS_PER_SEC; // Calculate the time taken

	printf("\nTotal time taken: %f seconds\n", timeTaken);
	printf("Total number of moves: %lu\n", totalNumOfMoves);
	printf("Average number of moves per second: %f\n\n", totalNumOfMoves / timeTaken);

	//printGrid(simData); // Print the grid to screen
	printGridToFile(simData); // Print the grid to a file

	emptyTiles = checkEmptyTiles(simData); // Check for empty tiles

    printf("There are %d empty tiles\n", emptyTiles);
	printf("Operations(Check/save/move): %lu\n", simData->operations);
	printf("Simulation completed\n");

	freeSimulationData(simData); // Free the memory

	system ("pause");

    return 0;
}