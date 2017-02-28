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
void startState(void);
void integerState(void);
void decimalState(void);
void endState(void);
void deconstruct(void);

bool digitInputVerifier(char character);
bool minusInputVerifier(char character);
bool plusInputVerifier(char character);
bool periodInputVerifier(char character);

void valueIsDigitAction(char character);
void negateAction(char character);
void noAction(char character);
void startFraction(char character);
void continuingIntegerAction(char character);
void continuingFractionAction(char character);

Edge edge[] = {
		{START, &digitInputVerifier, &valueIsDigitAction, INTEGER},
		{START, &minusInputVerifier, &negateAction, INTEGER},
		{START, &plusInputVerifier, &noAction, INTEGER},
		{START, &periodInputVerifier, &startFraction, DECIMAL},
		{INTEGER, &digitInputVerifier, &continuingIntegerAction, INTEGER},
		{INTEGER, &periodInputVerifier, &startFraction, DECIMAL},
		{DECIMAL, &digitInputVerifier, &continuingFractionAction, DECIMAL}
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
 * verifies a digit inputted
 */
bool digitInputVerifier(char character)
{
	return isdigit(character);
}

/**
 * verifies if minus sign
 */
bool minusInputVerifier(char character)
{
	return (character == '-');
}

/**
 * verifies if the character is a plus sign
 */
bool plusInputVerifier(char character)
{
	return (character == '+');
}

/**
 * verifies the character is a period
 */
bool periodInputVerifier(char character)
{
	return (character == '.');
}

/**
 * sets the value is digit action
 */
void valueIsDigitAction(char character)
{
	result->v = character - '0';
}

/**
 * sets sign to -1
 */
void negateAction(char character)
{
	result->s = -1;
}

/**
 * does nothing
 */
void noAction(char character) {}

/**
 * Executes an action when an input is '.'
 * Sets the pont to (0.1) since it's a fraction (/10)
 *
 * THIS SHOULD ONLY BE ON THE FIRST TRNASITION TO DECIMAL STATE
 */
void startFraction(char character)
{
	result->p = 0.1;
}

/**
 * When the integer state is repeated
 */
void continuingIntegerAction(char character)
{
	result->v = (10 * result->v) + (character - '0');
}

/**
 * should only be when decimal state is repeated
 */
void continuingFractionAction(char character)
{
	double value = result->p * (character - '0');
	result->v += value;
	result->p /= 10;
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

