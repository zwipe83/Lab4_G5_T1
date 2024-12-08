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

//Position struct
typedef struct
{
    int row;
    int col;

} Position;

//Size struct
typedef struct
{
	int rows;
	int cols;

} Size;

//GridInfo struct. Contains information about the grid.
typedef struct
{
    int rows;
    int cols;
    int coords;
    int searchDirRows;
    int searchDirCols;
    float factor;

} GridInfo;

//Directions struct. Contains arrays of directions for each direction.
typedef struct
{
    int* northDirections;
    int* southDirections;
    int* westDirections;
    int* eastDirections;

} Directions;

//Orders struct. Contains the order of directions for each direction.
typedef struct
{
    int northOrder;
    int southOrder;
    int westOrder;
    int eastOrder;

} Orders;

//SimulationData struct. Contains all data needed for the simulation.
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

#endif // STRUCTS_H_