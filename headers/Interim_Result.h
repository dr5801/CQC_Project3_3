/*
 * Interim_Result.h
 *
 *  Created on: Feb 25, 2017
 *      Author: drew
 */

#ifndef INTERIM_RESULT_H_
#define INTERIM_RESULT_H_

typedef struct interimResult{
	double p;
	int s;
	double v;
}InterimResult, *RESULT;

/* interim result used to store the result after going through each state */
InterimResult * result;

#endif /* INTERIM_RESULT_H_ */
