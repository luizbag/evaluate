/*
 * Connectivity.cpp
 *
 *  Created on: 12/03/2010
 *      Author: Gustavo
 */

#include "Connectivity.h"


Connectivity::Connectivity() : ValidationIndex("CON",internal) {}

Connectivity::~Connectivity() {
}

double Connectivity::calculate(Partition *pAPartition, RelationSDN *pARelation,	DataSet *pADataSet) {
	double connectivity = 0;
	//cout << pAPartition->getPartitionName() << endl;
	
	for (Partition::itClustersOfPartition itClusterOnPartition = pAPartition->begin(); itClusterOnPartition != pAPartition->end(); itClusterOnPartition++){
		double conPartial = 0;
		for(Cluster::itObjectsOfCluster itObjectsOnCluster1 = (*itClusterOnPartition).begin(); itObjectsOnCluster1 != (*itClusterOnPartition).end(); itObjectsOnCluster1++){
			// vizinhos
			for (int j = 1; j <= pARelation->getNnList()->getNumberOfNn(); j++){
				if (pAPartition->getClusterOf((pARelation->getNnList()->nearestNeighbor(*itObjectsOnCluster1, j))) !=  itClusterOnPartition)
					//connectivity += 1.0/j;
					conPartial += 1.0/j;
			}
		}
		connectivity += conPartial;
#ifdef IID
		cout << pAPartition->getPartitionName();
		cout << "\tCON \tcluster " << itClusterOnPartition->getLabel() << " \t(" << itClusterOnPartition->getNumberOfObjects() << " objects):\t" << conPartial << endl;
#endif
	}

	return connectivity;
}

double Connectivity::calculate(Partition &objAPartition1, Partition &objAPartition2) {
	//TODO Colocar no relat�rio esse retorno com n�mero qualquer
	return -100;
}
