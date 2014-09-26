/*
 * DataSet.cpp
 *
 *  Created on: Jun 21, 2011
 *      Author: Marcus Vinicius
 */

#include "DataSet.h"

DataSet::DataSet(string sPathADataSet, string sANameDataSet) {
	//Ask user for format wished.
	string sFormat  = "tabulate";

	sPathToDataSet = sPathADataSet;
	sNameDataSet = sANameDataSet;

	if (sFormat == "tabulate")
		tabulateMappingDataSet();
}

void DataSet::tabulateMappingDataSet() {
	string sPathDataSet = sPathToDataSet + sNameDataSet;
	string sIndexLine;
	string sTemp;
	string sLabel;
	istringstream instream;
	double dNumber;

	//cout << "sPathDataSet >> " << sPathDataSet << endl;
	ifstream in(sPathDataSet.c_str());

	//Gets the first line of the DataSet(Label of the objects)
	getline( in, sTemp );

	//Tokens' separator
 	char_separator<char> sep("\t");

 	tokenizer<char_separator<char> > tokens(sTemp, sep);
 	for (tokenizer<char_separator<char> >::iterator itTokens = tokens.begin(); itTokens	!= tokens.end(); ++itTokens) {
 		sLabel = *itTokens;
 		vectorDataSetLabel.insert(vectorDataSetLabel.end(), sLabel);
 	}

	while (	getline( in, sTemp ) ) {
		tokenizer<char_separator<char> > tokens(sTemp, sep);
		Object objObject;

		for (tokenizer<char_separator<char> >::iterator itTokens = tokens.begin(); itTokens	!= tokens.end(); ++itTokens) {
			//If it's the beginning of the line, then it's the Object's Id
			if (itTokens == tokens.begin()) {
				sIndexLine = *itTokens;
				objObject.setId(sIndexLine);
			//Else it's features of the Object
			} else {
				(istringstream(itTokens.current_token()) >> dNumber);
				objObject.addFeature(dNumber);
			}
		}
		vectorObjects.insert(vectorObjects.end(), objObject);
	}
	iNumObjects = vectorObjects.size();
	iNumFeatures = vectorObjects[1].getNumberOfFeatures();

	in.close();
}

void DataSet::print() {
	cout << endl;
	cout << "-- DataSet --" << endl;
	for (itObjectsOfDataSet it = begin(); it != end(); it++) {
		it->print();
	}
	cout << endl;
}

int DataSet::getNumberOfFeatures() {
	return vectorObjects[1].getNumberOfFeatures();//iNumFeatures;
}

int DataSet::getNumberOfObjects() {
	return vectorObjects.size();//iNumObjects;
}

fs::path DataSet::getPathToDataSet() {
	return sPathToDataSet;
}

string DataSet::getNameDataSet()  {
	return sNameDataSet;
}

void DataSet::setNameDataSet(string sANameDataSet) {
	sNameDataSet = sANameDataSet;
}

DataSet::itObjectsOfDataSet DataSet::begin() {
	return vectorObjects.begin();
}

DataSet::itObjectsOfDataSet DataSet::end(){
	return vectorObjects.end();
}

DataSet::itObjectsOfDataSet DataSet::find(string sAId) {
	DataSet::itObjectsOfDataSet itObjects;

	for (itObjects = begin(); itObjects != end() && itObjects->getId() != sAId; itObjects++);

	return itObjects;
}
