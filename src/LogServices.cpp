/*
 * LogServices.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: edward
 */

#include "LogServices.h"

LogService::LogService(const bool start, const unsigned int period, const bool hijackSTD, const unsigned int f):
				DataService(start, period), oldCout(std::cout.rdbuf()), oldCerr(std::cerr.rdbuf()), framesUntilWrite(f), frames(0)
{
	if(hijackSTD)
	{
		std::ios_base::sync_with_stdio(true);
		std::cout.rdbuf(coutRedirect.rdbuf());
		std::cerr.rdbuf(cerrRedirect.rdbuf());
	}
}

LogService::LogService(const LogService &other): DataService(other), oldCout(other.oldCout.rdbuf()), oldCerr(other.oldCerr.rdbuf()),
		framesUntilWrite(other.framesUntilWrite), frames(other.frames)
{
	if(std::cout.rdbuf() == other.coutRedirect.rdbuf() && std::cout.rdbuf() == other.coutRedirect.rdbuf())
	{
		std::cout.flush();
		std::cerr.flush();

		std::cout.rdbuf(coutRedirect.rdbuf());
		std::cerr.rdbuf(cerrRedirect.rdbuf());
	}
}

LogService::~LogService()  // Deallocates memory
{
}

const int LogService::LogAll()
{
	frames++;

	return DataService::LogAll();
}

const int LogService::logCurrent()
{
	if(coutRedirect.rdbuf()->in_avail() > 0)
	{
		oldCout<<coutRedirect.str();
		/*char buf[255];
		while(!coutRedirect.eof())
		{
			coutRedirect.getline(buf, 255);
			logText()<<"[STDOUT][INFO] "<<buf<<std::endl;
		}*/
		logText()<<"[STDOUT][INFO]"<<coutRedirect.rdbuf()<<std::endl;
		coutRedirect.clear();
	}

	if(coutRedirect.rdbuf()->in_avail() > 0)
	{
		oldCerr<<cerrRedirect.str();
		char buf[255];
		while(!cerrRedirect.eof())
		{
			coutRedirect.getline(buf, 255);
			logText()<<"[STDERR][ERR] "<<buf<<std::endl;
		}
		coutRedirect.clear();
	}

	return 0;
}

void LogService::logStdout(const string &text)
{
	logStdout()<<text<<endl;
}

ostream& LogService::logStdout()
{
	oldCout.width(FRAME_TEXT_WIDTH);
	oldCout.fill('0');
	return oldCout<<currentFrameTime()<<": ";
}

void LogService::logStderr(const string &text)
{
	logStderr()<<text<<endl;
}

ostream& LogService::logStderr()
{
	oldCerr.width(FRAME_TEXT_WIDTH);
	oldCerr.fill('0');
	return oldCerr<<currentFrameTime()<<": ";
}
