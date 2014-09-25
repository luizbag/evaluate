/*
 * Deviation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: Gustavo
 */

#include "Deviation.h"


Deviation::Deviation() : ValidationIndex("DEV", internal) {}

Deviation::~Deviation() { }

double Deviation::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){

	double dDev = 0;


	//walk all cluster from partition
	/*TODO MUDADO
	for(Partition::itClustersOfPartition itP = pAPartition->begin(); itP != pAPartition->end(); itP++){
		Object* centroid = (*itP).getCentroid();
		for(Partition::Cluster::itObjectsOfCluster itC = (*itP).begin(); itC != (*itP).end(); itC++){
			dDev +=  pARelation->getSimilarity()->calculate((*itC), (*centroid));
		}
	}*/

//	cout << pAPartition->getPartitionName() << endl;
	for(Partition::itClustersOfPartition itP = pAPartition->begin(); itP != pAPartition->end(); itP++){
		double devPartial = 0;
		Object *centroid = itP->getCentroid();
		//(*centroid).print();
		for(Cluster::itObjectsOfCluster itC = itP->begin(); itC != itP->end(); itC++){
			//(*(*itC)).print();
			double d = pARelation->getSimilarity()->calculate((*(*itC)), *centroid);			
			//dDev += d;
			devPartial += d;			
		}
		dDev += devPartial;
#ifdef IID
		cout << pAPartition->getPartitionName();
		cout << "\tDEV \tcluster " << itP->getLabel() << " \t(" << itP->getNumberOfObjects() << " objects):\t" << devPartial << endl;
#endif
	}

	return dDev;
}

double Deviation::calculate(Partition &objAPartition1, Partition &objAPartition2){
	//TODO Colocar no relat�rio esse retorno com n�mero qualquer
	return -100;
}
