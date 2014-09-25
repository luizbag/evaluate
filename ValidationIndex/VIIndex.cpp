#include "VIIndex.h"
#include "../Partition.h"
#include "../InformationTheory.h"
#include "../Exception.h"
#include "../time.h"
#include <pthread.h>
#include <stdio.h>

void* entropy_thread(void* rank) {
    Partition* objPartition = (Partition*)rank;
    double dSummation = 0;
    double dStore;

    for(Partition::itClustersOfPartition it1 = objPartition->begin(); it1 != objPartition->end(); it1++){
        dStore = (it1)->getNumberOfObjects()    / static_cast<double> (objPartition->getNumObjects());
        //printf("dStoret=%lf\n",dStore);
        if (dStore != 0) dStore *= log10(dStore); // assumindo log0 = 0
        dSummation += dStore;
    }
    dSummation = dSummation * -1;
    //printf("dSummationt=%lf\n",dSummation);
    pthread_exit((void*)&dSummation);
    //return -dSummation;
}

/* Implementation of both inherited methods */

double VIIndex::calculate(Partition &objAPartition1, Partition &objAPartition2)
{
    double *e1, *e2;
    double en1, en2;
    double start, finish;
    pthread_t* entropies = (pthread_t*)malloc(2*sizeof(pthread_t));
    //printf("-------começo-----\n");
    GET_TIME(start);
    pthread_create(&entropies[0], NULL, entropy_thread, (void*)&objAPartition1);
    pthread_create(&entropies[1], NULL, entropy_thread, (void*)&objAPartition2);
    pthread_join(entropies[0], (void**)&e1);
    pthread_join(entropies[1], (void**)&e2);
    GET_TIME(finish);
    printf("Elapsed thread: %lf\n",finish-start);
    //printf("Thread foi\n");
    GET_TIME(start);
    en1 = entropy(objAPartition1);
    //printf("entropy 1 já foi também\n");
    en2 = entropy(objAPartition2);
    GET_TIME(finish);
    printf("Elapsed serial: %lf\n",finish-start);
    //printf("essa foi a 2\n");
    printf("%f\t%f\n",*e1, en1);
    //printf("------fim-----\n");
    printf("%f\t%f\n",*e2, en2);
	return 0;//en1 + en2 - 2*mutualInformation(objAPartition1, objAPartition2);

}

double VIIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}