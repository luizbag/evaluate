/*
 * DataExplorer.h
 *
 */

#ifndef DATAEXPLORER_H_
#define DATAEXPLORER_H_

#include <boost/filesystem.hpp>

#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <map>
#include <string>
#include <sys/types.h>
#include <vector>

#include "DataSet.h"
#include "Euclidean.h"
#include "Partition.h"
#include "Pearson.h"
#include "RelationSDN.h"
#include "Similarity.h"
#include "ValidationIndex.h"
//#include "ValidationIndex/Deviation.h"

using namespace std;

namespace fs = boost::filesystem;

class DataExplorer {
	private:
		vector< ValidationIndex* > vectorValidationIndexes; ///< vector of the Validation indexes
		vector< Similarity * > vectorSimilarities; ///< vector of the measures of Similarity employed

		vector< pair< pair< Partition*, vector< double > >, pair< int, string > > > vectorPartitionsK2;

		int iNumNn; ///< Number of neighbors

		vector < RelationSDN *> vectorRelationSDN; ///< vector of pointers to the RelationSDNs
		DataSet *pDataSet; ///< pointer to the DataSet

		vector<Partition*> vectorPartitions; ///< vector of Partitions loaded
		vector<Partition*> vectorRealClasses;
		vector<double> vectorObjectivesValues; ///< vector of indexes values

	public:
		typedef vector< pair< pair< Partition*, vector< double > >, pair< int, string > > >::iterator itPartitionsOfPartitionsK2;

		/** Class constructor */
		/** @param  Number of neighbors, pointer to DataSet, vector of pointers to Similarities to be used, vector of validation indexes */
		DataExplorer(int iANumNn, DataSet *pADataSet, vector<Similarity *> vectorASimilarities, vector< ValidationIndex* > vectorAValidationIndexes);


		/** Loads Partitions from the disk to break them and added to Population */
		/** @param Don't have */
		void loadPartitions(fs::path pathAPartition)
;		void loadTruePartitions(fs::path pathAPartition);

		void assignPartition();

		/** Evaluates the partition with validation indexes */
		/** @param Partition to be evaluated */
		/** @return Returns a vector of the evaluated values */
		void evaluatePartition();

		void calculateCentroid();

		/** Saves the report of Population on disk */
		/** @param Don't have */
		void writeReport(fs::path pathAReport);

};

#endif /* DATAEXPLORER_H_ */
