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

#define MAX_SIZE 100

double execute(char * text);


/**
 * Runs the program and gets the user input
 */
int main(void)
{
	char * userInput = malloc(sizeof(char) * MAX_SIZE);
	printf("Please enter your number :");

	fgets(userInput, MAX_SIZE, stdin);

	/* remove the newline character added from fgets */
	userInput[strcspn(userInput, "\n")] = 0;

	execute(userInput);

	printf("The string length is -> %d", strlen(userInput));


	printf("\n This is your number -> %s", userInput);
}


double execute(char * text)
{
	char character = *text;


	return 0.0;
}
