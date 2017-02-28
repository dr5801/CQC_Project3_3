/*
 * Verifier.c
 *
 *  Created on: Feb 28, 2017
 *      Author: drew
 */

#include "headers/Verifier.h"
#include <ctype.h>

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
