/*
 * DataService.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#include "DataService.h"

void DataService::LoggingThread(DataService * const ls)
{

	if(ls == nullptr)
	{
		return;
	}
	while(ls->getThreadState() == THREAD_STATE_INIT);
	int failed = 0;
	//clock_t c = 0;
	while(ls->getThreadState() == THREAD_STATE_RUNNING && failed >= 0)
	{
		//if(clock() - c >= (int)ls->getLogPeriod()*CLOCKS_PER_SEC/1000)
		//{
			failed = ls->LogAll();
		//	c = clock();
		//}
		std::this_thread::sleep_for(std::chrono::milliseconds(ls->getLogPeriod()));
	}
    ls->LogAllCurrent();
    if(ls->getThreadState() == THREAD_STATE_RUNNING)
    	; // In which the logger quit due to a callback function returning KILL
}

DataService::~DataService()
{
	joinThread();
	for(auto i = logObjects.begin(); i != logObjects.end(); i++)
    {
		delete *i;
    }
    logObjects.clear();
}

const int DataService::LogAll()
{
	int ret = 0;
	for(unsigned int i = 0; i < logObjects.size() && ret >=0; i++)
		ret |= logObjects[i]->Log();

	return ret;
}

const int DataService::LogAllCurrent()
{
	int ret = 0;
	for(unsigned int i = 0; i < logObjects.size() && ret >= 0; i++)
		ret |= logObjects[i]->logCurrent();

	return ret;
}
