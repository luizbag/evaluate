/*
 * SimilarityMatrix.h
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vinicius
 */

#ifndef SIMILARITYMATRIX_H_
#define SIMILARITYMATRIX_H_

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include <map>

#include "DataSet.h"
#include "Euclidean.h"
#include "Object.h"
#include "Pearson.h"
#include "RelationSDN.h"

class RelationSDN;

using namespace std;

/// Represents a Similarity Matrix, that have a similarity calculated between each two objects of the DataSet
/** Represents a Similarity Matrix, that have a similarity calculated between each two objects of the DataSet */
class SimilarityMatrix {

	private:
		map<Object*, map <Object*, double> > mapMatrix; ///< Map that contains the Similarity between each Object in the DataSet

	public:
		/** Class constructor */
		/** @param  Pointer to the relationSDN */
		SimilarityMatrix(RelationSDN* pARelationSDN);

		/** Class destructor */
		/** @param  Don't have */
		virtual ~SimilarityMatrix();

		/** Prints the Similarity Matrix */
		/** @param Pointer to the relationSDN */
		void print(RelationSDN *pARelationSDN);

		/** Gets the similarity */
		/** @param Objects used to calculate the Similarity */
		/** @return Returns the Similarity between two objects */
		double getSimilarity(Object* objAObject1, Object* objAObject2);
};

#endif /* SIMILARITYMATRIX_H_ */
