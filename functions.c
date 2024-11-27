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

int** allocateHasNeighbours(int rows, int cols)
{
	// Allocate memory for the array of pointers (rows) 
	int** hasNeighbours = malloc(rows * sizeof(int*));
	if (hasNeighbours == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Allocate memory for each row (columns) 
	for (int i = 0; i < rows; i++) {
		hasNeighbours[i] = malloc(cols * sizeof(int));
		if (hasNeighbours[i] == NULL) {
			printf("Memory allocation failed\n");
			// Free previously allocated memory 
			for (int j = 0; j < i; j++) {
				free(hasNeighbours[j]);
			}
			free(hasNeighbours);
			return NULL;
		}
	}

	// Initialize the array with some values (e.g., 0)
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			hasNeighbours[i][j] = 0;
		}
	}

	return hasNeighbours;
}

int* allocateDirections(int rows)
{
	// Allocate memory for the array of pointers (rows) 
	int* directions = malloc(rows * sizeof(int));
	if (directions == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Initialize the array with some values (e.g., 0)
	for (int i = 0; i < rows; i++) {
		directions[i] = 0;
	}

	return directions;
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
	data->hasNeighbours = allocateHasNeighbours(rows, cols);
	// Initial order of directions
	data->northOrder = 0;
	data->southOrder = 1;
	data->westOrder = 2;
	data->eastOrder = 3;
	data->rows = rows;
	data->cols = cols;
	data->searchDirRows = searchDirRows;
	data->searchDirCols = searchDirCols;
	data->northDirections = allocateDirections(6);
	data->southDirections = allocateDirections(6);
	data->westDirections = allocateDirections(6);
	data->eastDirections = allocateDirections(6);

	data->northDirections[0] = -1; //NW
	data->northDirections[1] = -1;
	data->northDirections[2] = -1; //N
	data->northDirections[3] = 0;
	data->northDirections[4] = -1; //NE
	data->northDirections[5] = 1;
	data->southDirections[0] = 1; //SE
	data->southDirections[1] = 1;
	data->southDirections[2] = 1; //S
	data->southDirections[3] = 0;
	data->southDirections[4] = 1; //SW
	data->southDirections[5] = -1;
	data->westDirections[0] = -1; //NW
	data->westDirections[1] = -1;
	data->westDirections[2] = 0; //W
	data->westDirections[3] = -1;
	data->westDirections[4] = 1; //SW
	data->westDirections[5] = -1;
	data->eastDirections[0] = -1; //NE
	data->eastDirections[1] = 1;
	data->eastDirections[2] = 0; //E
	data->eastDirections[3] = 1;
	data->eastDirections[4] = 1; //SE
	data->eastDirections[5] = 1;

	return data;
}

int startRound(SimulationData* simData)
{
	int numOfMoves = 0;

	// Check for neighbours
	checkForNeighbours(simData);
	numOfMoves = performProposedMoves(simData);
	resetArrays(simData);

	return numOfMoves;
}

void resetArrays(SimulationData* simData)
{
	// Reset proposedMoves
	for (int i = 0; i < simData->rows; i++) {
		for (int j = 0; j < simData->cols; j++) {
			for (int k = 0; k < 2; k++) {
				simData->proposedMoves[i][j][k] = -1;
			}
		}
	}

	// Reset numOfProposedMoves
	for (int i = 0; i < simData->rows; i++) {
		for (int j = 0; j < simData->cols; j++) {
			simData->numOfProposedMoves[i][j] = 0;
		}
	}
}

int calculateEmptyTiles(SimulationData* simData) // TODO: Complete implementation
{
	int emptyTiles = 0;

	return emptyTiles;
}

void printGrid(SimulationData* simData)
{
	for (int i = 0; i < simData->rows; i++) {
		for (int j = 0; j < simData->cols; j++) {
			printf("%c", simData->grid[i][j]);
		}
		printf("\n");
	}
}

void shuffleOrder(SimulationData* simData)
{
    // Shuffle the order of directions in the opposite order
    int temp = simData->eastOrder;
    simData->eastOrder = simData->westOrder;
    simData->westOrder = simData->southOrder;
    simData->southOrder = simData->northOrder;
    simData->northOrder = temp;
}

void checkForNeighbours(SimulationData* simData)
{
	// Check for neighbours
	printf("Checking for neighbours\nnorthorder:%d\nsouthorder:%d\n\nwestorder:%d\n\neastorder:%d\n", simData->northOrder, simData->southOrder, simData->westOrder, simData->eastOrder);
	int nC = 0, sC = 0, wC = 0, eC = 0;

	for (int row = 0; row < simData->rows-1; row++)
	{
		//printf("Row %d\n", row);
		for (int col = 0; col < simData->cols-1; col++)
		{
			if (row == 75 && col == 75)
			{
				//printGrid(simData);
				int dummy = 0;
			}
			//printf("Col %d\n", col);
			simData->hasNeighbours[row][col] = 0;
			if (simData->grid[row][col] == '#')
			{
				//printf("Found %c at %d:%d", simData->grid[row][col],row,col);
				for (int i = 0; i <= 7; i++)
				{
					//printf("Checking direction %d\n", i);
					int rowNew = row + simData->searchDirections[i][0];
					int colNew = col + simData->searchDirections[i][1];
					//printf("New row %d, new col %d\n", newRow, newCol);
					if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
					{
						if (simData->grid[rowNew][colNew] == '#')
						{
							//printf("Found neighbour at %d:%d\n", rowNew, colNew);
							simData->hasNeighbours[row][col] = 1;
							//break;
						}
					}
				}
				if(simData->hasNeighbours[row][col] == 1)
				{
					//printf("Tile %d:%d has neighbours\n", row, col);
					int movePossible = 0;
					int moveFound = 0;
					int dx, dy, rowNew, colNew;

					for (int count = 0; count <= 3; count++)
					{
						movePossible = 1;
						if (count == simData->northOrder && moveFound == 0) // North
						{
							for (int count2 = 0; count2 < 5; count2 += 2)
							{
								dx = simData->northDirections[count2];
								dy = simData->northDirections[count2 + 1];

								rowNew = row + dx;
								colNew = col + dy;

								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									if (simData->grid[rowNew][colNew] == '#')
									{
										movePossible = 0;
										//break;
									}
								}
							}
							if (movePossible == 1)
							{
								rowNew = row + simData->northDirections[2];
								colNew = col + simData->northDirections[3];
								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									moveFound = 1;
									//printf("Northward move possible from %d:%d to %d:%d\n", row, col, rowNew, colNew);
									saveProposedMove(simData, row, col, rowNew, colNew);
									nC++;
								}
							}
						}
						if (count == simData->southOrder && moveFound == 0) // South
						{
							for (int count2 = 0; count2 < 6; count2 += 2)
							{
								dx = simData->southDirections[count2];
								dy = simData->southDirections[count2 + 1];

								rowNew = row + dx;
								colNew = col + dy;

								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									if (simData->grid[rowNew][colNew] == '#')
									{
										movePossible = 0;
										//break;
									}
								}
							}
							if (movePossible == 1)
							{
								rowNew = row + simData->southDirections[2];
								colNew = col + simData->southDirections[3];
								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									moveFound = 1;
									//printf("Southward move possible from %d:%d to %d:%d\n", row, col, rowNew, colNew);
									saveProposedMove(simData, row, col, rowNew, colNew);
									sC++;
								}
							}
						}
						if (count == simData->westOrder && moveFound == 0) //West
						{
							for (int count2 = 0; count2 < 6; count2 += 2)
							{
								dx = simData->westDirections[count2];
								dy = simData->westDirections[count2 + 1];

								rowNew = row + dx;
								colNew = col + dy;

								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									if (simData->grid[rowNew][colNew] == '#')
									{
										movePossible = 0;
										//break;
									}
								}
							}
							if (movePossible == 1)
							{
								rowNew = row + simData->westDirections[2];
								colNew = col + simData->westDirections[3];
								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									moveFound = 1;
									//printf("Westward move possible from %d:%d to %d:%d\n", row, col, rowNew, colNew);
									saveProposedMove(simData, row, col, rowNew, colNew);
									wC++;
								}
							}
						}
						if (count == simData->eastOrder && moveFound == 0) // East
						{
							for (int count2 = 0; count2 < 6; count2 += 2)
							{
								dx = simData->eastDirections[count2];
								dy = simData->eastDirections[count2 + 1];

								rowNew = row + dx;
								colNew = col + dy;

								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									if (simData->grid[rowNew][colNew] == '#')
									{
										movePossible = 0;
										//break;
									}
								}
							}
							if (movePossible == 1)
							{
								rowNew = row + simData->eastDirections[2];
								colNew = col + simData->eastDirections[3];
								if (rowNew >= 0 && rowNew <= simData->rows - 1 && colNew >= 0 && colNew <= simData->cols - 1)
								{
									moveFound = 1;
									//printf("Eastward move possible from %d:%d to %d:%d\n", row, col, rowNew, colNew);
									saveProposedMove(simData, row, col, rowNew, colNew);
									eC++;
								}
							}
						}
					}
				}
			}
		}
	}
}

void saveProposedMove(SimulationData* simData, int row, int col, int newRow, int newCol)
{
	if (newRow == 67 && newCol == 126)
	{
		int dummy = 0;
	}

	simData->proposedMoves[row][col][0] = newRow;
	simData->proposedMoves[row][col][1] = newCol;
	simData->numOfProposedMoves[newRow][newCol] += 1;
	//printf("Proposed move from %d:%d to %d:%d\n", row, col, newRow, newCol);
}

int performProposedMoves(SimulationData* simData)
{
	int numOfMoves = 0;
	
	printf("Performing proposed moves\n");


	for (int row = 0; row < simData->rows - 1; row++)
	{
		for (int col = 0; col < simData->cols - 1; col++)
		{
			if (row == 67 && col == 125)
			{
				int dummy = 0;
			}
			if (simData->proposedMoves[row][col][0] != -1 && simData->proposedMoves[row][col][1] != -1)
			{
				int newRow = simData->proposedMoves[row][col][0];
				int newCol = simData->proposedMoves[row][col][1];
				//printf("numofproposedmoves: %d\n", simData->numOfProposedMoves[newRow][newCol]);
				if (simData->numOfProposedMoves[newRow][newCol] == 1)
				{
					//printGrid(simData);
					//int dummy = 0;
					//printf("Moving from %d:%d to %d:%d\n", row, col, newRow, newCol);
					//printf("Char: %c\n", simData->grid[newRow][newCol]);
					if (1 || simData->grid[newRow][newCol] == '.') // TODO: Remove the 1 || to enable the check for empty tiles. There is obviously a bug here. Could be related to readFromFile() or the grid allocation.
					{
						simData->grid[newRow][newCol] = '#';
						simData->grid[row][col] = '.';
						if (simData->grid[newRow][newCol] == '#' && simData->grid[row][col] == '.')
						{
							numOfMoves++;
							//printf("Elf moved from %d:%d to %d:%d\n", row, col, newRow, newCol);
						}
					}
					else
					{
						int dummy = 0;
					}
				}
			}
		}
	}
	return numOfMoves;
}

void readFromFile(SimulationData* simData)
{
	// Read from file
	FILE* fp;
	errno_t err = fopen_s(&fp, "input.txt", "r");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	int row = 0, col = 0;
	char ch;

	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n') {
			simData->grid[row+51][col+51] = '\0';  // Null-terminate the string
			row++;
			col = 0;
		}
		else {
			simData->grid[row+50][col+50] = ch;
			col++;
		}
	}
	simData->grid[row+50][col+50] = '\0';  // Null-terminate the last string
	//printGrid(simData);
}