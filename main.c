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
    int numOfRounds = 0;
    int rows = 175;
    int cols = 175;
	int coords = 2;
	int searchDirCount = 8;
	int searchDirCoords = 2;

    SimulationData* simData = NULL;

    simData = allocateSimulationData(rows, cols, coords, searchDirCount, searchDirCoords);

    printf("Welcome to Elf Sim 2024\n");

    numOfRounds = userInput(numOfRounds);
    printf("You have chosen to simulate %d rounds\n", numOfRounds);
    //printf("%c", simData->grid[21][26]);
    //printf("%d", simData->searchDirections[4][1]);



    freeSimulationData(simData, rows, cols, searchDirCount);

    return 0;
}