/*
 * ValidationIndex.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vinicius
 */

#include "ValidationIndex.h"
using namespace std;

ValidationIndex::ValidationIndex(std::string sAIndexName, IndexType eAIndexType) :
		sIndexName(sAIndexName), eIndexType(eAIndexType) {};

string ValidationIndex::getValidationIndexName() {
	return sIndexName;
}

bool ValidationIndex::isInternal() {
	return eIndexType == internal;
}

bool ValidationIndex::isExternal() {
	return eIndexType == external;
}
