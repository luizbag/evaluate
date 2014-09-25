/*
 * Euclidean.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vinicius
 */

#ifndef EUCLIDEAN_H_
#define EUCLIDEAN_H_

#include <math.h>

#include "Similarity.h"

/// Represents the calculation of the Euclidean distance
/** Represents the calculation of the Euclidean distance */
class Euclidean : public Similarity {

	public:
		/** Class constructor */
		/** @param  Don't have */
		Euclidean();

		/** Class destructor */
		/** @param  Don't have */
		virtual ~Euclidean();

		/** Calculates the distance Euclidean */
		/** @param Objects used to calculate Euclidean distance */
		/** @return Returns the distance Euclidean between two objects passed as parameter */
		double calculate(const Object &objAObject_1, const Object &objAObject_2);
};

#endif /* EUCLIDEAN_H_ */
