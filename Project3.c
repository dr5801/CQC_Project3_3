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
#include "State_Enum.h"
#include "Interim_Result.h"

#define MAX_SIZE 100

double execute(char * text);
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
double execute(char * text)
{
	char character = *text;

	/**
	 * runs until character is null
	 */
	while(character  && (currentState != END))
	{
		MappedStates[currentState].func(character);
		character = *++text;
	}

	currentState = END;
	MappedStates[currentState].func(character);
	return 0.0;
}

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
	else
	{
		result->v = 0;
		result->s = 0;
		currentState = END;
	}
}

void decimalState(char character)
{
	if(isdigit(character))
	{
		result->v += result->p * (character - '0');
		result->p /= 10;
	}
	else
	{
		result->v = 0;
		result->s = 0;
		currentState = END;
	}
}

void endState(char character)
{
	printf("\n%.6f", result->v * result->s);
}

void deconstruct()
{
	free(userInput);
	userInput = NULL;

	free(result);
	result = NULL;
}

