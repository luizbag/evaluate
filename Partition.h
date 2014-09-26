/*
 * Partition.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#ifndef PARTITION_H_
#define PARTITION_H_


#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

#include "Cluster.h"
#include "DataSet.h"

using namespace boost;
using namespace std;

namespace fs = boost::filesystem;

/// Represents a vector of Clusters and others features of the Partition.
/** Represents a vector of Clusters and others features of the Partition. */
class Partition {

	private:
		int iNumObjects; ///< The number of Objects existing in the Partition
		int iNumClusters; ///< The number of Clusters existing in the Partition
		string sPathPartition; ///< Partition path
		string sNamePartition; ///< Partition name
		string pathPartition; ///< The path to the Partition in the computer

		vector<Cluster> vectorCluster; ///< Vector of Clusters

		DataSet *pDataSet; ///< pointer to the DataSet

	public:
		typedef vector<Cluster>::iterator itClustersOfPartition;

		/** Class constructor: creates a Partition by loading it from a file */
		/** @param  Path and name of the Partition */
		Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition);

		/** Class constructor: creates a Partition with a given number of clusters by randomly assigning the objects to the clusters */
		/** @param  Path and name of the Partition and number of Clusters */
		Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition, int iANumberOfClusters);

		/** Class destructor */
		/** @param  Don't have */
		virtual ~Partition();

		/** Loads the Partitions from de system to the programm */
		/** @param Don't have */
		void loadPartition();

		/** Writes the Partition in disk, passing in the argument the path where the user want to save the Partition */
		/** @param  pathSaveIn */
		void writePartition(fs::path sAFolder);

		/** Calculates the centroid of the Cluster */
		/** @param Don't have */
		/** @see calculateCentroid(DataSet &obADataSet) */
		void calculateCentroid();

		/** Adds the Cluster in the Partition */
		/** @param Cluster to be added */
		void addCluster(Cluster *pACluster);

		/** Compares if both Partitions are equals */
		/** @param Partition to be compared */
		/** @return Returns true if they are equals or false if they are not */
		bool compare(Partition *pAPartition);
		bool equal(Partition *pAPartition);

		/** Prints the Partition */
		/** @param Don't have */
		void print();

		/** Gets the number of Clusters existing on the Partition */
		/** @param Don't have */
		/** @return Returns number of Clusters on the Partition */
		int getNumClusters();

		/** Gets the number of Objects existing on the Partition */
		/** @param Don't have */
		/** @return Returns number of Objects on the Partition */
		int getNumObjects();

		/** Gets the name of the Partition */
		/** @param Don't have */
		/** @return Returns name of the Partition */
		string getPartitionName();

		/** Sets the name of the Partition */
		/** @param Partition name */
		void setPartitionName(string sAPartitionName);

		/** Gets which Cluster the object belongs */
		/** @param Object that want to know in which cluster it is in */
		/** @return Returns a Cluster iterator */
		itClustersOfPartition getClusterOf(DataSet::itObjectsOfDataSet objAObject);

		/** Returns the centroid of Cluster*/
		/** @param Cluster Label */
		/** @return Returns the centroid of Cluster wished */
		Object* getCentroidInCluster(int iAClusterLabel);

		/** Iterator that point the beginning of the Clusters' vector */
		/** @param Don't have */
		itClustersOfPartition begin();

		/** Iterator that points to the end of the Clusters' vector */
		/** @param Don't have */
		itClustersOfPartition end();

		/** Iterator that points to the object called iALabel of the Clusters' vector */
		/** @param Cluster Label */
		itClustersOfPartition findCluster(int iALabel);
};

#endif /* PARTITION_H_ */
