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

StreamHandle::StreamHandle(StreamHandle && other): service(other.service), instance(other.instance), level(other.level), pushed(other.pushed)
{
	buf << other.buf.str();
	other.buf.str("");
	other.pushed = true;
}

void StreamHandle::Push()
{
	TextLog::Log(service, instance, buf.str(), level);
	pushed = true;
}

}


