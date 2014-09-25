/*
 * Variance.h
 *
 *  Created on: 12/03/2010
 *      Author: Gustavo
 */

#ifndef VARIANCE_H_
#define VARIANCE_H_

#include "../DataSet.h"
#include "../Partition.h"
#include "../ValidationIndex.h"

using namespace std;

/**
 *  @author Katti Faceli
 *  @since 10/05/2014
 *  @version 1.0
 */

/* This class is responsible for implementing internal validation of the Index of Intra-cluster Variance.
 * This index indicates the degree of compactness of a partition */
class Variance:public ValidationIndex {
public:
	/** Does nothing */
	/** @param Don't have any parameter */
	Variance();
	virtual ~Variance();

	/** Return value of deviation from parameter partition*/
	/** @param Partition, RelationSDN and DataSet */
	/** @return Value deviation*/
	virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataSet);

	/** Does nothing */
	virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
};

#endif /* VARIANCE_H_ */
