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

/// <summary>
/// Read user input
/// </summary>
/// <param name="numOfRounds"></param>
/// <returns></returns>
int userInput(int numOfRounds)
{
	printf("Enter the number of rounds you would like to simulate: ");
	int i = scanf("%d", &numOfRounds);
	return numOfRounds;
}

/// <summary>
/// Allocate memory for a 1D array
/// </summary>
/// <param name="length"></param>
/// <param name="elementSize"></param>
/// <param name="initialValue"></param>
/// <returns></returns>
void* allocate1DArray(int length, size_t elementSize, void* initialValue) 
{
	// Allocate memory for the array
	void* array = malloc(length * elementSize);
	if (array == NULL) 
	{
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Initialize the array with the initial value
	for (int i = 0; i < length; i++) 
	{
		if (elementSize == sizeof(int)) 
		{
			((int*)array)[i] = *(int*)initialValue;
		}
	}

	return array;
}

/// <summary>
/// Allocate memory for a 2D array
/// </summary>
/// <param name="rows"></param>
/// <param name="cols"></param>
/// <param name="elementSize"></param>
/// <param name="initialValue"></param>
/// <returns></returns>
void** allocate2DArray(int rows, int cols, size_t elementSize, void *initialValue) 
{
	// Allocate memory for the array of pointers (rows)
	void** array = malloc(rows * sizeof(void*));
	if (array == NULL) 
	{
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Allocate memory for each row
	for (int i = 0; i < rows; i++) 
	{
		array[i] = malloc(cols * elementSize);
		if (array[i] == NULL) 
		{
			printf("Memory allocation failed\n");
			// Free previously allocated memory
			for (int j = 0; j < i; j++) 
			{
				free(array[j]);
			}
			free(array);
			return NULL;
		}
        // Set each element to the initial value
        for (int j = 0; j < cols; j++) 
		{
            if (elementSize == sizeof(int)) 
			{
                ((int*)array[i])[j] = *(int*)initialValue;
            } 
			else if (elementSize == sizeof(char)) 
			{
                ((char*)array[i])[j] = *(char*)initialValue;
			}            
		}
	}

	return array;
}

/// <summary>
/// Allocate memory for a 3D array
/// </summary>
/// <param name="rows"></param>
/// <param name="cols"></param>
/// <param name="depth"></param>
/// <param name="elementSize"></param>
/// <param name="initialValue"></param>
/// <returns></returns>
void*** allocate3DArray(int rows, int cols, int depth, size_t elementSize, void* initialValue) 
{
	void*** array = malloc(rows * sizeof(void**));
	if (array == NULL) 
	{
		printf("Memory allocation failed\n");
		return NULL;
	}
	for (int i = 0; i < rows; i++) 
	{
		array[i] = (void**)allocate2DArray(cols, depth, elementSize, initialValue);
		if (array[i] == NULL) 
		{
			printf("Memory allocation failed\n");
			for (int j = 0; j < i; j++) 
			{
				free2DArray(array[j], cols);
			}
			free(array);
			return NULL;
		}
	}
	return array;
}

/// <summary>
/// Free the allocated 1D array
/// </summary>
/// <param name="array"></param>
void free1DArray(void* array) 
{
	free(array);
}

/// <summary>
/// Free the allocated 2D array
/// </summary>
/// <param name="array"></param>
/// <param name="rows"></param>
void free2DArray(void** array, int rows) 
{
	// Free each row
	for (int i = 0; i < rows; i++) 
	{
		free(array[i]);
	}
	// Free the array of pointers
	free(array);
}

/// <summary>
/// Free the allocated 3D array
/// </summary>
/// <param name="array"></param>
/// <param name="rows"></param>
/// <param name="cols"></param>
void free3DArray(void*** array, int rows, int cols) 
{
	for (int i = 0; i < rows; i++) 
	{
		free2DArray(array[i], cols);
	}
	free(array);
}

/// <summary>
/// Free the allocated memory for the simulation data
/// </summary>
/// <param name="simData"></param>
void freeSimulationData(SimulationData* simData) 
{
	if (simData == NULL) return;

	// Free grid
	if (simData->grid != NULL)
	{
		free2DArray(simData->grid, simData->gridInfo.rows);
	}

	// Free searchDirections
	if (simData->searchDirections != NULL)
	{
		free2DArray(simData->searchDirections, simData->gridInfo.searchDirRows);
	}

	// Free proposedMoves
	if (simData->proposedMoves != NULL) {
		free3DArray(simData->proposedMoves, simData->gridInfo.rows, simData->gridInfo.cols);
	}

	// Free numOfProposedMoves
	if (simData->numOfProposedMoves != NULL)
	{
		free2DArray(simData->numOfProposedMoves, simData->gridInfo.rows);
	}

	// Free northDirections
	if (simData->directions.northDirections != NULL)
	{
		free1DArray(simData->directions.northDirections);
	}

	// Free southDirections
	if (simData->directions.southDirections != NULL)
	{
		free1DArray(simData->directions.southDirections);
	}

	// Free westDirections
	if (simData->directions.westDirections != NULL)
	{
		free1DArray(simData->directions.westDirections);
	}

	// Free eastDirections
	if (simData->directions.eastDirections != NULL)
	{
		free1DArray(simData->directions.eastDirections);
	}

	// Free the SimulationData structure itself
	free(simData);
}

/// <summary>
/// Allocate memory for the simulation data
/// </summary>
/// <param name="gridInfo"></param>
/// <param name="fileSize"></param>
/// <returns></returns>
SimulationData* allocateSimulationData(GridInfo gridInfo, Size fileSize) 
{
	SimulationData* data = (SimulationData*)malloc(sizeof(SimulationData));
	if (data == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	//Allocate memory for the grid, search directions, proposed moves, and number of proposed moves
	char initialChar = '.';
	int initialInt = 0;
	data->grid = allocate2DArray(gridInfo.rows, gridInfo.cols, sizeof(char), &initialChar);
	data->searchDirections = allocate2DArray(gridInfo.searchDirRows, gridInfo.searchDirCols, sizeof(int), &initialInt);
	data->proposedMoves = allocate3DArray(gridInfo.rows, gridInfo.cols, gridInfo.coords, sizeof(int), &initialInt);
	data->numOfProposedMoves = allocate2DArray(gridInfo.rows, gridInfo.cols, sizeof(int), &initialInt);
	data->directions.northDirections = allocate1DArray(6, sizeof(int), &initialInt);
	data->directions.southDirections = allocate1DArray(6, sizeof(int), &initialInt);
	data->directions.westDirections = allocate1DArray(6, sizeof(int), &initialInt);
	data->directions.eastDirections = allocate1DArray(6, sizeof(int), &initialInt);

	//Store information about the file
	data->fileSize.rows = fileSize.rows;
	data->fileSize.cols = fileSize.cols;

	//Store information about the grid
	data->gridInfo.rows = gridInfo.rows;
	data->gridInfo.cols = gridInfo.cols;
	data->gridInfo.factor = gridInfo.factor;

	// Initial order of directions
	data->orders.northOrder = 0;
	data->orders.southOrder = 1;
	data->orders.westOrder = 2;
	data->orders.eastOrder = 3;

	// Set search directions
	data->searchDirections[0][0] = -1; //NW
	data->searchDirections[0][1] = -1;
	data->searchDirections[1][0] = -1; //N
	data->searchDirections[1][1] = 0;
	data->searchDirections[2][0] = -1; //NE
	data->searchDirections[2][1] = 1;
	data->searchDirections[3][0] = 0; //E
	data->searchDirections[3][1] = 1;
	data->searchDirections[4][0] = 1; //SE
	data->searchDirections[4][1] = 1;
	data->searchDirections[5][0] = 1; //S
	data->searchDirections[5][1] = 0;
	data->searchDirections[6][0] = 1; //SW
	data->searchDirections[6][1] = -1;
	data->searchDirections[7][0] = 0; //W
	data->searchDirections[7][1] = -1;

	// Set directions for each direction
	data->directions.northDirections[0] = -1; //NW
	data->directions.northDirections[1] = -1;
	data->directions.northDirections[2] = -1; //N
	data->directions.northDirections[3] = 0;
	data->directions.northDirections[4] = -1; //NE
	data->directions.northDirections[5] = 1;

	data->directions.southDirections[0] = 1; //SE
	data->directions.southDirections[1] = 1;
	data->directions.southDirections[2] = 1; //S
	data->directions.southDirections[3] = 0;
	data->directions.southDirections[4] = 1; //SW
	data->directions.southDirections[5] = -1;

	data->directions.westDirections[0] = -1; //NW
	data->directions.westDirections[1] = -1;
	data->directions.westDirections[2] = 0; //W
	data->directions.westDirections[3] = -1;
	data->directions.westDirections[4] = 1; //SW
	data->directions.westDirections[5] = -1;

	data->directions.eastDirections[0] = -1; //NE
	data->directions.eastDirections[1] = 1;
	data->directions.eastDirections[2] = 0; //E
	data->directions.eastDirections[3] = 1;
	data->directions.eastDirections[4] = 1; //SE
	data->directions.eastDirections[5] = 1;

	return data;
}

/// <summary>
/// Start a round of the simulation
/// </summary>
/// <param name="simData"></param>
/// <returns></returns>
int startRound(SimulationData* simData)
{
	int numOfMoves = 0;

	// Check for neighbours
	checkForNeighbours(simData);
	numOfMoves = performProposedMoves(simData);
	resetArrays(simData);

	return numOfMoves;
}

/// <summary>
/// Reset the proposed moves and number of proposed moves arrays
/// </summary>
/// <param name="simData"></param>
void resetArrays(SimulationData* simData)
{
	// Reset proposedMoves
	for (int i = 0; i < simData->gridInfo.rows; i++) 
	{
		for (int j = 0; j < simData->gridInfo.cols; j++)
		{
			for (int k = 0; k < 2; k++) 
			{
				simData->proposedMoves[i][j][k] = -1;
			}
		}
	}

	// Reset numOfProposedMoves
	for (int i = 0; i < simData->gridInfo.rows; i++)
	{
		for (int j = 0; j < simData->gridInfo.cols; j++)
		{
			simData->numOfProposedMoves[i][j] = 0;
		}
	}
}

/// <summary>
/// Check for empty tiles
/// </summary>
/// <param name="simData"></param>
/// <returns></returns>
int checkEmptyTiles(SimulationData* simData) // FIXED: Complete implementation
{
	int emptyTiles = 0;
	int top = 0, bottom = simData->gridInfo.rows - 1;
	int left = 0, right = simData->gridInfo.cols - 1;
	int topFound = 0, rightFound = 0, bottomFound = 0, leftFound = 0;
	int topRow = 0, rightCol = 0, bottomRow = 0, leftCol = 0;

	while (top <= bottom && left <= right) 
	{
		// Parse the top row
		if (!topFound) 
		{
			for (int col = left; col <= right; col++) 
			{
				if (simData->grid[top][col] == '#') 
				{
					topFound = 1;
					printf("Top #: (%d, %d)\n", top, col);
					topRow = top;
					break;
				}
			}
			top++;
		}

		// Parse the rightmost column
		if (!rightFound) 
		{
			for (int row = top; row <= bottom; row++) 
			{
				if (simData->grid[row][right] == '#') 
				{
					rightFound = 1;
					printf("Right #: (%d, %d)\n", row, right);
					rightCol = right;
					break;
				}
			}
			right--;
		}

		// Parse the bottom row
		if (!bottomFound) 
		{
			for (int col = right; col >= left; col--) 
			{
				if (simData->grid[bottom][col] == '#') 
				{
					bottomFound = 1;
					printf("Bottom #: (%d, %d)\n", bottom, col);
					bottomRow = bottom;
					break;
				}
			}
			bottom--;
		}

		// Parse the leftmost column
		if (!leftFound) {
			for (int row = bottom; row >= top; row--) 
			{
				if (simData->grid[row][left] == '#') 
				{
					leftFound = 1;
					printf("Left #: (%d, %d)\n", row, left);
					leftCol = left;
					break;
				}
			}
			left++;
		}
		// Break out of the loop if all '#' are found 
		if (topFound && rightFound && bottomFound && leftFound) 
		{ 
			break; 
		}
	}
	printf("Top row: %d\nRight column: %d\nBottom row: %d\nLeft column: %d\n", topRow, rightCol, bottomRow, leftCol);

	for (int row = topRow; row <= bottomRow; row++)
	{
		for (int col = leftCol; col <= rightCol; col++)
		{
			if (simData->grid[row][col] == '.')
			{
				emptyTiles++;
			}
			else if (simData->grid[row][col] == '#')
			{
				//Nothing to do here.
			}
			else
			{
				printf("Error: Invalid character in grid %d:%d, bad if you end up here: %c\n", row, col, simData->grid[row][col]);
				//emptyTiles++;
			}
		}
	}

	return emptyTiles;
}

/// <summary>
/// Print the grid to the console
/// </summary>
/// <param name="simData"></param>
void printGrid(SimulationData* simData)
{
    for (int i = 0; i < simData->gridInfo.rows; i++)
	{
	    for (int j = 0; j < simData->gridInfo.cols; j++)
		{
			printf("%c", simData->grid[i][j]);
		}
		printf("\n");
	}
}

/// <summary>
/// Shuffle the order of directions
/// </summary>
/// <param name="simData"></param>
void shuffleOrder(SimulationData* simData)
{
    // Shuffle the order of directions in the opposite order
    int temp = simData->orders.eastOrder;
    simData->orders.eastOrder = simData->orders.westOrder;
    simData->orders.westOrder = simData->orders.southOrder;
    simData->orders.southOrder = simData->orders.northOrder;
    simData->orders.northOrder = temp;
}

/// <summary>
/// Check for neighbours
/// </summary>
/// <param name="simData"></param>
void checkForNeighbours(SimulationData* simData)
{
	//printf("Checking for neighbours\nnorthorder:%d\nsouthorder:%d\n\nwestorder:%d\n\neastorder:%d\n", simData->northOrder, simData->southOrder, simData->westOrder, simData->eastOrder);
    Position position;

	printf("Checking for neighbours\n");

	for (int row = 0; row < simData->gridInfo.rows - 1; row++)
	{
		//printf("Row %d\n", row);
	    for (int col = 0; col < simData->gridInfo.cols - 1; col++)
		{
			//printf("Col %d\n", col);
			if (simData->grid[row][col] == '#')
			{
				//printf("Found %c at %d:%d", simData->grid[row][col],row,col);
				for (int i = 0; i < 8; i++) // Check all 8 directions
				{
					//printf("Checking direction %d\n", i);
					int rowNew = row + simData->searchDirections[i][0];
					int colNew = col + simData->searchDirections[i][1];
					//printf("New row %d, new col %d\n", newRow, newCol);
					if (rowNew >= 0 && rowNew <= simData->gridInfo.rows - 1 && colNew >= 0 && colNew <= simData->gridInfo.cols - 1)
					{
						if (simData->grid[rowNew][colNew] == '#')
						{
							//printf("Found neighbour at %d:%d\n", rowNew, colNew);
						    // Has neighbour
							position.row = row;
							position.col = col;

							checkForMoves (simData, position);
							
							break;
						}
					}
				}
			}
		}
	}
}

/// <summary>
/// Check for possible moves
/// </summary>
/// <param name="simData"></param>
/// <param name="position"></param>
void checkForMoves(SimulationData* simData, Position position)
{
	//printf("Tile %d:%d has neighbours\n", row, col);
	int movePossible = 0;
	int moveFound = 0;

	for (int count = 0; count <= 3; count++)
	{
		movePossible = 1;
		if (count == simData->orders.northOrder && moveFound == 0) // North
		{
			moveFound = checkMove(simData, position, simData->directions.northDirections);
		}
		if (count == simData->orders.southOrder && moveFound == 0) // South
		{
			moveFound = checkMove(simData, position, simData->directions.southDirections);
		}
		if (count == simData->orders.westOrder && moveFound == 0) //West
		{
			moveFound = checkMove(simData, position, simData->directions.westDirections);
		}
		if (count == simData->orders.eastOrder && moveFound == 0) // East
		{
			moveFound = checkMove(simData, position, simData->directions.eastDirections);
		}
	}
}

/// <summary>
/// Check if a move is possible
/// </summary>
/// <param name="simData"></param>
/// <param name="position"></param>
/// <param name="directions"></param>
/// <returns></returns>
int checkMove(SimulationData* simData, Position position, int* directions)
{
    int dx, dy, rowNew, colNew, moveFound = 0;
    for (int count2 = 0; count2 < 5; count2 += 2)
    {
        dx = directions[count2];
        dy = directions[count2 + 1];

        rowNew = position.row + dx;
        colNew = position.col + dy;

        if (rowNew >= 0 && rowNew <= simData->gridInfo.rows - 1 && colNew >= 0 && colNew <= simData->gridInfo.cols - 1)
        {
            if (simData->grid[rowNew][colNew] == '#')
            {
                return moveFound;
            }
        }
    }

    rowNew = position.row + directions[2];
    colNew = position.col + directions[3];
    if (rowNew >= 0 && rowNew <= simData->gridInfo.rows - 1 && colNew >= 0 && colNew <= simData->gridInfo.cols - 1)
    {
        moveFound = 1;
        saveProposedMove(simData, position.row, position.col, rowNew, colNew);
    }

    return moveFound;
}

/// <summary>
/// Save the proposed move
/// </summary>
/// <param name="simData"></param>
/// <param name="row"></param>
/// <param name="col"></param>
/// <param name="newRow"></param>
/// <param name="newCol"></param>
void saveProposedMove(SimulationData* simData, int row, int col, int newRow, int newCol)
{
	simData->proposedMoves[row][col][0] = newRow;
	simData->proposedMoves[row][col][1] = newCol;
	simData->numOfProposedMoves[newRow][newCol] += 1;
	//printf("Proposed move from %d:%d to %d:%d\n", row, col, newRow, newCol);
}

/// <summary>
/// Perform the proposed moves, if possible
/// </summary>
/// <param name="simData"></param>
/// <returns></returns>
int performProposedMoves(SimulationData* simData)
{
	int numOfMoves = 0;
	
	printf("Performing proposed moves\n");


	for (int row = 0; row < simData->gridInfo.rows - 1; row++)
	{
		for (int col = 0; col < simData->gridInfo.cols - 1; col++)
		{
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
					if (simData->grid[newRow][newCol] == '.') // FIXED: Remove the 1 || to enable the check for empty tiles. There is obviously a bug here. Could be related to readFromFile() or the grid allocation. readFromFile() was fixed
					{
						simData->grid[newRow][newCol] = '#';
						simData->grid[row][col] = '.';
						if (simData->grid[newRow][newCol] == '#' && simData->grid[row][col] == '.')
						{
							numOfMoves++;
							//printf("Elf moved from %d:%d to %d:%d\n", row, col, newRow, newCol);
						}
					}
				}
			}
		}
	}
	return numOfMoves;
}

/// <summary>
/// Read the grid from the input file
/// </summary>
/// <param name="simData"></param>
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
			row++;
			col = 0;
		}
		else {
			setGridValue(simData, row, col, ch);
			col++;
		}
	}
	fclose (fp);
}

/// <summary>
/// Set the value of the grid at the specified row and column
/// </summary>
/// <param name="simData"></param>
/// <param name="row"></param>
/// <param name="col"></param>
/// <param name="ch"></param>
void setGridValue(SimulationData* simData, int row, int col, char ch)
{
	int offsetRow = (simData->gridInfo.rows - simData->fileSize.rows) / 2;
	int offsetCol = (simData->gridInfo.cols - simData->fileSize.cols) / 2;
	simData->grid[row + offsetRow][col + offsetCol] = ch;
}

/// <summary>
/// Function to get the size of the grid from the input file
/// </summary>
/// <returns></returns>
int* getGridSize()
{
	FILE* file; errno_t err = fopen_s(&file, "input.txt", "r"); if (err != 0) 
	{ 
		perror("Unable to open file"); 
		return EXIT_FAILURE; 
	} 
	int rows = 0; 
	int cols = 0; 
	int max_cols = 0; 
	char ch; 
	static int size[2] = { 0, 0 };
	// Count the number of rows and columns 
	while ((ch = fgetc(file)) != EOF) 
	{ 
		if (ch == '.' || ch == '#')
		{ 
			cols++; 
		} 
		else if (ch == '\n') 
		{ 
			rows++; 
			if (cols > max_cols) 
			{ 
				max_cols = cols; 
			} 
			cols = 0; 
		} 
	} 
	// Account for the last row if there's no newline at the end of the file 
	if (cols > 0) 
	{ 
		rows++; 
		if (cols > max_cols) 
		{ 
			max_cols = cols; 
		} 
	}

	size[0] = rows;
	size[1] = max_cols;

	return size;
}