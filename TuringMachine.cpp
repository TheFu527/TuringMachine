//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CODE_MAX 1000
#define TAPE_MAX 100
#define NAME_MAX 5

struct inputCode
{
	char currentState[NAME_MAX];
	char currentSymbol;
	char newSymbol;
	char movement;
	char newState[NAME_MAX];
};

void welcomeMessage()
{
	printf("\nTURING MACHINE \n\n");
	printf("Please enter the Turing Machine input code\n");
	printf("Format:\n");
	printf("<current state> <current symbol> <new symbol> <movement,\'r\',\'l\'or\'*\'> <new state>\n");
	printf("Use \'_\' for blank, \'#\' for halting state, \'$\' as current state to stop.\n");
	printf("\n");
}

//Read Turing Machine code from user
int readData(const inputCode inputcode[])
{
	int i;
	for (i = 0; i < CODE_MAX; i++)
	{
		scanf("%s", &inputcode[i].currentState);
		if (!strcmp(inputcode[i].currentState, "$"))
			break;
		scanf(" %c %c %c %s", &inputcode[i].currentSymbol, &inputcode[i].newSymbol, &inputcode[i].movement, &inputcode[i].newState);
	}
	return i;
}

//Read initial tape from user
void readTape(const char paperTape[])
{
	printf("Please enter input the Tape:\n");
	scanf("%s", paperTape);
}

//Read initial machine state from user
void readState(const char state[])
{
	printf("Please enter input initial machine state:\n");
	scanf("%s", state);
}

int main()
{
	int head;
	int tapeSize;
	int tapeLimit;
	int flag;
	char paperTape[TAPE_MAX];
	char state[NAME_MAX];
	inputCode inputcode[CODE_MAX];
	welcomeMessage();
	//Reading data from user
	tapeLimit = readData(inputcode);
	readTape(paperTape);
	readState(state);
	tapeSize = strlen(paperTape);
	//Start trasition operations
	head = 0;
	while (1)
	{
		flag = 0;
		for (int i = 0; i < tapeLimit; i++)
		{
			//Find the match code
			if (!strcmp(state, inputcode[i].currentState) && paperTape[head] == inputcode[i].currentSymbol)
			{
				//Update tape
				paperTape[head] = inputcode[i].newSymbol;
				//Move right
				if (inputcode[i].movement == 'r')
					head++;
				//Move left
				if (inputcode[i].movement == 'l')
					head--;
				//if paperTape area exceed
				if (head == -1)
				{
					for (int j = tapeSize; j > 0; j--)
						paperTape[j] = paperTape[j - 1];
					paperTape[0] = '_';
					tapeSize++;
					paperTape[tapeSize] = '\0';
					head = 0;
				}
				else if (head == tapeSize)
				{
					paperTape[tapeSize] = '_';
					tapeSize++;
					paperTape[tapeSize] = '\0';
				}
				//Update machine state
				strcpy(state, inputcode[i].newState);
				//Print result of this step
				printf("%-10s\t|  State is %-6sHead is %d\n", paperTape, inputcode[i].newState, head);
				//Read the symbol for halting state
				if (!strcmp(state, "#"))
					flag = 2;
				//Success operation
				else
					flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			printf("No code found for current symbol \'%c\' at state \'%s\'. Turing Machine halted!\n", paperTape[head], state);
			break;
		}
		else if (flag == 2)
		{
			printf("Good operations! Turing Machine halted!\n");
			break;
		}
	}
	system("pause");
	return 0;
}



