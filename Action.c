/*
 * Action.c
 *
 *  Created on: Feb 28, 2017
 *      Author: drew
 *
 * Does all the actions
 */

#include "headers/Interim_Result.h"

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
