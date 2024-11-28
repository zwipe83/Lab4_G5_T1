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

typedef struct
{
    int row;
    int col;

} Position;

typedef struct
{
    int rows;
    int cols;
    int coords;
    int searchDirRows;
    int searchDirCols;
    float factor;

} GridInfo;

typedef struct {
    char** grid;
    int** searchDirections;
    int*** proposedMoves;
    int** numOfProposedMoves;
    int northOrder;
	int southOrder;
	int westOrder;
	int eastOrder;
	int searchDirRows;
	int searchDirCols;
	int* northDirections;
	int* southDirections;
	int* westDirections;
	int *eastDirections;
	GridInfo gridInfo;

} SimulationData;

//extern const int searchDirections[16];
int userInput(int numOfRounds);
char** allocateGrid(int rows, int cols);
int** allocateSearchDirections(int rows, int cols);
int*** allocateProposedMoves(int rows, int cols, int coords);
int** allocateNumOfProposedMoves(int rows, int cols);
SimulationData* allocateSimulationData(GridInfo gridInfo);
void freeSimulationData(SimulationData* data, GridInfo gridInfo);
//void loadInitialState();
void checkForNeighbours(SimulationData* simData);
int checkEmptyTiles(SimulationData* simData);
int performProposedMoves(SimulationData* simData);
void printGrid(SimulationData* simData);
//void printGridToFile();
void readFromFile(SimulationData* simData);
void resetArrays(SimulationData* simData);
void saveProposedMove(SimulationData* simData, int row, int col, int newRow, int newCol);
void shuffleOrder(SimulationData* simData);
int startRound(SimulationData* simData);
int* getGridSize();

void checkForMoves(SimulationData* simData, Position position);
int checkMove(SimulationData* simData, Position position, int* directions);
void resetGrid (SimulationData* simData);

#endif // FUNCTIONS_H_
