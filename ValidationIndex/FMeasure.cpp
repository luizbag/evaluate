/*
 * FMeasure.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: marcus
 */

#include "FMeasure.h"

FMeasure::FMeasure() : ValidationIndex("FM", external) {}


/* Implementation of both inherited methods */
double FMeasure::calculate(Partition &objAPartition1, Partition &objAPartition2){
	Partition::itClustersOfPartition itClass = objAPartition1.begin();
	Partition::itClustersOfPartition itCluster = objAPartition2.begin();

	int n_ij = 0;
	int n_i = itClass->getNumberOfObjects();
	int n_j = itCluster->getNumberOfObjects();
	double recall, precision;

	for (Cluster::itObjectsOfCluster it = itClass->begin(); it != itClass->end(); it++) {
		if (it->operator ->() == (itCluster->find(*it))->operator ->()) {
			n_ij++;
		}
	}

	recall = double(n_ij)/double(n_i);
	precision = double(n_ij)/double(n_j);

	if ((precision + recall) == 0) {
		return 0;
	} else {
		return (2*recall*precision)/(precision + recall);
	}
}

/* This method is to be used in internal validation measures, since CR isn't an internal validation measure
    the call of this method will throw an exception */
double FMeasure::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat�rio esse retorno com n�mero qualquer
	return -100;
}





