/*
 * Variance.cpp
 *
 *  Created on: 19/05/2014
 *      Author: Katti
 */

#include "Variance.h"


Variance::Variance() : ValidationIndex("VAR", internal) {}

Variance::~Variance() { }

double Variance::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){

	double dVar = 0;

	//cout << pAPartition->getPartitionName() << endl;
	for(Partition::itClustersOfPartition itP = pAPartition->begin(); itP != pAPartition->end(); itP++){
		double varPartial = 0;
		Object *centroid = itP->getCentroid();
		for(Cluster::itObjectsOfCluster itC = itP->begin(); itC != itP->end(); itC++){
			//(*(*itC)).print();
			double d = pARelation->getSimilarity()->calculate((*(*itC)), *centroid);			
			varPartial += d;			
		}
		dVar += varPartial;
#ifdef IID
		cout << pAPartition->getPartitionName();
		cout << "\tVAR \tcluster " << itP->getLabel() << " \t(" << itP->getNumberOfObjects() << " objects):\t" << sqrt(varPartial/itP->getNumberOfObjects()) << endl;
#endif
	}

	return sqrt(dVar/pADataset->getNumberOfObjects());
}



double Variance::calculate(Partition &objAPartition1, Partition &objAPartition2){
	//TODO Colocar no relat�rio esse retorno com n�mero qualquer
	return -100;
}
