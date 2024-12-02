//////////////////////////////////////////////////////////////////////////
// <summary>
// Lab 4 Grade 5 Task, option 3
// Filename: structs.h
// Created on: 2024-12-01 00:00:00
// Author: Samuel Jeffman
// Description: Header file for structs related to elf simulations.
// </summary>
//////////////////////////////////////////////////////////////////////////

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct
{
    int row;
    int col;

} Position;

typedef struct // TODO: Could be made const
{
	int rows;
	int cols;

} Size;

typedef struct
{
    int rows;
    int cols;
    const int coords;
    const int searchDirRows;
    const int searchDirCols;
    float factor;

} GridInfo;

typedef struct // TODO: Could be made const
{
    int* northDirections;
    int* southDirections;
    int* westDirections;
    int* eastDirections;

} Directions;

typedef struct
{
    int northOrder;
    int southOrder;
    int westOrder;
    int eastOrder;

} Orders;

typedef struct 
{
    char** grid;
    int** numOfProposedMoves;
    int** searchDirections;
    int*** proposedMoves;
    GridInfo gridInfo;
	Directions directions;
	Orders orders;
	Size fileSize;

} SimulationData;

#endif /* STRUCTS_H_ */