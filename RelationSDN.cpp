/*
 * RelationSDN.cpp
 *
 *  Created on: Jul 28, 2011
 *      Author: Marcus Vinicius
 */

#include "RelationSDN.h"

RelationSDN::RelationSDN(Similarity *pASimilarity, DataSet *pADataSet, int iANumNn) :
	pSimilarity(pASimilarity),
	pDataSet(pADataSet)
{
	pSimilarityMatrix = new SimilarityMatrix(this);
	pNnList = new NnList(this, iANumNn);
}

RelationSDN::~RelationSDN() {
	delete pSimilarityMatrix;
	delete pNnList;
}

SimilarityMatrix* RelationSDN::getSimilarityMatrix(){
	return pSimilarityMatrix;
}

Similarity* RelationSDN::getSimilarity(){
	return pSimilarity;
}

DataSet* RelationSDN::getDataSet(){
	return pDataSet;
}

NnList* RelationSDN::getNnList(){
	return pNnList;
}
