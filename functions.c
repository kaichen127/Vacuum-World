// pseudo code for graph vs tree search:
// unction Tree-Search(problem, fringe) returns a solution, or failure 
// fringe = Insert(Make-Node(Initial-State[problem]), fringe) 
// loop do 
// if fringe is empty then return failure 
// node = Remove-Front(fringe) 
// if Goal-Test(problem, State(node)) then return node 
// fringe = InsertAll(Expand(node, problem), fringe) 
// end 
 
// function Graph-Search(problem, fringe) returns a solution, or failure 
// closed = an empty set 
// fringe = Insert(Make-Node(Initial-State[problem]), fringe) 
// loop do 
// if fringe is empty then return failure 
// node = Remove-Front(fringe) 
// if Goal-Test(problem, State[node]) then return node 
// if State[node] is not in closed then 
// add State[node] to closed 
// fringe = InsertAll(Expand(node, problem), fringe) 
// end 

// idea: 
// need to create fringe

#include "index.h"

void printGraph(int** graph)
{
    	for (int i= 0; i<4; i++)
	{
		for (int j=0; j<5; j++)
		{
			printf("%d ", graph[i][j]);
			// printf("(%d, %d) ", i, j);
		}
		printf("\n");

	}
	printf("\n");
}

int** createGraph(Coordinate dirty[MAXMEMORY])
{
	int **array; 
	if (array = malloc(4 * sizeof(int*)))
	{
	}
	else
	{
		printf("not enough memory \n");
	}

	for (int i=0; i<4; i++)
	{
		array[i] = malloc(5*sizeof(int));
		for (int j=0; j<5; j++)
		{
			array[i][j]=0;
		}
	}

	for (int i=0; i<MAXMEMORY; i++)
	{
		if (dirty[i].x == -1 || dirty[i].y == -1 )
		{
			break;
		}
		else
		{
			array[dirty[i].y][dirty[i].x] = 1;
		}
	}

	return array;
}

Coordinate *giveCoordinateArray(int number)
{
	if (number ==1)
	{
		Coordinate *array = malloc(sizeof(Coordinate) * 4);
		array[0].x=1;
		array[0].y=0;
		array[1].x=3;
		array[1].y=1;
		array[2].x=4;
		array[2].y=2;
		array[3].x=-1;
		array[3].y=-1;
		// (1,2), (2,4), (3,5). 
		return array;

	}
	if (number ==2)
	{
		Coordinate *array = malloc(sizeof(Coordinate) * 5);
		array[0].x=1;
		array[0].y=0;
		array[1].x=0;
		array[1].y=1;
		array[2].x=3;
		array[2].y=1;
		array[3].x=2;
		array[3].y=2;
		array[4].x=-1;
		array[4].y=-1;
		// (1,2), (2,1), (2,4), (3,3). 
		return array;

	}

}

Queue *initializeQueue()
{
	Queue *queue = malloc(sizeof(Queue));
	queue->count=0;
	queue->array = malloc(sizeof(State) * MAXMEMORY);
	return queue;
}

void enqueue(Queue queue, State state)
{
	queue.array[queue.count]=state;
	queue.count++;
}

State dequeue(Queue queue)
{
	if (queue.count == 0)
	{
		exit;
	}
	queue.count--;
	State state= queue.array[0];
	queue.array++;
	return state;
}

State initializeState(int number, State state)
{
	int** graph;
	Coordinate* dirty;
	if (number == 1)
	{
	dirty = giveCoordinateArray(number);
	graph = createGraph(dirty);
	state.vacuum.x=1;
	state.vacuum.y=1;
	state.dirtySpots = 3;
	// state.dirtyArray=dirty;
	}
	if (number == 2)
	{
	dirty = giveCoordinateArray(number);
	graph = createGraph(dirty);

	state.vacuum.x=1;
	state.vacuum.y=2;
	state.dirtySpots = 4;
	// state.dirtyArray=dirty;
	}
	state.cost=0;
	state.moves=0;
	state.graph=graph;
	state.history = malloc (sizeof(char) * MAXMEMORY);
	// for (int i=0; i < MAXMEMORY; i++)
	// {
	// 	state.history[i] = 32;
	// }
	return state;
}

//now with 100% more vacuum!!
void printGraphWithVacuum(int **graph, Coordinate vacuum)
{
	    for (int i= 0; i<4; i++)
	{
		for (int j=0; j<5; j++)
		{
			if (i==vacuum.y && j==vacuum.x)
			{
				if (graph[i][j]==1)
				{
					printf("V ");

				}
				if (graph[i][j]==0)
				{
					printf("v ");
				}
			}
			else
			{
				printf("%d ", graph[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printState(State state)
{
	printf("-----------------\n");
	printGraphWithVacuum(state.graph, state.vacuum);
	printf("COST IS : %.1f\n", state.cost);
	// printf("NUMBER OF MOVES IS %d\n", state.moves);
	printf("HISTORY IS : ");
	for (int i=0; i<state.moves; i++)
	{
	printf("%c ", state.history[i]);

	}
	printf("\n-----------------\n");
}

//scanning the whole graph and finding the closest dirty point
Coordinate closestPoint(State state)
{
	Coordinate smallest, distance;
	smallest.x = 999;
	smallest.y = 999;
	distance.x = 999;
	distance.y = 999;
	float smallestCost = 999;
    for (int i= 0; i<4; i++)
	{
		for (int j=0; j<5; j++)
		{
			//calculating the distance for every single 1 on the board. 
			if (state.graph[i][j]==1)
			{
				float totalCost = 0;
				// printf("found point with coordinates (y,x) = (%d, %d)\n", i, j);
				distance.y= state.vacuum.y - i;
				distance.x= j - state.vacuum.x ;
				// printf("distance is (y,x) = (%d, %d)\n", distance.y, distance.x);

			// positive y, go up
				if (distance.y >= 0)
				{
					totalCost = totalCost + (0.8 * distance.y);
				}
			//negative y, go down
				else if (distance.y < 0)
				{
					totalCost = totalCost - (0.7 * distance.y);
				}
			//positive x, right
				if (distance.x >= 0)
				{
					totalCost = totalCost + (0.9 * distance.x);
				}
			//negative x, left
				else if (distance.x < 0)
				{
					totalCost = totalCost - (distance.x);
				}
				// printf("total cost is %f\n", totalCost);
			//tiebreak, row numbers first then column numbers
				if (totalCost == smallestCost)
				{
					if (j < smallest.x )
					{
						smallest.x=j;
						smallest.y=i;
					}
					else if (j == smallest.x)
					{
						if (i < smallest.y)
						{
							smallest.x=j;
							smallest.y=i;
						}
					}
				}
			//if new smallest distance is found
				if (totalCost < smallestCost)
				{
					smallestCost = totalCost;
					smallest.x = j;
					smallest.y= i;
				}

			}
		}

	}
	if (smallest.x == 999|| smallest.y ==999)
	{
		printf("everything is clean!\n");
		return smallest;
	}
	return smallest;

}

// returns 1, 2, 3, 4, 5, depending on which direction the vacuum should go or if it should clean
int nextStep(State state)
{

}

// given the coordinate closest to the vacuum, this function should move towards it by moving rows first and then columns


void push(Queue* stack, State state)
{
	stack->array[stack->count]=state;
	stack->count++;
}

State pop(Queue* stack)
{
	if (stack->count == 0)
	{
		printf("nothing to pop!\n");
		exit;
	}
	stack->count--;
	State state= stack->array[stack->count];
	return state;
}

int expand(Queue *stack, State state)
{
	// y is greater than 0, can expand up (y -- )
	int i=0;
	if (state.vacuum.y > 0)
	{
		push(stack, moveState(state, 'U'));
		i++;
	}
	if (state.vacuum.y < 3)
	{
		push(stack, moveState(state, 'D'));
		i++;
	}
	if (state.vacuum.x > 0)
	{
		push(stack, moveState(state, 'L'));
		i++;
	}
	if (state.vacuum.x < 4)
	{
		push(stack, moveState(state, 'R'));
		i++;
	}
	push(stack, moveState(state, 'S'));
	i++;
	return i;
	//return the number of expansions
}

void IDS (State start)
{
	// for int i until maxmem, DFS to depth 1
	int i = 1;
	printf("-----------------\n");
	printf("FIRST 5 STATES: \n");
	printf("-----------------\n");
	Queue *stack = initializeQueue();
	for (i; i < MAXMEMORY ; i++)
	{

		push(stack, start);

		// printf("stack count is %d\n", stack->count);

		//could be a source of a bug. is stack-> count dynamic ?
		//going through the whole stack for candidates to expand
		int stackCount = stack->count;
		for (int j=0; j< stackCount; j++)
		{

			//pop the state at the top of the stack, check to see if should expand
			State currentState = pop(stack);

			// ?????
			if (currentState.dirtySpots < start.dirtySpots)
			{
				start = currentState;
				if(checkClean(start) == 0)
				{
					break;
				}
			}

			//comment out later
			// printState(currentState);

			if ( i == 1 && j <5 )
			{
				printState(currentState);
			}

			// j++;
			//expand if it's close to the node
			if (currentState.moves < i)
			{
				j = j - expand(stack, currentState);
				// need to increment j somehow by the number of expansions
			}
		}
		if(checkClean(start) == 0)
		{
			printf("*****************\n");
			printf("SOLUTION: \n");
			printf("*****************\n");
			printState(start);
			break;
		}

	}
}

State copyState(State original, State copy)
{
	//copying and making memory for a copy of the graph
	int **copyArray = malloc(4 * sizeof(int*));
	for (int i=0; i<4; i++)
	{
		copyArray[i] = malloc(5*sizeof(int));
		for (int j=0; j<5; j++)
		{
			copyArray[i][j]=original.graph[i][j];
		}
	}
	copy.graph = copyArray;
	copy.history = malloc (sizeof(char) * MAXMEMORY);
	strcpy(copy.history, original.history);
	int moves = original.moves;
	copy.moves = moves;
	int dirtySpots = original.dirtySpots;
	copy.dirtySpots = dirtySpots;
	float cost = original.cost;
	copy.cost = cost;
	Coordinate copyVacuum;
	copyVacuum.x = original.vacuum.x;
	copyVacuum.y = original.vacuum.y;
	copy.vacuum = copyVacuum;
	return copy;
	
}

State moveState(State state, char direction)
{
	State newState;
	newState = copyState(state, newState);
	if (direction == 'U')
	{
		if (newState.vacuum.y == 0)
		{
			printf("Going out of bounds!\n");
			exit;
		}
		else 
		{
			newState.vacuum.y--;
			newState.cost = newState.cost + 0.8;
			newState.history[newState.moves]='U';
			newState.moves++;
		}
	}
	if (direction == 'D')
	{
			if (newState.vacuum.y == 3)
		{
			printf("Going out of bounds!\n");
			exit;
		}
		else 
		{
			newState.vacuum.y++;
			newState.cost = newState.cost + 0.7;
			newState.history[newState.moves]='D';
			newState.moves++;
		}	
	}
	if (direction == 'L')
	{
			if (newState.vacuum.x == 0)
		{
			printf("Going out of bounds!\n");
			exit;
		}
		else 
		{
			newState.vacuum.x--;
			newState.cost = newState.cost + 1;
			newState.history[newState.moves]='L';
			newState.moves++;
		}
		
	}
	if (direction == 'R')
	{
			if (newState.vacuum.x == 4)
		{
			printf("Going out of bounds!\n");
			exit;
		}
		else 
		{
			newState.vacuum.x++;
			newState.cost = newState.cost + 0.9;
			newState.history[newState.moves]='R';
			newState.moves++;
		}
		
	}
	if (direction == 'S')
	{
		if (newState.graph[newState.vacuum.y][newState.vacuum.x] == 1)
		{
			newState.graph[newState.vacuum.y][newState.vacuum.x] = 0;
			newState.history[newState.moves]='S';
			newState.dirtySpots --;
		}
		else 
		{
			newState.history[newState.moves]='s';
		}
		newState.cost += 0.6;
		newState.moves ++;
		if (checkClean(newState) == 0)
		{
			//finished search!
			// printf("completed search:\n");
			// printState(newState);
			exit;
		}
	}
		return newState;
	}

	//returns the number of dirty squares
	// int checkClean(State state)
	// {
	// 	int i=0;
	// 	for (int i=0; i<4; i++)
	// 	{
	// 		for (int j=0; j<5; j++)
	// 		{
	// 			if (state.graph[i][j] == 1)
	// 			{
	// 				i++;
	// 			}
	// 		}
	// 	}	
	// 	printf("checkclean is %d\n", i);
	// 	return i;
	// }

	int checkClean(State state)
	{
		return state.dirtySpots;
	}