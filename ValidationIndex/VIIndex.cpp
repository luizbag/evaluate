#include "VIIndex.h"
#include "../Partition.h"
#include "../InformationTheory.h"
#include "../Exception.h"
#include "../time.h"

/* Implementation of both inherited methods */

double VIIndex::calculate(Partition &objAPartition1, Partition &objAPartition2, int iNumT)
{
	return entropy(objAPartition1,iNumT) + entropy(objAPartition2,iNumT) - 2*mutualInformation(objAPartition1, objAPartition2,iNumT);
}

double VIIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}
