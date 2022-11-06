#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 20 is definitely not correct
#define MAXMEMORY 20

typedef struct coordinate {
    int x;
    int y;
} Coordinate;

typedef struct currentState {
    Coordinate vacuum;
    // Coordinate *dirtyArray;
    // might have to make a new array for every single state unless there's a better way to do this
    int **graph;
    float cost;
    int moves;
    // U for up, D for down, R for right, L for left, C for clean, 
    char* history;
    int dirtySpots;
    
} State;

//this struct might be unnecessary
typedef struct queue {
 State *array;
 int count;
} Queue;

void enqueue(Queue queue, State state);

State dequeue(Queue queue);

void printGraph(int** graph);

Queue* initializeQueue();

// takes an array of coordinates of the dirty tiles and returns a graph, all other tiles are assumed clean 
int** createGraph(Coordinate dirty[MAXMEMORY]);

Coordinate *giveCoordinateArray(int number);

State initializeState(int number, State state);

void printState(State state);

void printGraphWithVacuum(int **graph, Coordinate vacuum);

void push(Queue *stack, State state);

State pop(Queue *stack);

int nextStep(State state);

Coordinate closestPoint(State state);

State copyState(State original, State copy);

State moveState(State state, char direction);

void IDS (State start);

int checkClean(State state);





    // some kind of function for tree/graph/iterative search
