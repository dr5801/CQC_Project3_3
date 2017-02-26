/**
 * Project3.c
 *
 *  Created on: Feb 25, 2017
 *      Author: Drew Rife and Jordan Long
 *
 *  Implements the State Machine design for C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "State_Enum.h"
#include "Interim_Result.h"

#define MAX_SIZE 100

void execute(char * text);
void startState(char character);
void integerState(char character);
void decimalState(char character);
void endState(char character);
void initialize();
void deconstruct();

typedef struct {
	State * state;
	void (* func)(char);
}Machine;

Machine MappedStates[] = {
		{START, &startState},
		{INTEGER, &integerState},
		{DECIMAL, &decimalState},
		{END, &endState}
	};

InterimResult * result;
State currentState;

char * userInput;
bool endStatePrinted = false;

/**
 * Runs the program and gets the user input
 */
int main(void)
{
	userInput = malloc(sizeof(char) * MAX_SIZE);
	printf("Please enter your number :");

	fgets(userInput, MAX_SIZE, stdin);

	/* remove the newline character added from fgets */
	userInput[strcspn(userInput, "\n")] = 0;

	initialize();
	execute(userInput);
	deconstruct();

	return 0;
}

/**
 * initialize the system
 */
void initialize()
{
	result = (InterimResult *)malloc(sizeof(RESULT));

	/* set the default values */
	result->p = 1.0;
	result->s = 1;
	result->v = 0;

	currentState = START;
}

/**
 * executes the state machine
 */
void execute(char * text)
{
	char character = *text;


	/**
	 * runs until character is null
	 */
	while(currentState != END)
	{
		MappedStates[currentState].func(character);
		character = *++text;
	}

	MappedStates[currentState].func(character);
}

/**
 * handles the functionality of the machine when in start state
 */
void startState(char character)
{
	if(isdigit(character))
	{
		result->v = character - '0';
		currentState = INTEGER;
	}
	else if(character == '+')
	{
		currentState = INTEGER;
	}
	else if(character == '-')
	{
		result->s = -1;
		currentState = INTEGER;
	}
	else if(character == '.')
	{
		result->p = 0.1;
		currentState = DECIMAL;
	}
	else
	{
		currentState = END;
	}
}

/**
 * handles the functionality of the machine when in integer state
 */
void integerState(char character)
{
	if(isdigit(character))
	{
		result->v *= 10;
		result->v += character - '0';
	}
	else if(character == '.')
	{
		result->p = 0.1;
		currentState = DECIMAL;
	}
	else if(character == '\0')
	{
		currentState = END;
	}
	else
	{
		result->v = 0;
		currentState = END;
	}
}

/**
 * handles the functionality of the machine when in the decimal state
 */
void decimalState(char character)
{
	if(isdigit(character))
	{
		result->v += result->p * (character - '0');
		result->p /= 10;
	}
	else if(character == '\0')
	{
		currentState = END;
	}
	else
	{
		result->v = 0;
		currentState = END;
	}
}

/**
 * prints the results when in the end state
 */
void endState(char character)
{
	printf("\n%.3f", result->v * result->s);
	endStatePrinted = true;
}

/**
 * free all pointers and set them to null after use
 */
void deconstruct()
{
	free(userInput);
	userInput = NULL;

	free(result);
	result = NULL;
}

