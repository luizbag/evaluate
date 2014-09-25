/*
 * Object.h
 *
 *  Created on: Jun 21, 2011
 *      Author: Marcus Vinicius
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/// Represents an Object and its features
/** Represents an Object and its features */
class Object {

	private:
		string sId; ///< Object ID
		vector<double> vectorFeatures; ///< Vector of Object features

	public:
		typedef vector<double>::iterator itFeaturesOfObject;

		/** Initializes the vector of features with zeros */
		/** @param Don't have */
		void initialize();

		/** Adds in the vector, the feature of the Object */
		/** @param Feature to be added */
		void addFeature(double dAFeature);

		/** Accesses the iAIndex-th position of the features' vector */
		/** @param The index of the wished feature */
		/** @return Returns the iAIndex-th feature of the Object */
		double & operator[] (const int iAIndex);

		/** Prints the Object */
		/** @param Don't have */
		void print();

		/** Gets the iAIndex-th position of the features' vector */
		/** @param The index of the wished feature */
		/** @return Returns the iAIndex-th feature of the Object */
		double getFeature(const int iAIndex) const;

		/** Gets the number of features that the Object has */
		/** @param Don't have */
		/** @return Returns the number of features of the Object */
		int getNumberOfFeatures() const;

		/** Gets the Object ID */
		/** @param Don't have */
		/** @return Returns the Object ID */
		string getId();

		/** Sets the Object ID */
		/** @param Object ID */
		void setId(string sAId);

		/** Iterator that points to the beginning of the features' vector */
		/** @param Don't have */
		itFeaturesOfObject begin();

		/** Iterator that points to the end of the features' vector */
		/** @param Don't have */
		itFeaturesOfObject end();
};

#endif /* OBJECT_H_ */
