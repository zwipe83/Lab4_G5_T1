//////////////////////////////////////////////////////////////////////////
// <summary>
// Lab 4 Grade 5 Task, option 3
// Filename: functions.c
// Created on: 2024-11-23 00:00:00
// Author: Samuel Jeffman
// Description: Function implementations for elf simulations.
// </summary>
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int userInput(int numOfRounds)
{
	printf("Enter the number of rounds you would like to simulate: ");
	int i = scanf("%d", &numOfRounds);
	return numOfRounds;
}

char** allocateGrid(int rows, int cols) {
    // Allocate memory for the array of pointers (rows) 
    char** grid = malloc(rows * sizeof(char*));
    if (grid == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Allocate memory for each row (columns) 
    for (int i = 0; i < rows; i++) {
        grid[i] = malloc(cols * sizeof(char));
        if (grid[i] == NULL) {
            printf("Memory allocation failed\n");
            // Free previously allocated memory 
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return NULL;
        }
    }

    // Initialize the array with some values (e.g., '.') 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = '.';
        }
    }

    return grid;
}

int** allocateSearchDirections(int rows, int cols)
{
	// Allocate memory for the array of pointers (rows) 
	int** searchDirections = malloc(rows * sizeof(int*));
	if (searchDirections == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Allocate memory for each row (columns) 
	for (int i = 0; i < rows; i++) {
		searchDirections[i] = malloc(cols * sizeof(int));
		if (searchDirections[i] == NULL) {
			printf("Memory allocation failed\n");
			// Free previously allocated memory 
			for (int j = 0; j < i; j++) {
				free(searchDirections[j]);
			}
			free(searchDirections);
			return NULL;
		}
	}

	searchDirections[0][0] = -1; //NW
	searchDirections[0][1] = -1;
	searchDirections[1][0] = -1; //N
	searchDirections[1][1] = 0;
	searchDirections[2][0] = -1; //NE
	searchDirections[2][1] = 1;
	searchDirections[3][0] = 0; //E
	searchDirections[3][1] = 1;
	searchDirections[4][0] = 1; //SE
	searchDirections[4][1] = 1;
	searchDirections[5][0] = 1; //S
	searchDirections[5][1] = 0;
	searchDirections[6][0] = 1; //SW
	searchDirections[6][1] = -1;
	searchDirections[7][0] = 0; //W
	searchDirections[7][1] = -1;

	return searchDirections;
}

int*** allocateProposedMoves(int rows, int cols, int coords)
{
	// Allocate memory for the array of pointers (rows) 
	int*** proposedMoves = malloc(rows * sizeof(int**));
	if (proposedMoves == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Allocate memory for each row (columns) 
	for (int i = 0; i < rows; i++) {
		proposedMoves[i] = malloc(cols * sizeof(int*));
		if (proposedMoves[i] == NULL) {
			printf("Memory allocation failed\n");
			// Free previously allocated memory 
			for (int j = 0; j < i; j++) {
				free(proposedMoves[j]);
			}
			free(proposedMoves);
			return NULL;
		}
	}

	// Allocate memory for each row (columns) 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			proposedMoves[i][j] = malloc(coords * sizeof(int));
			if (proposedMoves[i][j] == NULL) {
				printf("Memory allocation failed\n");
				// Free previously allocated memory 
				for (int k = 0; k < j; k++) {
					free(proposedMoves[i][k]);
				}
				free(proposedMoves[i]);
				for (int k = 0; k < i; k++) {
					free(proposedMoves[k]);
				}
				free(proposedMoves);
				return NULL;
			}
		}
	}

	// Initialize the array with some values (e.g., '-1')
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			for (int k = 0; k < coords; k++) {
				proposedMoves[i][j][k] = -1;
			}
		}
	}

	return proposedMoves;
}

int** allocateNumOfProposedMoves(int rows, int cols)
{
	// Allocate memory for the array of pointers (rows) 
	int** numOfProposedMoves = malloc(rows * sizeof(int*));
	if (numOfProposedMoves == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Allocate memory for each row (columns) 
	for (int i = 0; i < rows; i++) {
		numOfProposedMoves[i] = malloc(cols * sizeof(int));
		if (numOfProposedMoves[i] == NULL) {
			printf("Memory allocation failed\n");
			// Free previously allocated memory 
			for (int j = 0; j < i; j++) {
				free(numOfProposedMoves[j]);
			}
			free(numOfProposedMoves);
			return NULL;
		}
	}

	// Initialize the array with some values (e.g., 0)
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			numOfProposedMoves[i][j] = 0;
		}
	}

	return numOfProposedMoves;
}

void freeSimulationData(SimulationData* data, int rows, int cols, int searchDirRows) {
	if (data == NULL) return;

	// Free grid
	for (int i = 0; i < rows; i++) {
		free(data->grid[i]);
	}
	free(data->grid);

	// Free searchDirections
	for (int i = 0; i < searchDirRows; i++) {
		free(data->searchDirections[i]);
	}
	free(data->searchDirections);

	// Free proposedMoves
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			free(data->proposedMoves[i][j]);
		}
		free(data->proposedMoves[i]);
	}
	free(data->proposedMoves);

	// Free numOfProposedMoves
	for (int i = 0; i < rows; i++) {
		free(data->numOfProposedMoves[i]);
	}
	free(data->numOfProposedMoves);

	// Free the SimulationData structure itself
	free(data);
}


SimulationData* allocateSimulationData(int rows, int cols, int coords, int searchDirRows, int searchDirCols) {
	SimulationData* data = (SimulationData*)malloc(sizeof(SimulationData));
	if (data == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	data->grid = allocateGrid(rows, cols);
	data->searchDirections = allocateSearchDirections(searchDirRows, searchDirCols);
	data->proposedMoves = allocateProposedMoves(rows, cols, coords);
	data->numOfProposedMoves = allocateNumOfProposedMoves(rows, cols);
	// Initial order of directions
	data->northOrder = 0;
	data->southOrder = 1;
	data->westOrder = 2;
	data->eastOrder = 3;

	return data;
}

int startRound(SimulationData* simData)
{
	int numOfMoves = 0;

	return numOfMoves;
}
