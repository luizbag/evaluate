/*
 * NnList.h
 *
 *  Created on: Jul 25, 2011
 *      Author: Marcus Vinicius
 */

#ifndef NNLIST_H_
#define NNLIST_H_

#include <map>

#include "DataSet.h"
#include "RelationSDN.h"

class DataSet;
class RelationSDN;

using namespace std;

typedef pair<DataSet::itObjectsOfDataSet, double> tPairObjSim;

class CompareObjectL : public std::binary_function <tPairObjSim, tPairObjSim, bool> {
public:
	bool operator()(tPairObjSim x, tPairObjSim y) {
    	   return (x.second < y.second);
       }
};

class CompareObjectG : public std::binary_function <tPairObjSim, tPairObjSim, bool> {
public:
	bool operator()(tPairObjSim x, tPairObjSim y) {
    	   return (x.second > y.second);
       }
};

/// Represents the nearest neighbors of all Objects of the DataSet according to the Similarity Matrix
/** Represents the nearest neighbors of all Objects of the DataSet according to the Similarity Matrix */
class NnList {

	private:
		map<DataSet::itObjectsOfDataSet, vector<DataSet::itObjectsOfDataSet> > mapNnList; ///< Map that contains the Object and their nearest neighbors

		// para uso no dataexplorer precisa que armazene todos os vizinhos (principalmente pelo indice GDID) - então iNumNn = tamanho do dataset - 1
		int iNumNn; ///< Number of neighbors

	public:
		typedef map<DataSet::itObjectsOfDataSet, vector<DataSet::itObjectsOfDataSet> >::iterator itNeighborsOfObject;

		/** Class constructor */
		/** @param  Don't have */
		NnList(RelationSDN *pARelationSDN, int iANumNn);

		/** Class destructor */
		/** @param  Don't have */
		virtual ~NnList();

		/** Accesses the iAIndex-th position of the neighbors' vector */
		/** @param The index of the wished neighbor of the Object passed as parameter */
		/** @return Returns the iAIndex-th neighbor of the Object */
		DataSet::itObjectsOfDataSet nearestNeighbor(DataSet::itObjectsOfDataSet objAObject, int iAIndex);

		/** Prints the nearest neighbors*/
		/** @param Don't have */
		void print();

		/** Gets the number of neighbors */
		/** @param Don't have */
		/** @return Returns the number of neighbors */
		int getNumberOfNn();
};

#endif /* NNLIST_H_ */
