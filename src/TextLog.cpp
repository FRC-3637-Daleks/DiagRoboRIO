/*
 * TextLog.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: edward
 */

#include <sstream>
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


vector<shared_ptr<TextLog>> TextLog::listeners({shared_ptr<TextLog>(new TextLog())});
shared_ptr<PollValue<long long>> TextLog::stamp(DiagnosticService::GetFramePoll());

const int TextLog::Log(const string & service, const string & message, const LEVEL_t level)
{
	std::stringstream ss;
	ss.width(10);
	ss.fill('0');
	ss<<stamp->getPreviousValue()<<": ["<<service<<"]["<<LEVEL_t::text[level]<<"] "<<message;

	int ret = 0;
	for(int i = 0; i < listeners.size(); i++)
		ret |= listeners[i]->LogInternal(ss.str());

	return ret;
}

const int TextLog::LogInternal(const string & message)
{
	std::cout<<message<<std::endl;
	return 0;
}

}


