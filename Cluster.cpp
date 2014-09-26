/*
 * Cluster.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus Vinicius
 */

#include "Cluster.h"

Cluster::Cluster(int iAClusterLabel) {
	iLabel = iAClusterLabel;
	bCentroidCalculated = false;	
	//objCentroid.initialize();
	//objCentroid.calculateCentroid();
}

void Cluster::addObject(DataSet::itObjectsOfDataSet objAObject) {
	vectorObjects.push_back(objAObject);
}

void Cluster::calculateCentroid() {
	int iNumFeatures = vectorObjects[0]->getNumberOfFeatures();
//vectorObjects[0]->print();
	string sIdCentroid = "centroid" + boost::lexical_cast<string>(iLabel);
	objCentroid.setId(sIdCentroid);

	if (!bCentroidCalculated){ // inicializa o vetor, caso não tenha sido calculado nenhuma vez ("gambiarra")
		for (int i = 0; i < iNumFeatures; i++)
			objCentroid.addFeature(0); // initialize the feature vector 
		bCentroidCalculated = true;	
	}
	for (int i = 0; i < iNumFeatures; i++) {
		double dSum = 0;
		for (itObjectsOfCluster it = vectorObjects.begin(); it != vectorObjects.end(); it++){
			dSum += (*it)->getFeature(i);
		}
		objCentroid[i] = dSum/getNumberOfObjects();
	}
//	cout << "Centroid " << endl;
//	objCentroid.print();
//	cout << endl << endl;

}

void Cluster::removeObject(DataSet::itObjectsOfDataSet objAObject){
	itObjectsOfCluster itObj = find(objAObject);

	if ( itObj != vectorObjects.end()){ //found
		vectorObjects.erase(itObj);
	}
}

bool Cluster::compare(Cluster *pACluster) {
	for (itObjectsOfCluster it = begin(); it != end(); it++) {
		if (pACluster->find(*it) == pACluster->end()) {
			return false;
		}
	}
	return true;
}

bool Cluster::equal(Cluster *pACluster) {
	for (itObjectsOfCluster it = begin(); it != end(); it++) {
		if (pACluster->find(*it) == pACluster->end()) {
			return false;
		}
	}
	return true;
}

void Cluster::print(){
	for (itObjectsOfCluster it = begin(); it != end(); it++){
		cout << (*it)->getId() << "\t" << iLabel << endl;
	}
}

int Cluster::getLabel() {
	return iLabel;
}

Object *Cluster::getCentroid(){
	return &objCentroid;
}

int Cluster::getNumberOfObjects() {
	return vectorObjects.size();
}

Cluster::itObjectsOfCluster Cluster::begin() {
	return vectorObjects.begin();
}

Cluster::itObjectsOfCluster Cluster::end() {
	return vectorObjects.end();
}

Cluster::itObjectsOfCluster Cluster::find(DataSet::itObjectsOfDataSet objAObject){
	Cluster::itObjectsOfCluster itObj;
	for (itObj = begin(); itObj != end() && (*itObj) != objAObject; itObj++);
	return itObj;
}
