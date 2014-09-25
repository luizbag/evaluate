/*
 * Cluster.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus Vinicius
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <sstream>
#include <time.h>

#include "DataSet.h"

using namespace boost;
using namespace std;

/// Represents a group of objects that were considered similar according some clustering algorithm
/** Represents a group of objects that were considered similar according some clustering algorithm */
class Cluster {
	private:
		int iLabel; ///< Label of the cluster
		Object objCentroid; ///< A object that will receive the centroids of each cluster
		vector<DataSet::itObjectsOfDataSet> vectorObjects; ///< Vector that will receive the iterators of object of the dataset
		bool bCentroidCalculated; // true, if centroid is calculated once

	public:
		typedef vector<DataSet::itObjectsOfDataSet>::iterator itObjectsOfCluster;

		/** Class constructor */
		/** @param  Cluster label */
		Cluster(int iAClusterLabel);

		/** Adds the object in the vector of objects */
		/** @param  string sID */
		void addObject(DataSet::itObjectsOfDataSet objAObject);

		/** Calculates the centroid of the cluster */
		/** @param  Don't have */
		void calculateCentroid();

		/** Removes an object of the cluster */
		/** @param String object  */
		void removeObject(DataSet::itObjectsOfDataSet objAObject);

		/** Compares if both clusters are equals */
		/** @param Cluster to be compared */
		/** @return Returns true if they are equals or false if they are not */
		bool compare(Cluster *pACluster);
		bool equal(Cluster *pACluster);

		/** Prints the cluster */
		/** @param Don't have */
		void print();

		/** Gets the cluster label */
		/** @param Don't have  */
		/** @return Returns the label of the cluster */
		int getLabel();

		/** Gets the centroids of the cluster */
		/** @param Don't have  */
		/** @return Returns the centroids of the cluster */
		Object* getCentroid();

		/** Gets the number of objects that the cluster has */
		/** @param  Don't have.*/
		/** @return Returns the size of the vectorObjects */
		int getNumberOfObjects();

		/** Iterator that point the beginning of the Objects' vector */
		/** @param Don't have */
		itObjectsOfCluster begin();

		/** Iterator that points to the end of the Objects' vector */
		/** @param Don't have */
		itObjectsOfCluster end();

		/** Iterator that points to the object called sAId of the Objects' vector */
		/** @param Don't have */
		itObjectsOfCluster find(DataSet::itObjectsOfDataSet objAObject);
};

#endif /* CLUSTER_H_ */
