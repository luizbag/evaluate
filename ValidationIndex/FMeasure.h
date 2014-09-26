/*
 * FMeasure.h
 *
 *  Created on: Mar 25, 2012
 *      Author: marcus
 */

#ifndef FMEASURE_H_
#define FMEASURE_H_

#include <algorithm>
#include <vector>
#include <iostream>

#include "../Exception.h"
#include "../Partition.h"
#include "../ValidationIndex.h"


class FMeasure : public ValidationIndex {
  public:
		FMeasure();
        virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
        virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset);
};

#endif /* FMEASURE_H_ */
