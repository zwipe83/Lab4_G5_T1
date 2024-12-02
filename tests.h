//////////////////////////////////////////////////////////////////////////
// <summary>
// Lab 4 Grade 5 Task, option 3
// Filename: tests.h
// Created on: 2024-12-02 00:00:00
// Author: Samuel Jeffman
// Description: Header file for tests related to elf simulations.
// </summary>
//////////////////////////////////////////////////////////////////////////

#ifndef TESTS_H_
#define TESTS_H_

#include "functions.h"

void testAllocate1DArray();
void testAllocate2DArray();
void testAllocate3DArray();
void testAllocateSimulationData();
//void testCheckForNeighbours();
void testCheckEmptyTiles();
void testPerformProposedMoves();
//void testPrintGrid();
void testReadFromFile();
void testResetArrays();
void testSaveProposedMove();
void testShuffleOrder();
void testStartRound();
void testGetGridSize();
void testCheckForMoves();
//void testCheckMove();
void testSetGridValue();
void testFree1DArray();
void testFree2DArray();
void testFree3DArray();

void runTests();


#endif // TESTS_H_
