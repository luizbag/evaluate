/*
 * DataExplorer.cpp
 *
 */

#include "DataExplorer.h"
#include "time.h"
#include <stdio.h>

DataExplorer::DataExplorer(int iANumNn, DataSet *pADataSet, vector<Similarity *> vectorASimilarities, vector< ValidationIndex* > vectorAValidationIndexes) {

	iNumNn = iANumNn;
	pDataSet = pADataSet;
	vectorSimilarities = vectorASimilarities;
	vectorValidationIndexes = vectorAValidationIndexes;

	RelationSDN *pRelationSDN;
	for (vector<Similarity *>::iterator it = vectorSimilarities.begin(); it != vectorSimilarities.end(); it++) {
		pRelationSDN = new RelationSDN((*it), pDataSet, iNumNn);
		vectorRelationSDN.insert(vectorRelationSDN.end(), pRelationSDN);
	}
	//cin.get();

	vectorPartitions.clear();
	vectorObjectivesValues.clear();

	srand (time(NULL));
}

void DataExplorer::loadPartitions(fs::path pathAPartition) {
	Partition *pTempPartition;

	vectorPartitions.clear();

	if (fs::is_directory(pathAPartition)) {
		fs::directory_iterator end_it;
		for (fs::directory_iterator it(pathAPartition); it != end_it; ++it) {
			//if (!fs::is_directory(*it))
			if (fs::is_regular_file(*it)){
				//cout <<(*it)<<endl;
				pTempPartition = new Partition(pDataSet, pathAPartition.string(), (*it).path().filename().string());
				//pTempPartition->print();
				pTempPartition->calculateCentroid();
				vectorPartitions.insert(vectorPartitions.end(), pTempPartition);
			}
		}
	}
}


void DataExplorer::loadTruePartitions(fs::path pathAPartition) {
	Partition *pTempPartition;

	vectorRealClasses.clear();

	if (fs::is_directory(pathAPartition)) {
		fs::directory_iterator end_it;

		for (fs::directory_iterator it(pathAPartition); it != end_it; ++it) {
			if (!fs::is_directory(*it)) {
				pTempPartition = new Partition(pDataSet, pathAPartition.string(), (*it).path().filename().string());
				pTempPartition->calculateCentroid();
				vectorRealClasses.insert(vectorRealClasses.end(), pTempPartition);
			}
		}
	}
}

void DataExplorer::assignPartition() {
	string sNamePartitionK2;
	bool iFlag;

	vectorPartitionsK2.clear();
	vectorObjectivesValues.clear();

	for (unsigned int i = 0; i < vectorPartitions.size(); i++) {
		//vectorPartitions[i]->print();
		iFlag = false;

		for (itPartitionsOfPartitionsK2 it = vectorPartitionsK2.begin(); it != vectorPartitionsK2.end(); it++) {
			if (it->first.first->equal(vectorPartitions[i])) {
				it->second.first++;
				it->second.second += ", " + vectorPartitions[i]->getPartitionName();

				iFlag = true;
				break;
			}
		}
		if (iFlag == false) {
			vectorPartitionsK2.insert(vectorPartitionsK2.end(), make_pair(make_pair(vectorPartitions[i], vectorObjectivesValues), make_pair(1, "")));
		}

	}
	calculateCentroid();
}

void DataExplorer::evaluatePartition() {
	vectorObjectivesValues.clear();
	double start, finish;

#ifdef GDID
	map<string, double> mapGDidValues;

	ifstream in("/home/tiemi/experimentos/dataExplorer/DE2/ds2c2sc13/ds2c2sc13-gdid.txt");

	string sClusterName;
	double dGDid;

	int waiting;
	cout << "Enter a number after calculate g-did index in matlab" << endl;
	cin >> waiting; //

	while(!in.eof()){
		in >> sClusterName >> dGDid;
		mapGDidValues[sClusterName] = dGDid;
		//cout << sClusterName << " " << dGDid << " " << mapGDidValues[sClusterName] << endl;
	}

	in.close();
	GET_TIME(start);
	for (itPartitionsOfPartitionsK2 it = vectorPartitionsK2.begin(); it != vectorPartitionsK2.end(); it++) {
		for (unsigned int j = 0; j < vectorValidationIndexes.size(); j++) {
			for (vector<RelationSDN *>::iterator itRelationSDN = vectorRelationSDN.begin(); itRelationSDN != vectorRelationSDN.end(); itRelationSDN++) {
				double value;
				if (vectorValidationIndexes[j]->getValidationIndexName() == "GDid"){
					//cout << "Gdid " << it->first.first->getPartitionName() << endl;
					value = mapGDidValues[it->first.first->getPartitionName()];
				} else {
					value = vectorValidationIndexes[j]->calculate(it->first.first, (*itRelationSDN), pDataSet);
				}
				vectorObjectivesValues.insert(vectorObjectivesValues.end(), value);
			}

		}
		it->first.second = vectorObjectivesValues; //stores the indices values in the vectorPartitionK2 structure
		vectorObjectivesValues.clear();
	}
	GET_TIME(finish);
	printf("elapsed: %lf\n",finish-start);
#else
	GET_TIME(start);
	for (itPartitionsOfPartitionsK2 it = vectorPartitionsK2.begin(); it != vectorPartitionsK2.end(); it++) {
		#pragma parallel for num_threads(2)
		for (unsigned int j = 0; j < vectorValidationIndexes.size(); j++) {
			for (vector<RelationSDN *>::iterator itRelationSDN = vectorRelationSDN.begin(); itRelationSDN != vectorRelationSDN.end(); itRelationSDN++) {
			  if (vectorValidationIndexes[j]->isInternal()){
				double value = vectorValidationIndexes[j]->calculate(it->first.first, (*itRelationSDN), pDataSet);
				vectorObjectivesValues.insert(vectorObjectivesValues.end(), value);
			  } else {
			    for (unsigned int i = 0; i < vectorRealClasses.size(); i++) {
			      double value = vectorValidationIndexes[j]->calculate(*vectorRealClasses[i], *(it->first.first));
			      vectorObjectivesValues.insert(vectorObjectivesValues.end(), value);
			    }
			  }
			}

		}
		it->first.second = vectorObjectivesValues; //stores the indices values in the vectorPartitionK2 structure
		vectorObjectivesValues.clear();
	}
	GET_TIME(finish);
	printf("elapsed: %lf\n",finish-start);
#endif

}

void DataExplorer::calculateCentroid() {
	for (itPartitionsOfPartitionsK2 it = vectorPartitionsK2.begin(); it != vectorPartitionsK2.end(); it++) {
		it->first.first->calculateCentroid();
	}
}

void DataExplorer::writeReport(fs::path pathAReport) {
	fs::path pathReport = pathAReport.string() + "/report.txt";
	Partition::itClustersOfPartition itMainCluster;
	unsigned int i;

	ofstream out(pathReport.string().c_str());

	out << "Id\tPartition Name\t# Clusters";

	for (i = 0; i < vectorValidationIndexes.size(); i++) {
	  if (vectorValidationIndexes[i]->isInternal()){
		for (vector<RelationSDN *>::iterator itRelationSDN = vectorRelationSDN.begin(); itRelationSDN != vectorRelationSDN.end(); itRelationSDN++) {
			out << "\t" << vectorValidationIndexes[i]->getValidationIndexName()
				<< "/" << (*itRelationSDN)->getSimilarity()->getSimilarityShortName();
		}
	  } else {
		for (vector<RelationSDN *>::iterator itRelationSDN = vectorRelationSDN.begin(); itRelationSDN != vectorRelationSDN.end(); itRelationSDN++) {
		  for (int j = 0; j <  vectorRealClasses.size(); j++) {
			out << "\t" << vectorValidationIndexes[i]->getValidationIndexName()
			    << "/" << (*itRelationSDN)->getSimilarity()->getSimilarityShortName() 
			    << " (" << vectorRealClasses[j]->getPartitionName() << ")";
		  }
		}
	  }
	}


	out << "\tCount\tRepeated Partitions\n";

	for (itPartitionsOfPartitionsK2 it = vectorPartitionsK2.begin(); it != vectorPartitionsK2.end(); it++) {

		out << distance(vectorPartitionsK2.begin(), it) + 1 << "\t" << it->first.first->getPartitionName();// id and cluster name

		out << "\t" << it->first.first->getNumClusters();
		for (unsigned int i = 0; i < it->first.second.size(); i++) { // size of the vector with the indices values
			out << "\t" << it->first.second[i];
		}

		out  << "\t" << it->second.first << "\t" << it->second.second << "\n"; // count and the list of the name of partitions that were equal to the reported one
	}

	out.close();
}

