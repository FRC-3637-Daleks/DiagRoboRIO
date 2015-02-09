/*
 * DoList.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#include "DoList.h"
#include <algorithm>

namespace DRR
{

const int DoList::DoAll()
{
	int ret = 0;
	for(iteration = 0; iteration < size() && ret >= 0; iteration++)
	{
		ret |= at(iteration)->Do();
	}

	iteration = -1;
	return ret;
}

}


