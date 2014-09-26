/*
 * main.cpp
 *
 */

#include <boost/filesystem.hpp>

#include <iostream>

#include "Cluster.h"
#include "DataExplorer.h"
#include "DataSet.h"
#include "Object.h"
#include "Similarity.h"
#include "SimilarityMatrix.h"
#include "Euclidean.h"
#include "Pearson.h"
#include "Partition.h"
#include "NnList.h"
#include "RelationSDN.h"
#include "ValidationIndex.h"
#include "ValidationIndex/Connectivity.h"
#include "ValidationIndex/Deviation.h"
#include "ValidationIndex/Variance.h"
#include "ValidationIndex/Silhouette.h"


#include "ValidationIndex/CRIndex.h"
#include "ValidationIndex/NMIIndex.h"
#include "ValidationIndex/VIIndex.h"
#include "ValidationIndex/FMeasure.h"

// to run G-DID index, uncomment the line below
//#define GDID
// to print Internal Indices details
//#define IID

//./evaluationIndices test/iris/dataset/iris.txt test/iris/results 15 test/iris/partitions/ test/iris/TP/

namespace fs = boost::filesystem;
using namespace std;

int main(int argc, char **argv) {

	if (argc < 5)
	{
		std::cout << "Usage: ./evaluationIndices <Dataset> <Experiment' Directory> <Number of Nearest Neighbours> "
			      "<Partitions' Directory> [True Partitions' Directory] \n" << std::endl;
		return -1;
	}

	//DATASET
	fs::path pathDataSet = argv[1];
	//cout << "pathDataSet "<<pathDataSet <<endl;
	DataSet *pObjDataSet;
	if (!fs::exists(pathDataSet)){
		cout << "The dataset doesn't exist!" << endl << "Please, check your dataset path." << endl;
		return -1;
	}


	// Experiments directory - where DataExplorer will write the produced reports, files, etc
	fs::path dir = argv[2];
	fs::path pathReport = dir.string();
	if (! fs::exists(pathReport)){
	  fs::create_directory(dir);
	}

	//NnNUM (number of nearest neighbors used by some algorithms and/or validation indices
	int iNumNn = atoi(argv[3]);

	//PARTITIONS
	// partitions obtained with the algorithms with the DataExplorer or to be loaded
	fs::path pathPartition;
	pathPartition = argv[4];
	if (! fs::exists(pathPartition)){
	  cout << "The path to the initial partitions " << pathPartition << " doesn't exist!" << endl;
	  return -1;
	}

	//PARTITIONS REAL CLASSES
	// true partitions to be used for evaluation purposes
	// it should exist if the evaluation is to be run
	fs::path pathPartitionRealClasses;
	if (argc > 5) {
		pathPartitionRealClasses = argv[5];
		if (! fs::exists(pathPartitionRealClasses)){
			cout << "The informed path to the PARTITIONS REAL CLASSES doesn't exist!" << endl << "Please, check your partitions path." << endl;
			return -1;
		}
	} else {
		pathPartitionRealClasses = pathReport.string() + "TruePartitionsDir/";
		fs::create_directory(pathPartitionRealClasses);
	}

	pObjDataSet = new DataSet(pathDataSet.parent_path().string() + "/", pathDataSet.filename().string());

	//SIMILARITY
	Euclidean *pSimilarityEuclidean = new Euclidean();
//	Pearson *pSimilarityPearson = new Pearson();

	vector< Similarity* > vectorSimilarities;
	vectorSimilarities.clear();

	vectorSimilarities.insert(vectorSimilarities.end(), pSimilarityEuclidean );
	//vectorSimilarities.insert(vectorSimilarities.end(), pSimilarityPearson );

	//INDEXES
	Connectivity *pConnectivity = new Connectivity();
	Deviation *pDeviation = new Deviation();
	Variance *pVariance = new Variance();
	Silhouette *pSilhouette = new Silhouette();
	//CKNNCluster *pCKNN = new CKNNCluster();
#ifdef GDID
	//GDid *pGDid = new GDid();
#endif
	VIIndex *pVIIndex = new VIIndex();
	FMeasure *pFMeasure = new FMeasure();
	CRIndex *pCRIndex = new CRIndex();
	NMIIndex *pNMIIndex = new NMIIndex();

	vector< ValidationIndex* > vectorValidationIndexes;
	vectorValidationIndexes.clear();

	// for the evaluators use only the internal validation indices
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pConnectivity);
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pDeviation);
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pVariance);
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pSilhouette);
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pCKNN);
#ifdef GDID
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pGDid);
#endif
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pCRIndex);	
	vectorValidationIndexes.insert(vectorValidationIndexes.end(), pNMIIndex);
	vectorValidationIndexes.insert(vectorValidationIndexes.end(), pVIIndex);
	//vectorValidationIndexes.insert(vectorValidationIndexes.end(), pFMeasure);
	


	DataExplorer *pObjDataExplorer;
	pObjDataExplorer = new DataExplorer(iNumNn, pObjDataSet, vectorSimilarities, vectorValidationIndexes);

	/**********************************************/


	/**********************************************/


// load the partitions and stores in the DataExplorer proper attribute
//	cout <<"pathPartition"<< pathPartition << endl;
	pObjDataExplorer->loadPartitions(pathPartition);
	pObjDataExplorer->loadTruePartitions(pathPartitionRealClasses);
	pObjDataExplorer->assignPartition(); // associa as partições carregadas à estrutura correta do DataExplorer
	pObjDataExplorer->calculateCentroid();
	pObjDataExplorer->evaluatePartition();
	pObjDataExplorer->writeReport(pathReport);

	/**********************************************/

//	cout << "fim";

	return 0;
}



