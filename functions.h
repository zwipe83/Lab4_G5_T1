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

#include <stddef.h>
#include "structs.h"

int userInput(int numOfRounds);
int userInputMode(int mode);

void* allocate1DArray(int length, size_t elementSize, void* initialValue);
void** allocate2DArray(int rows, int cols, size_t elementSize, void* initialValue);
void*** allocate3DArray(int rows, int cols, int depth, size_t elementSize, void* initialValue);

void free1DArray(void* array);
void free2DArray(void** array, int rows);
void free3DArray(void*** array, int rows, int cols);

SimulationData* allocateSimulationData(GridInfo gridInfo, Size fileSize);
void freeSimulationData(SimulationData* data);

int startRound(SimulationData* simData);
void checkForNeighbours(SimulationData* simData);
int checkEmptyTiles(SimulationData* simData);
int performProposedMoves(SimulationData* simData);
void saveProposedMove(SimulationData* simData, int row, int col, int newRow, int newCol);
void shuffleOrder(SimulationData* simData);
void resetArrays(SimulationData* simData);

void checkForMoves(SimulationData* simData, Position position);
int checkMove(SimulationData* simData, Position position, int* directions);
void setGridValue(SimulationData* simData, int row, int col, char ch);

void printGrid(SimulationData* simData);
void printGridToFile(SimulationData* simData);

void readFromFile(SimulationData* simData);
int* getGridSize();

#endif // FUNCTIONS_H_
