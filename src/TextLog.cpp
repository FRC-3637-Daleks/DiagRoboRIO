/*
 * TextLog.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: edward
 */

#include "TextLog.h"

namespace DRR
{


const char * [] LEVEL_t::text = {
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

const int TextLog::Log(const string & service, const LEVEL_t level, const string & message)
{
	if(!handler)
		return -1;
	return handler->LogInternal(string("[")+service+"]["+LEVEL_t::text[level]+"] " + message);
}

const int TextLog::LogInternal(const string & message)
{
	std::cout<<message<<std::endl;
	return 0;
}

}


