#include "index.h"

int main()
{


	// Coordinate* dirty2 = giveCoordinateArray(2);
	
	// int** graph2;

	// graph2= createGraph(dirty2);

	// printGraph(graph2);

	// Queue *queue = initializeQueue();

	State state1;
	
	state1 = initializeState(1, state1);

	// printState(state1);


	// // printf("coordinates of the closest point are %d, %d\n", smallest.y, smallest.x);

	// char *test = malloc(sizeof (char)* 10);
	// for (int i=0; i<10; i++)
	// {
	// 	test[i] = i+65;
	// }
	// printf("test is %s\n", test);
	// test = test+1;
	// printf(" test is %s now \n", test);

	// printf("testintesting\n");


	IDS(state1);

	State state2;

	state2 = initializeState(2, state2);

	IDS(state2);
	
}

