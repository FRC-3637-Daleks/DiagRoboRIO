/*
 * StreamHandle.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: 3637-DS-0
 */

#include "StreamHandle.h"
#include "TextLog.h"

namespace DRR
{

void StreamHandle::Push()
{
	TextLog::Log(service, buf.str(), level);
	pushed = true;
}


}


