//////////////////////////////////////////////////////////////////////////
// <summary>
// Lab 4 Grade 5 Task, option 3
// Filename: tests.c
// Created on: 2024-12-02 00:00:00
// Author: Samuel Jeffman
// Description: Test file for elf simulations.
// </summary>
//////////////////////////////////////////////////////////////////////////

#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/// <summary>
/// Test function for allocate1DArray()
/// </summary>
void testAllocate1DArray()
{
	int length = 5;
	int initialValue = 11;
	int* array = allocate1DArray(length, sizeof(int), &initialValue);
	for (int i = 0; i < length; i++)
    {
        assert(array[i] == 11 && "testAllocate1DArray(): Array element is not equal to 11");
    }

	free1DArray(array);
}

/// <summary>
/// Test function for allocate2DArray()
/// </summary>
void testAllocate2DArray()
{
	int rows = 5;
	int cols = 5;
	int initialValue = 22;
	int** array = allocate2DArray(rows, cols, sizeof(int), &initialValue);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			assert(array[i][j] == 22 && "testAllocate2DArray(): Array element is not equal to 22");
		}
	}

	free2DArray(array, rows);
}

/// <summary>
/// Test function for allocate3DArray()
/// </summary>
void testAllocate3DArray()
{
	int rows = 5;
	int cols = 5;
	int depth = 5;
	int initialValue = 33;
	int*** array = allocate3DArray(rows, cols, depth, sizeof(int), &initialValue);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < depth; k++)
			{
				assert(array[i][j][k] == 33 && "testAllocate3DArray(): Array element is not equal to 33");
			}
		}
	}

	free3DArray(array, rows, cols);
}

/// <summary>
/// Test function for allocateSimulationData()
/// </summary>
void testAllocateSimulationData()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	assert(simData != NULL && "testAllocateSimulationData(): SimulationData is NULL");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for checkEmptyTiles()
/// </summary>
void testCheckEmptyTiles()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	int emptyTiles = checkEmptyTiles(simData);
	assert(emptyTiles == 2871 && "testCheckEmptyTiles(): Empty tiles should be 2871");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for performProposedMoves()
/// </summary>
void testPerformProposedMoves()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	int numOfMoves = performProposedMoves(simData);
	assert(numOfMoves == 0 && "testPerformProposedMoves(): Number of moves should be 0");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for readFromFile()
/// </summary>
void testReadFromFile()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	assert(simData->grid != NULL && "testReadFromFile(): Grid should not be NULL");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for resetArrays()
/// </summary>
void testResetArrays()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	simData->numOfProposedMoves[0][0] = 100;
	simData->numOfProposedMoves[simData->gridInfo.rows-1][simData->gridInfo.cols - 1] = 100;
	simData->proposedMoves[0][0][0] = 100;
	simData->proposedMoves[simData->gridInfo.rows-1][simData->gridInfo.cols-1][0] = 100;
	resetArrays(simData);
	assert(simData->numOfProposedMoves != NULL && "testResetArrays(): numOfProposedMoves should not be NULL");
	assert(simData->numOfProposedMoves[0][0] == 0 && "testResetArrays(): numOfProposedMoves should be 0");
	assert(simData->numOfProposedMoves[simData->gridInfo.rows-1][simData->gridInfo.cols-1] == 0 && "testResetArrays(): numOfProposedMoves should be 0");
	assert(simData->proposedMoves[0][0][0] == -1 && "testResetArrays(): proposedMoves should be -1");
	assert(simData->proposedMoves[simData->gridInfo.rows - 1][simData->gridInfo.cols - 1][0] == -1 && "testResetArrays(): proposedMoves should be -1");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for saveProposedMove()
/// </summary>
void testSaveProposedMove()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	saveProposedMove(simData, 0, 0, 1, 1);
	assert(simData->proposedMoves[0][0][0] == 1 && "testSaveProposedMove(): proposedMoves should be 1");
	assert(simData->proposedMoves[0][0][1] == 1 && "testSaveProposedMove(): proposedMoves should be 1");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for shuffleOrder()
/// </summary>
void testShuffleOrder()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	shuffleOrder(simData);
	assert(simData->orders.northOrder == 3 && "testShuffleOrder(): northOrder should not be 0");
	assert(simData->orders.southOrder == 0 && "testShuffleOrder(): southOrder should not be 0");
	assert(simData->orders.westOrder == 1 && "testShuffleOrder(): westOrder should not be 0");
	assert(simData->orders.eastOrder == 2 && "testShuffleOrder(): eastOrder should not be 0");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for startRound()
/// </summary>
void testStartRound()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	int numOfMoves = startRound(simData);
	assert(numOfMoves == 756 && "testStartRound(): Number of moves should be 756");
	shuffleOrder(simData);
	numOfMoves = startRound(simData);
	assert(numOfMoves == 581 && "testStartRound(): Number of moves should be 581");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for getGridSize()
/// </summary>
void testGetGridSize()
{
	int* gridSize = getGridSize();
	assert(gridSize[0] == 75 && "testGetGridSize(): Rows should be 75");
	assert(gridSize[1] == 75 && "testGetGridSize(): Cols should be 75");
}

/// <summary>
/// Test function for checkForMoves()
/// </summary>
void testCheckForMoves()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	int numOfMoves = startRound(simData);
	assert(simData->numOfProposedMoves[0][0] == 0 && "testCheckForMoves(): numOfProposedMoves should be 0");
	assert(simData->numOfProposedMoves[simData->gridInfo.rows-1][simData->gridInfo.cols - 1] == 0 && "testCheckForMoves(): numOfProposedMoves should be 0");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for setGridValue()
/// </summary>
void testSetGridValue()
{
	GridInfo gridInfo = { 0,0,2,8,2,1 };
	Size fileSize;
	int* gridSize = getGridSize();
	fileSize.rows = gridSize[0];
	fileSize.cols = gridSize[1];
	gridInfo.factor = 3;
	gridInfo.rows = gridSize[0] * gridInfo.factor;
	gridInfo.cols = gridSize[1] * gridInfo.factor;
	SimulationData* simData = allocateSimulationData(gridInfo, fileSize);
	readFromFile(simData);
	setGridValue(simData, 0, 0, 'X');
	int offsetRow = (simData->gridInfo.rows - simData->fileSize.rows) / 2;
	int offsetCol = (simData->gridInfo.cols - simData->fileSize.cols) / 2;
	assert(simData->grid[0+offsetRow][0+offsetCol] == 'X' && "testSetGridValue(): Grid value should be X");
	freeSimulationData(simData);
}

/// <summary>
/// Test function for free1DArray()
/// </summary>
void testFree1DArray()
{
	int length = 5;
	int initialValue = 11;
	int* array = allocate1DArray(length, sizeof(int), &initialValue);
	free1DArray(array);
	array = NULL;
	assert(array == NULL && "testFree1DArray(): Array should be NULL");
}

/// <summary>
/// Test function for free2DArray()
/// </summary>
void testFree2DArray()
{
	int rows = 5;
	int cols = 5;
	int initialValue = 22;
	int** array = allocate2DArray(rows, cols, sizeof(int), &initialValue);
	free2DArray(array, rows);
	array = NULL;
	assert(array == NULL && "testFree2DArray(): Array should be NULL");
}

/// <summary>
/// Test function for free3DArray()
/// </summary>
void testFree3DArray()
{
	int rows = 5;
	int cols = 5;
	int depth = 5;
	int initialValue = 33;
	int*** array = allocate3DArray(rows, cols, depth, sizeof(int), &initialValue);
	free3DArray(array, rows, cols);
	array = NULL;
	assert(array == NULL && "testFree3DArray(): Array should be NULL");
}

/// <summary>
/// Run all tests
/// </summary>
void runTests()
{
	testAllocate1DArray();
	testAllocate2DArray();
	testAllocate3DArray();
	testAllocateSimulationData();
	testCheckEmptyTiles();
	testPerformProposedMoves();
	testReadFromFile();
	testResetArrays();
	testSaveProposedMove();
	testShuffleOrder();
	testStartRound();
	testGetGridSize();
	testCheckForMoves();
	testSetGridValue();
	testFree1DArray();
	testFree2DArray();
	testFree3DArray();
}