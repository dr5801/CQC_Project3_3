/**
 * Project3.c
 *
 *  Created on: Feb 25, 2017
 *      Author: Drew Rife and Jordan Long
 *
 *  Implements the State Machine table driven design for C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "State_Enum.h"
#include "Interim_Result.h"

#define MAX_SIZE 100  // max input size for the user

/**
 * methods for the state machine
 */
void execute(void);
void startState(void);
void integerState(void);
void decimalState(void);
void endState(void);
void deconstruct(void);

/**
 * holds the information for a State and a function pointer
 */
typedef struct {
	State * state;
	void (* func)(void);
}Machine;

/**
 * Maps the function pointer to the function associated with the State Enum value
 */
Machine MappedStates[] = {
		{START, &startState},
		{INTEGER, &integerState},
		{DECIMAL, &decimalState},
		{END, &endState}
	};

/* interim result used to store the result after going through each state */
InterimResult * result;

/* string pointer for user input */
char * userInput;

/* the current index of userInput */
int indexOfUserInput = 0;

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

	/* execute the table driven state machine */
	execute();

	/* deconstruct all dynamically allocated memory after use */
	deconstruct();

	return 0;
}


/**
 * initializes the result variables and executes the state machine
 */
void execute(void)
{
	result = (InterimResult *)malloc(sizeof(RESULT));

	/* set the default values */
	result->p = 0;
	result->s = 1;
	result->v = 0;

	/* state machine starts in the start state */
	startState();
}

/**
 * handles the functionality of the machine when in start state
 */
void startState(void)
{
	char currentCharacter = *(userInput + indexOfUserInput);

	if(isdigit(currentCharacter))
	{
		result->v = * userInput - '0';
		MappedStates[INTEGER].func();
	}
	else if(currentCharacter == '+')
	{
		MappedStates[INTEGER].func();
	}
	else if(currentCharacter == '-')
	{
		result->s = -1;
		MappedStates[INTEGER].func();
	}
	else if(currentCharacter == '.')
	{
		result->p = 0.1;
		MappedStates[DECIMAL].func();
	}
	else
	{
		MappedStates[END].func();
	}
}

/**
 * handles the functionality of the machine when in integer state
 */
void integerState(void)
{
	indexOfUserInput++;
	char currentCharacter = *(userInput + indexOfUserInput);

	if(isdigit(currentCharacter))
	{
		result->v *= 10;
		result->v += currentCharacter - '0';
		MappedStates[INTEGER].func( );
	}
	else if(currentCharacter == '.')
	{
		result->p = 0.1;
		MappedStates[DECIMAL].func( );
	}
	else if(currentCharacter == '\0')
	{
		MappedStates[END].func( );
	}
	else
	{
		result->v = 0;
		MappedStates[END].func( );
	}
}

/**
 * handles the functionality of the machine when in the decimal state
 */
void decimalState(void)
{
	indexOfUserInput++;
	char currentCharacter = *(userInput + indexOfUserInput);

	if(isdigit(currentCharacter))
	{
		result->v += result->p * ( currentCharacter - '0');
		result->p /= 10;
		MappedStates[DECIMAL].func( );
	}
	else if(currentCharacter == '\0')
	{
		MappedStates[END].func( );
	}
	else
	{
		result->v = 0;
		MappedStates[END].func( );
	}
}

/**
 * prints the results when in the end state
 */
void endState(void)
{
	printf("\n%.3f", result->v * result->s);
}

/**
 * free all pointers and set them to null after use
 */
void deconstruct(void)
{
	free(userInput);
	userInput = NULL;

	free(result);
	result = NULL;
}

