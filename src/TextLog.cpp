/*
 * TextLog.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: edward
 */

#include <iostream>
#include "DiagnosticService.h"
#include "DatumValue.h"
#include "TextLog.h"

namespace DRR
{

const char * LEVEL_t::text[] = {
		[EMER] = "EMER",
		[ALERT] = "ALERT",
		[CRIT] = "CRIT",
		[ERR] = "ERR",
		[WARN] = "WARN",
		[NOTICE] = "NOTICE",
		[INFO] = "INFO",
		[DEBUG] = "DEBUG"
};


shared_ptr<TextLog> TextLog::handler(new TextLog());
shared_ptr<PollValue<long long>> TextLog::stamp(DiagnosticService::GetFramePoll());

const int TextLog::Log(const string & service, const LEVEL_t level, const string & message)
{
	if(!handler)
		return -1;
	return handler->LogInternal(
			DatumValue<long long>(stamp->getPreviousValue()).toString() +
			string("[")+service+"]["+LEVEL_t::text[level]+"] " +
			message);
}

const int TextLog::LogInternal(const string & message)
{
	std::cout<<message<<std::endl;
	return 0;
}

}


