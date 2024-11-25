//////////////////////////////////////////////////////////////////////////
// <summary>
// Lab 4 Grade 5 Task, option 3
// Filename: functions.h
// Created on: 2024-11-23 00:00:00
// Author: Samuel Jeffman
// Description: Header file for functions related to elf simulations.
// </summary>
//////////////////////////////////////////////////////////////////////////

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef struct {
    char** grid;
	int** hasNeighbours;
    int** searchDirections;
    int*** proposedMoves;
    int** numOfProposedMoves;
    int northOrder;
	int southOrder;
	int westOrder;
	int eastOrder;
    int rows;
	int cols;
	int searchDirRows;
	int searchDirCols;
	int* northDirections;
	int* southDirections;
	int* westDirections;
	int* eastDirections;

} SimulationData;

//extern const int searchDirections[16];
int userInput(int numOfRounds);
char** allocateGrid(int rows, int cols);
int** allocateSearchDirections(int rows, int cols);
int*** allocateProposedMoves(int rows, int cols, int coords);
int** allocateNumOfProposedMoves(int rows, int cols);
SimulationData* allocateSimulationData(int rows, int cols, int coords, int searchDirRows, int searchDirCols);
void freeSimulationData(SimulationData* data, int rows, int cols, int searchDirRows);
//void loadInitialState();
void checkForNeighbours();
int calculateEmptyTiles();
int performProposedMoves(SimulationData* simData);
void printGrid();
void printGridToFile();
void readFromFile(SimulationData* simData);
void resetArrays(SimulationData* simData);
void saveProposedMove(SimulationData* simData, int row, int col, int newRow, int newCol);
void shuffleOrder(SimulationData* simData);
int startRound();

#endif // FUNCTIONS_H_
