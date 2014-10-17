#include "VIIndex.h"
#include "../Partition.h"
#include "../InformationTheory.h"
#include "../Exception.h"

/* Implementation of both inherited methods */

double VIIndex::calculate(Partition &objAPartition1, Partition &objAPartition2)
{
double entropia, tempoinicio,tempofim,tempo,entropia2, tempoinicio2,tempofim2,tempo2;
double entropiafun1,entropiafun2,mutualfun;
    
    GET_TIME(tempoinicio);
	entropia = entropy(objAPartition1) + entropy(objAPartition2) - 2*mutualInformation(objAPartition1, objAPartition2);
	GET_TIME(tempofim);
	tempo = tempofim - tempoinicio;
	printf("Tempo serial= %lf \n", tempo);
    
	
	 GET_TIME(tempoinicio2);
    
    
	#  pragma omp parallel 
	{
	//entropia2 = entropy(objAPartition1) + entropy(objAPartition2) - 2*mutualInformation(objAPartition1, objAPartition2);
     entropiafun1=   entropy(objAPartition1);
     entropiafun2=   entropy(objAPartition2);
     mutualfun= 2*mutualInformation(objAPartition1, objAPartition2);
      entropia2 = entropiafun1+entropiafun2- mutualfun;
        
	}
	GET_TIME(tempofim2);
	tempo2 = tempofim2 - tempoinicio2;
	printf("Tempo paralelo= %lf \n", tempo2);
	
	
	return entropia;


	//return entropy(objAPartition1) + entropy(objAPartition2) - 2*mutualInformation(objAPartition1, objAPartition2);

}

double VIIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}
