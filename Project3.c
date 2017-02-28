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

#include "headers/State_Enum.h"
#include "headers/Interim_Result.h"
#include "headers/Action.h"
#include "headers/Verifier.h"

#define MAX_SIZE 100  // max input size for the user

/**
 * holds the information for a State and a function pointer
 */
typedef struct {
	State currentState;
	bool (* isVerified)(char);
	void (* action)(char);
	State nextState;
}Edge;


/**
 * methods for the state machine
 */
void execute(char * string);
Edge searchForEdge(State currentState, char character);
void deconstruct(void);

Edge edge[] = {
		{START, &digitInputVerifier, &valueIsDigitAction, INTEGER},
		{START, &minusInputVerifier, &negateAction, INTEGER},
		{START, &plusInputVerifier, &noAction, INTEGER},
		{START, &periodInputVerifier, &startFraction, DECIMAL},
		{INTEGER, &digitInputVerifier, &continuingIntegerAction, INTEGER},
		{INTEGER, &periodInputVerifier, &startFraction, DECIMAL},
		{DECIMAL, &digitInputVerifier, &continuingFractionAction, DECIMAL}
};

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
	execute(userInput);

	/* print the result */
	printf("%.3f", result->s * result->v);

	/* deconstruct all dynamically allocated memory after use */
	deconstruct();

	return 0;
}

/**
 * initializes the result variables and executes the state machine
 */
void execute(char *text)
{
	result = (InterimResult *)malloc(sizeof(RESULT));

	/* set the default values */
	result->p = 0;
	result->s = 1;
	result->v = 0;

	/* state machine starts in the start state */
	State currentState = START;

	int index;
	bool invalidInput = false;
	for(index = 0; index < strlen(text) && !invalidInput; index++)
	{
		char character = *(text + index);
		Edge nextEdge = searchForEdge(currentState, character);

		if(nextEdge.nextState != -1)
		{
			nextEdge.action(character);
			currentState = nextEdge.nextState;
		}
		else
		{
			invalidInput = true;
			result->v = 0;
			result->s = 0;
		}
	}
}

/**
 * searches for the next edge
 */
Edge searchForEdge(State currentState, char character)
{
	Edge nextEdge = {9 , NULL, NULL , 9 };

	int size = sizeof(edge)/sizeof(edge[0]);
	int index;
	for(index = 0; index < size; index++)
	{
		if(edge[index].currentState == currentState && edge[index].isVerified(character))
		{
			nextEdge = edge[index];
		}
	}

	if(nextEdge.isVerified == NULL && nextEdge.action == NULL)
	{
		nextEdge.nextState = -1;
	}

	return nextEdge;
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

