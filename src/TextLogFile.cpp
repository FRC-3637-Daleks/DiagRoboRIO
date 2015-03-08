/*
 * TextLogFile.cpp
 *
 *  Created on: Mar 7, 2015
 *      Author: 3637-DS-1
 */

#include <sstream>
#include "TextLogFile.h"

namespace DRR
{

const int TextLogFile::LogInternal(const string & message)
{
	if(FilePusher::Log(message+'\n'));
		return 0;
	return -1;
}


}


