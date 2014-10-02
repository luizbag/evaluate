#include "VIIndex.h"
#include "../Partition.h"
#include "../InformationTheory.h"
#include "../Exception.h"
#include "../time.h"
#include <pthread.h>
#include <stdio.h>

#define qtdThreads 8
double resposta[qtdThreads];
Partition* partitions;
double mutual_summation=0;
double en[2];

void* entropy_thread(void* attr) {
    long id = (long)attr;
    Partition* objPartition = partitions+id;
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
    en[id] = dSummation;
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

void* partition_calculate(void* rank) {
    long id = (long)rank;
    long i=0;
    Partition objPartition1 = *partitions;
    Partition objPartition2 = *(partitions+1);
    long n = objPartition1.getNumClusters()/qtdThreads;
    long first = n*id;
    long last = first+n;
    double dSummation = 0;
    double dStore = 0, dProbabilityPartition1 = 0, dProbabilityPartition2 = 0;
    Partition::itClustersOfPartition it1;

    for(i=0, it1 = objPartition1.begin(); i<first && it1 != objPartition1.end(); it1++, i++);
    for(i=first; i<last && it1 != objPartition1.end(); i++, it1++) {
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
    resposta[id]=dSummation;
}

void* mutual_thread(void* attr) {
    mutual_summation = 0;
    int i=0;

    pthread_t* threads = (pthread_t*)malloc(qtdThreads*sizeof(pthread_t));

    for(i=0;i<qtdThreads;i++) {
        resposta[i]=0;
        pthread_create(&threads[i], NULL, partition_calculate, (void*)i);
    }

    for(i=0;i<qtdThreads;i++) {
        pthread_join(threads[i], NULL);
        mutual_summation += resposta[i];
    }
    free(threads);



    //Partition objPartition1 = *partitions;
    //Partition objPartition2 = *(partitions+1);
//
    //for(Partition::itClustersOfPartition it1 = objPartition1.begin(); it1 != objPartition1.end(); it1++){
    //    for(Partition::itClustersOfPartition it2 = objPartition1.begin(); it2 != objPartition1.end(); it2++){
    //        dStore = intersection(objPartition1, objPartition2, it1, it2);
//
    //        dProbabilityPartition1 = (*it1).getNumberOfObjects() / static_cast<double> (objPartition1.getNumObjects());
    //        dProbabilityPartition2 = (*it2).getNumberOfObjects() / static_cast<double> (objPartition2.getNumObjects());
//
    //        if (dStore != 0 && dStore / (dProbabilityPartition1 * dProbabilityPartition2) != 0) {
    //            dStore *= log10(dStore / ((dProbabilityPartition1 * dProbabilityPartition2)));
    //            dSummation += dStore;
    //        }
    //    }
    //}
}

/* Implementation of both inherited methods */

double VIIndex::calculate(Partition &objAPartition1, Partition &objAPartition2)
{
    int i;
    Partition partition[2] = {objAPartition1, objAPartition2};
    partitions = partition;
    pthread_t* entropies = (pthread_t*)malloc(2*sizeof(pthread_t));
    pthread_t* mutual = (pthread_t*)malloc(sizeof(pthread_t));
    //Entropia
    for(i=0;i<2;i++) {
       pthread_create(&entropies[i], NULL, entropy_thread, (void*)i);
    }
    for(i=0;i<2;i++) {
        pthread_join(entropies[i], NULL);
    }
    //Mutual
    pthread_create(mutual, NULL, mutual_thread, (void*)&partition);
    pthread_join(*mutual, NULL);
    free(entropies);
    free(mutual);
	//return en1 + en2 - 2*mutualInformation(objAPartition1, objAPartition2);
    return en[0]+en[1]-2*mutual_summation;//*e1 + *e2 - 2*mutual_summation;

}

double VIIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}