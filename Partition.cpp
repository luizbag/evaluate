/*
 * Partition.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus Vinicius
 */

#include "Partition.h"


Partition::Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition) {
	sPathPartition = sAPathPartition;
	sNamePartition = sANamePartition;
	pDataSet = pAObjDataSet;

	pathPartition = sPathPartition + sNamePartition;
	loadPartition();
}

Partition::Partition(DataSet *pAObjDataSet, string sAPathPartition, string sANamePartition, int iANumberOfClusters){
	iNumClusters = iANumberOfClusters;
	sPathPartition = sAPathPartition;
	sNamePartition = sANamePartition;
	pDataSet = pAObjDataSet;

	pathPartition = sPathPartition + sNamePartition;

	for(int i = 0; i < iANumberOfClusters; i++){
		Cluster *newCluster = new Cluster(i);
		vectorCluster.push_back(*newCluster);
		delete newCluster;
	}

//TODO Ver com professora
// # Corrigir para que todos os clusters criados tenham pelo menos 1 objeto
	for (DataSet::itObjectsOfDataSet it = pDataSet->begin(); it != pDataSet->end(); it++){
		int iCluster = rand() % getNumClusters() + 1; // numero entre 1 e iNumClusters
		vectorCluster[iCluster].addObject(it);
	}
	for (itClustersOfPartition it = vectorCluster.begin(); it != vectorCluster.end(); it++){
		it->calculateCentroid();
	}

	iNumObjects = pDataSet->getNumberOfObjects();
}

Partition::~Partition() {}

void Partition::loadPartition() {
	Cluster *pObjCluster;
	string sTemp;
	string sObject;
	istringstream instream;
	int iCluster;
	unsigned int i;

	iNumObjects = 0;
	ifstream in(pathPartition.c_str());

	// Defines what gonna be the tokenizer character
	char_separator<char> sep("\t");
	while (getline(in, sTemp)) {

		// Tokenizes the string sTemp that's the line read in the file informed in 'pathAPartition'
		tokenizer<char_separator<char> > tokens(sTemp, sep);

		for (tokenizer<char_separator<char> >::iterator itTokens = tokens.begin(); itTokens != tokens.end(); ++itTokens) {

			// putting the ID of the element in the memory
			// mapVector[sIndexLine].push_back(dNumber);
			sObject = *itTokens;
			++itTokens;

			(istringstream(itTokens.current_token()) >> iCluster);
			// check if the cluster already exists
			i = 0;
			while (i < vectorCluster.size() && vectorCluster[i].getLabel() != iCluster) {
				i++;
			}

			if (i == vectorCluster.size()) {
			// create the new cluster if it does not exist
				pObjCluster = new Cluster(iCluster);
				pObjCluster->addObject(pDataSet->find(sObject));

				vectorCluster.push_back(*pObjCluster);
				delete pObjCluster;
			} else
				vectorCluster[i].addObject(pDataSet->find(sObject));
			iNumObjects++;
		}
	}

	iNumClusters =  vectorCluster.size();
	calculateCentroid();
}

void Partition::writePartition(fs::path sAFolder) {

	if (!exists(sAFolder))
		fs::create_directory(sAFolder);

	string sPath = sAFolder.string() + sNamePartition;

	ofstream out(sPath.c_str());

	for (itClustersOfPartition it = begin(); it != end(); it++) {
		for (Cluster::itObjectsOfCluster it2 = it->begin(); it2 != it->end(); it2++) {
			out << (*it2)->getId() << "\t" << it->getLabel() << "\n";
		}
	}

	out.close();
}

void Partition::calculateCentroid() {

	for (Partition::itClustersOfPartition it = vectorCluster.begin(); it != vectorCluster.end(); it++){
		(*it).calculateCentroid();
	}
}

void Partition::addCluster(Cluster *pACluster) {
	vectorCluster.insert(vectorCluster.end(), *pACluster);
	iNumClusters =  vectorCluster.size();
}

bool Partition::equal(Partition *pAPartition) { // verdadeiro se duas partições são iguais
	if (pAPartition->getNumClusters() == getNumClusters()) {
		for (itClustersOfPartition it1 = begin(); it1 != end(); it1++) {
			bool bFindEqual = false;
			for (itClustersOfPartition it2 = pAPartition->begin(); it2 != pAPartition->end(); it2++)
				if (it1->equal(it2.operator ->()))
					bFindEqual = true; // if one cluster is not equal, the partition is not equal
			if (!bFindEqual) return false;
		}
	} else {
		return false;
	}
	return true;
}

/*bool Partition::compare(Partition *pAPartition) {
	itClustersOfPartition itClusterPartition0 = begin();
	itClustersOfPartition itClusterPartition1 = pAPartition->begin();

	if (itClusterPartition0->getNumberOfObjects() == itClusterPartition1->getNumberOfObjects()) {
		return itClusterPartition0->compare(itClusterPartition1.operator ->());
	} else {
		return false;
	}
}
*/

void Partition::print(){
	for (itClustersOfPartition it = begin(); it != end(); ++ it){
		it->print();
	}
	cout << endl;
}

int Partition::getNumClusters() {
	return vectorCluster.size();//iNumClusters;
}

int Partition::getNumObjects() {
	return pDataSet->getNumberOfObjects();
}

string Partition::getPartitionName() {
	return sNamePartition;
}

void Partition::setPartitionName(string sAPartitionName) {
	sNamePartition = sAPartitionName;
}

Partition::itClustersOfPartition Partition::getClusterOf(DataSet::itObjectsOfDataSet objAObject){
	itClustersOfPartition it;
	for (it = vectorCluster.begin(); !((*it).find(objAObject) != (*it).end())  && it != vectorCluster.end(); it++);
	return it;
}

Object* Partition::getCentroidInCluster(int iAClusterLabel){
	itClustersOfPartition it = findCluster(iAClusterLabel);
	if (it != end())
		return (*it).getCentroid();
	return NULL;
}

Partition::itClustersOfPartition Partition::begin() {
	return vectorCluster.begin();
}

Partition::itClustersOfPartition Partition::end() {
	return vectorCluster.end();
}

Partition::itClustersOfPartition Partition::elementAt(int index) 
{
   Partition::itClustersOfPartition it = begin() + index;

	return it;
}

Partition::itClustersOfPartition Partition::findCluster(int iALabel){
	itClustersOfPartition it;

	for (it = vectorCluster.begin(); (*it).getLabel() != iALabel && it != vectorCluster.end(); it++);

	return it;
}
