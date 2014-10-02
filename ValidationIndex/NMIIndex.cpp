/*
 * NMIndex.h
 *
 *  Created on: ??/??/2010
 *      Author: ???
 */

#include "NMIIndex.h"
#include "../time.h"
#include <pthread.h>
#include <stdio.h>

#define qtdThreads 2
double resposta_nmi[qtdThreads];
Partition* partitions_nmi;
double mutual_summation_nmi=0;

void* entropy_thread_nmi(void* attr) {
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

double intersection_nmi(Partition &objPartition1, Partition &objPartition2, Partition::itClustersOfPartition itPartition1, Partition::itClustersOfPartition itPartition2) {
    int iCounter = 0;

    for (Cluster::itObjectsOfCluster itObjects1 = (*itPartition1).begin(); itObjects1 != (*itPartition1).end(); itObjects1++) {
        if (itPartition2->find((*itObjects1)) != itPartition2->end())
            iCounter++;
    }

    return iCounter / static_cast<double> (objPartition1.getNumObjects());
}

void* partition_calculate_nmi(void* rank) {
    long id = (long)rank;
    long i=0;
    Partition objPartition1 = *partitions_nmi;
    Partition objPartition2 = *(partitions_nmi+1);
    long n = objPartition1.getNumClusters()/qtdThreads;
    long first = n*id;
    long last = first+n;
    double dSummation = 0;
    double dStore = 0, dProbabilityPartition1 = 0, dProbabilityPartition2 = 0;
    Partition::itClustersOfPartition it1;


    for(i=0, it1 = objPartition1.begin(); i<first && it1 != objPartition1.end(); it1++, i++);

    for(i=first; i<last && it1 != objPartition1.end(); i++, it1++) {
        for(Partition::itClustersOfPartition it2 = objPartition1.begin(); it2 != objPartition1.end(); it2++){
            dStore = intersection_nmi(objPartition1, objPartition2, it1, it2);

            dProbabilityPartition1 = (*it1).getNumberOfObjects() / static_cast<double> (objPartition1.getNumObjects());
            dProbabilityPartition2 = (*it2).getNumberOfObjects() / static_cast<double> (objPartition2.getNumObjects());

            if (dStore != 0 && dStore / (dProbabilityPartition1 * dProbabilityPartition2) != 0) {
                dStore *= log10(dStore / ((dProbabilityPartition1 * dProbabilityPartition2)));
                dSummation += dStore;
            }
        }
    }
    resposta_nmi[id]=dSummation;
}

void* mutual_thread_nmi(void* attr) {
    mutual_summation_nmi = 0;
    partitions_nmi = (Partition*)attr;
    int i=0;

    pthread_t* threads = (pthread_t*)malloc(qtdThreads*sizeof(pthread_t));

    for(i=0;i<qtdThreads;i++) {
        resposta_nmi[i]=0;
        pthread_create(&threads[i], NULL, partition_calculate_nmi, (void*)i);
    }

    for(i=0;i<qtdThreads;i++) {
        pthread_join(threads[i], NULL);
        mutual_summation_nmi += resposta_nmi[i];
    }
}

/* Implementation of both inherited methods */

/* Implementation of both inherited methods */
double NMIIndex::calculate(Partition &objAPartition1, Partition &objAPartition2)
{
    double *e1, *e2, *mut;
    double en1, en2, muts;
    double start, finish;
    double serial, paralel;
    Partition partition[2] = {objAPartition1, objAPartition2};
    pthread_t* entropies = (pthread_t*)malloc(2*sizeof(pthread_t));
    pthread_t* mutual = (pthread_t*)malloc(sizeof(pthread_t));
    //printf("-------começo-----\n");
    //Entropia
    pthread_create(&entropies[0], NULL, entropy_thread_nmi, (void*)&objAPartition1);
    pthread_create(&entropies[1], NULL, entropy_thread_nmi, (void*)&objAPartition2);
    pthread_join(entropies[0], (void**)&e1);
    pthread_join(entropies[1], (void**)&e2);
    //Mutual
    pthread_create(mutual, NULL, mutual_thread_nmi, (void*)&partition);
    pthread_join(*mutual, NULL);
    return mutual_summation_nmi/sqrt((*e1)*(*e2));
	//return  mutualInformation(objAPartition1, objAPartition2)/sqrt(entropy(objAPartition1)*entropy(objAPartition2));
}

/* This method is to be used in internal validation measures, since NMI isn't an internal validation measure
    the call of this method will throw an exception */
double NMIIndex::calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset){
	//TODO Colocar no relat—rio esse retorno com nœmero qualquer
	return -100;
}
