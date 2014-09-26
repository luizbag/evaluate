/*
 * Similarity.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: Marcus Vinicius
 */

#include "Similarity.h"
using namespace std;

bool Similarity::isSimilarity(){
	return bSimilarity;
}

Similarity::Similarity(std::string sASimilarityName, std::string sASimilarityShortName, bool bASimilarity)
: sSimilarityName(sASimilarityName),
  sSimilarityShortName(sASimilarityShortName),
  bSimilarity(bASimilarity) {}


string Similarity::getSimilarityName() {
	return sSimilarityName;
}

string Similarity::getSimilarityShortName() {
	return sSimilarityShortName;
}
