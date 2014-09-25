/*
 * CRIndex.h
 *
 *      Author: Vinicius
 */

#ifndef __CR_INDEX_H__
#define __CR_INDEX_H__

#include <algorithm>
#include <vector>
#include <iostream>

#include "../Exception.h"
#include "../Partition.h"
#include "../ValidationIndex.h"


class CRIndex : public ValidationIndex {
  public:
		CRIndex() : ValidationIndex("CR", external) {}
        virtual double calculate(Partition &objAPartition1, Partition &objAPartition2);
        virtual double calculate(Partition *pAPartition, RelationSDN *pARelation, DataSet *pADataset);
};

#endif
