/*
 * RelationSDN.h
 *
 *  Created on: Jul 28, 2011
 *      Author: Marcus Vinicius
 */

#ifndef RELATIONSDN_H_
#define RELATIONSDN_H_

#include "DataSet.h"
#include "NnList.h"
#include "Similarity.h"
#include "SimilarityMatrix.h"

class DataSet;
class NnList;
class SimilarityMatrix;

/// Represents a pointer for each next classes: SimilarityMatrix, Similarity, DataSet and NnList
/** Represents a pointer for each next classes: SimilarityMatrix, Similarity, DataSet and NnList */
class RelationSDN {

	private:
		SimilarityMatrix *pSimilarityMatrix; ///< pointer to the Similarity Matrix
		Similarity *pSimilarity; ///< pointer to the measure of Similarity
		DataSet *pDataSet; ///< pointer to the DataSet
		NnList *pNnList; ///< pointer to the nearest neighbor list

	public:
		/** Class constructor */
		/** @param  Don't have */
		RelationSDN(Similarity *pASimilarity, DataSet *pADataSet, int iANumNn);

		/** Class destructor */
		/** @param  Don't have */
		virtual ~RelationSDN();

		/** Returns pointer to the Similarity Matrix */
		/** @param Don't have  */
		/** @return Pointer to the Similarity Matrix */
		SimilarityMatrix* getSimilarityMatrix();

		/** Returns pointer to the measure Similarity */
		/** @param Don't have  */
		/** @return Pointer to the Similarity */
		Similarity* getSimilarity();

		/** Returns pointer to the DataSet */
		/** @param Don't have  */
		/** @return Pointer to the DataSet */
		DataSet* getDataSet();

		/** Returns pointer to the nearest neighbor list */
		/** @param Don't have  */
		/** @return Pointer to the Object NnList */
		NnList* getNnList();
};

#endif /* RELATIONSDN_H_ */
