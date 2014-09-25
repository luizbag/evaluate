#include "VIIndex.h"
#include "../Partition.h"
#include "../InformationTheory.h"
#include "../Exception.h"
#include "../time.h"
#include <pthread.h>
#include <stdio.h>

void* entropy_thread(void* attr) {
    Partition* objPartition = (Partition*)attr;
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

double intersection(Partition &objPartition1, Partition &objPartition2, Partition::itClustersOfPartition itPartition1, Partition::itClustersOfPartition itPartition2) {
    int iCounter = 0;

    for (Cluster::itObjectsOfCluster itObjects1 = (*itPartition1).begin(); itObjects1 != (*itPartition1).end(); itObjects1++) {
        if (itPartition2->find((*itObjects1)) != itPartition2->end())
            iCounter++;
    }

    return iCounter / static_cast<double> (objPartition1.getNumObjects());
}

void* mutual_thread(void* attr) {
    double dSummation = 0;
    double dStore = 0, dProbabilityPartition1 = 0, dProbabilityPartition2 = 0;
    Partition* partitions = (Partition*)attr;
    Partition objPartition1 = *partitions;
    Partition objPartition2 = *(partitions+1);

    for(Partition::itClustersOfPartition it1 = objPartition1.begin(); it1 != objPartition1.end(); it1++){
        for(Partition::itClustersOfPartition it2 = objPartition1.begin(); it2 != objPartition1.end(); it2++){
            dStore = intersection(objPartition1, objPartition2, it1, it2);

            dProbabilityPartition1 = (*it1).getNumberOfObjects() / static_cast<double> (objPartition1.getNumObjects());
            dProbabilityPartition2 = (*it2).getNumberOfObjects() / static_cast<double> (objPartition2.getNumObjects());

            if (dStore != 0 && dStore / (dProbabilityPartition1 * dProbabilityPartition2) != 0) {
                dStore *= log10(dStore / ((dProbabilityPartition1 * dProbabilityPartition2)));
                dSummation += dStore;
            }
        }
    }

    pthread_exit((void*)&dSummation);
}

/* Implementation of both inherited methods */

double VIIndex::calculate(Partition &objAPartition1, Partition &objAPartition2)
{
    double *e1, *e2, *mut;
    double en1, en2, muts;
    double start, finish;
    double serial, paralel;
    Partition partition[2] = {objAPartition1, objAPartition2};
    pthread_t* entropies = (pthread_t*)malloc(2*sizeof(pthread_t));
    pthread_t* mutual = (pthread_t*)malloc(sizeof(pthread_t));
    //printf("-------começo-----\n");
    GET_TIME(start);
    pthread_create(&entropies[0], NULL, entropy_thread, (void*)&objAPartition1);
    pthread_create(&entropies[1], NULL, entropy_thread, (void*)&objAPartition2);
    pthread_create(mutual, NULL, mutual_thread, (void*)&partition);
    pthread_join(*mutual, (void**)&mut);
    pthread_join(entropies[0], (void**)&e1);
    pthread_join(entropies[1], (void**)&e2);
    GET_TIME(finish);
    paralel = finish-start;
    //printf("Thread foi\n");
    GET_TIME(start);
    en1 = entropy(objAPartition1);
    //printf("entropy 1 já foi também\n");
    en2 = entropy(objAPartition2);
    muts = mutualInformation(objAPartition1, objAPartition2);
    GET_TIME(finish);
    serial = finish-start;
    printf("Elapsed serial: %lf\nElapsed thread: %lf\n",serial, paralel);
    printf("----------------------\n");
	return 0;//en1 + en2 - 2*mutualInformation(objAPartition1, objAPartition2);

}

double VIIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}