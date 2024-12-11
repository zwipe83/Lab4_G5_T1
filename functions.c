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

/**
 * @brief Read user input
 *
 * @param numOfRounds
 * @return int
 */
int userInput(int numOfRounds)
{
	printf("Enter the number of rounds you would like to simulate: ");
	int i = scanf("%d", &numOfRounds);
	return numOfRounds;
}

/**
 * @brief Read user input mode
 *
 * @param mode
 * @return int
 */
int userInputMode(int mode)
{
	do
	{
		printf("Which mode do we run?(Default is 0)\n0: Slow and steady.\n1: Fast and on the edge. ");
		int i = scanf("%d", &mode);
	} while (mode < 0 || mode > 1);
	return mode;
}

/**
 * @brief Allocate memory for a 1D array
 *
 * @param length
 * @param elementSize
 * @param initialValue
 * @return void*
 */
void* allocate1DArray(int length, size_t elementSize, void* initialValue) // Only handles int(4 Bytes) and char(1 Byte)
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
		else if (elementSize == sizeof(char))
		{
			((char*)array)[i] = *(char*)initialValue;
		}
		else
		{
			printf("Element size not supported: %zu Bytes\n", sizeof(elementSize));
			return NULL;
		}
	}

	return array;
}

/**
 * @brief Allocate memory for a 2D array
 *
 * @param rows
 * @param cols
 * @param elementSize
 * @param initialValue
 * @return void**
 */
void** allocate2DArray(int rows, int cols, size_t elementSize, void* initialValue)
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
		array[i] = (void*)allocate1DArray(cols, elementSize, initialValue);
		if (array[i] == NULL)
		{
			printf("Memory allocation failed\n");
			// Free previously allocated memory
			for (int j = 0; j < i; j++)
			{
				free1DArray(array[j]);
			}
			free(array);
			return NULL;
		}
	}

	return array;
}

/**
 * @brief Allocate memory for a 3D array
 *
 * @param rows
 * @param cols
 * @param depth
 * @param elementSize
 * @param initialValue
 * @return void***
 */
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

/**
 * @brief Free the allocated 1D array
 *
 * @param array
 * @return void
 */
void free1DArray(void* array)
{
	free(array);
}

/**
 * @brief Free the allocated 2D array
 * 
 * @param array
 * @param rows
 * @return void
 */
void free2DArray(void** array, int rows)
{
	int dummy = 0;
	// Free each row
	for (int i = 0; i < rows; i++)
	{
		free1DArray(array[i]);
	}
	// Free the array of pointers
	free(array);
}

/**
 * @brief Free the allocated 3D array
 * 
 * @param array
 * @param rows
 * @param cols
 * @return void
 */
void free3DArray(void*** array, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		free2DArray(array[i], cols);
	}
	free(array);
}

/**
 * @brief Free the allocated simulation data
 *
 * @param simData
 */
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
		free2DArray(simData->searchDirections, simData->gridInfo.searchDirRows); // FIXED: gridInfo contains invalid data. Removed consts from gridInfo struct
	}

	// Free proposedMoves
	if (simData->proposedMoves != NULL)
	{
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

/**
 * @brief Allocate memory for the simulation data
 * 
 * @param gridInfo
 * @param fileSize
 * @return SimulationData*
 */
SimulationData* allocateSimulationData(GridInfo gridInfo, Size fileSize)
{
	SimulationData* data = (SimulationData*)malloc(sizeof(SimulationData));
	if (data == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
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
	data->gridInfo.searchDirRows = gridInfo.searchDirRows;
	data->gridInfo.searchDirCols = gridInfo.searchDirCols;
	data->gridInfo.coords = gridInfo.coords;

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

	data->operations = 0;

	return data;
}

/**
 * @brief Run the simulation
 *
 * @param simData
 * @return int
 */
int startRound(SimulationData* simData)
{
	int numOfMoves = 0;

	// Check for neighbours
	checkForNeighbours(simData);
	numOfMoves = performProposedMoves(simData);
	resetArrays(simData);

	return numOfMoves;
}

/**
 * @brief Reset the arrays
 *
 * @param simData
 * @return void
 */
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

/**
 * @brief Check for empty tiles
 *
 * @param simData
 * @return int
 */
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
				simData->operations++;
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
				simData->operations++;
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
				simData->operations++;
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
		if (!leftFound)
		{
			for (int row = bottom; row >= top; row--)
			{
				simData->operations++;
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
			simData->operations++;
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
			}
		}
	}

	return emptyTiles;
}

/**
 * @brief Print the grid to the console
 *
 * @param simData
 * @return void
 */
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

/**
 * @brief Print the grid to a file
 *
 * @param simData
 * @return void
 */
void printGridToFile(SimulationData* simData)
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "C:/ElfSim/output.txt", "w");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	for (int i = 0; i < simData->gridInfo.rows; i++)
	{
		for (int j = 0; j < simData->gridInfo.cols; j++)
		{
			fprintf(fp, "%c", simData->grid[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

/**
 * @brief Shuffle the order of directions
 *
 * @param simData
 * @return void
 */
void shuffleOrder(SimulationData* simData)
{
    // Shuffle the order of directions in the opposite order
    int temp = simData->orders.eastOrder;
    simData->orders.eastOrder = simData->orders.westOrder;
    simData->orders.westOrder = simData->orders.southOrder;
    simData->orders.southOrder = simData->orders.northOrder;
    simData->orders.northOrder = temp;
}

/**
 * @brief Check for neighbours
 *
 * @param simData
 * @return void
 */
void checkForNeighbours(SimulationData* simData)
{
	Position position = { 0, 0 };

	printf("Checking for neighbours\n");

	for (int row = 0; row < simData->gridInfo.rows - 1; row++)
	{
	    for (int col = 0; col < simData->gridInfo.cols - 1; col++)
		{
			if (simData->grid[row][col] == '#')
			{
				for (int i = 0; i < 8; i++) // Check all 8 directions
				{
					simData->operations++;
					int rowNew = row + simData->searchDirections[i][0];
					int colNew = col + simData->searchDirections[i][1];

					if (rowNew >= 0 && rowNew <= simData->gridInfo.rows - 1 && colNew >= 0 && colNew <= simData->gridInfo.cols - 1)
					{
						if (simData->grid[rowNew][colNew] == '#')
						{
						    // Has neighbour
							position.row = row;
							position.col = col;

							checkForMoves(simData, position);
							
							break;
						}
					}
				}
			}
		}
	}
}

/**
 * @brief Check for moves
 *
 * @param simData
 * @param position
 * @return void
 */
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

/**
 * @brief Check if a move is possible
 *
 * @param simData
 * @param position
 * @param directions
 * @return int
 */
int checkMove(SimulationData* simData, Position position, int* directions)
{
    int dx, dy, rowNew, colNew, moveFound = 0;
    for (int count2 = 0; count2 < 5; count2 += 2)
    {
		simData->operations++;
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
	else
	{
		printf("Move not possible due to grid size constraints. Increase grid size, by increasing gridInfo.factor.\nTerminating application now.");
		system("pause");
		exit(0);
	}

    return moveFound;
}

/**
 * @brief Save the proposed move
 *
 * @param simData
 * @param row
 * @param col
 * @param newRow
 * @param newCol
 * @return void
 */
void saveProposedMove(SimulationData* simData, int row, int col, int newRow, int newCol)
{
	simData->proposedMoves[row][col][0] = newRow;
	simData->proposedMoves[row][col][1] = newCol;
	simData->numOfProposedMoves[newRow][newCol] += 1;
}

/**
 * @brief Perform proposed moves
 *
 * @param simData
 * @return int
 */
int performProposedMoves(SimulationData* simData)
{
	int numOfMoves = 0;
	
	printf("Performing proposed moves\n");

	for (int row = 0; row < simData->gridInfo.rows - 1; row++)
	{
		for (int col = 0; col < simData->gridInfo.cols - 1; col++)
		{
			simData->operations++;
			if (simData->proposedMoves[row][col][0] != -1 && simData->proposedMoves[row][col][1] != -1)
			{
				int newRow = simData->proposedMoves[row][col][0];
				int newCol = simData->proposedMoves[row][col][1];

				if (simData->numOfProposedMoves[newRow][newCol] == 1)
				{
					if (simData->grid[newRow][newCol] == '.') // FIXED: Remove the 1 || to enable the check for empty tiles. There is obviously a bug here. Could be related to readFromFile() or the grid allocation. readFromFile() was fixed
					{
						simData->grid[newRow][newCol] = '#';
						simData->grid[row][col] = '.';
						if (simData->grid[newRow][newCol] == '#' && simData->grid[row][col] == '.')
						{
							numOfMoves++;
						}
					}
				}
			}
		}
	}
	return numOfMoves;
}

/**
 * @brief Read from file
 *
 * @param simData
 * @return void
 */
void readFromFile(SimulationData* simData)
{
	// Read from file
	FILE* fp;
	errno_t err = fopen_s(&fp, "C:/ElfSim/input.txt", "r");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1); // No reason to continue if we can't read the file
	}
	int row = 0, col = 0;
	char ch;

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			setGridValue(simData, row, col, ch);
			col++;
		}
	}
	fclose (fp);
}

/**
 * @brief Set the grid value
 *
 * @param simData
 * @param row
 * @param col
 * @param ch
 * @return void
 */
void setGridValue(SimulationData* simData, int row, int col, char ch)
{
	int offsetRow = (simData->gridInfo.rows - simData->fileSize.rows) / 2;
	int offsetCol = (simData->gridInfo.cols - simData->fileSize.cols) / 2;
	simData->grid[row + offsetRow][col + offsetCol] = ch;
}

/**
 * @brief Get the grid size from the input file
 *
 * @return int*
 */
int* getGridSize()
{
	FILE* file; 
	errno_t err = fopen_s(&file, "C:/ElfSim/input.txt", "r");
	if (err != 0)
	{
		printf("Unable to open file\n");
		return 1;
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