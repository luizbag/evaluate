/*
 * Similarity.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vinicius
 */

#ifndef SIMILARITY_H_
#define SIMILARITY_H_

#include "Object.h"

/// Represents the calculation of some similarity (Pearson or Euclidean)
/** Represents the calculation of some similarity (Pearson or Euclidean) */
class Similarity {

	protected:
		const string sSimilarityName;
		const string sSimilarityShortName;
		bool bSimilarity; ///< True if the measure is similarity and false if it is dissimilarity

	public:
		/** Class constructor */
		/** @param  Don't have */
		Similarity(std::string sASimilarityName, std::string sASimilarityShortName, bool bASimilarity);

		virtual ~Similarity() {};

		/** Virtual method: Each Similarity class has this method to calculate the measures of Similarity */
		/** @param Patterns used to calculate the Similarity */
		/** @return Returns the Similarity between two patterns */
		virtual double calculate(const Object &objAObject_1, const Object &objAObject_2) = 0;

		/** Gets the type of Similarity (similarity or dissimilarity) */
		/** @param Don't have */
		/** @return Returns true if the measure is similarity and false if it is dissimilarity */
		bool isSimilarity();

		string getSimilarityName();

		string getSimilarityShortName();
};

#endif /* SIMILARITY_H_ */
