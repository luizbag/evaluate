/*
 * ValidationIndex.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#ifndef VALIDATIONINDEX_H_
#define VALIDATIONINDEX_H_

#include <cmath>
#include <iostream>
#include <math.h>

#include "Partition.h"
#include "RelationSDN.h"

using namespace std;

/// Abstract class with two calculate methods, the one with two parameters is to be used in external validation measures and the other one is to be used in internal validation measures
/**Abstract class with two calculate methods, the one with two parameters is to be used in external validation measures and the other one is to be used in internal validation measures */
class ValidationIndex {
protected:
	enum IndexType {internal, external};

	const string sIndexName;
	IndexType eIndexType;


public:
	ValidationIndex(std::string sAIndexName, IndexType eAIndexType);

	virtual ~ValidationIndex() {};

	/** Method virtual from return value of measure validation internal */
	/** @param Partition, RelationSDN and DataSet */
	/** @return Returns value from measure validation*/
	virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pDataSet) = 0;

	/** Method virtual from return value of measure validation external */
	/** @param Two Partitions */
	/** @return Returns value from measure validation*/
	virtual double calculate(Partition &objPartition1, Partition &objPartition2, int iNumT) = 0;


	string getValidationIndexName();

	/**  @return Returns true if the index is for an internal validation criteria */
	bool isInternal();

	/**  @return Returns true if the index is for an external validation criteria */
	bool isExternal();
};

#endif /* VALIDATIONINDEX_H_ */
