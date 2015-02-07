/*
 * DataService.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#include "DataService.h"

void DataService::DataThread(DataService::DS_HANDLER ds)
{
	if(ds == nullptr)
	{
		return;
	}
	while(ds->getThreadState() == THREAD_STATE_INIT);
	int failed = 0;
	while(ds->getThreadState() == THREAD_STATE_RUNNING && failed >= 0)
	{
		clock_t c = clock();
		failed = ds->LogAll();

		// Ensures logger keeps to schedule
		if(clock() - c > ds->getLogPeriod()*CLOCKS_PER_SEC/1000)
			std::this_thread::sleep_for(std::chrono::milliseconds(ds->getLogPeriod() - (clock()-c)*1000/CLOCKS_PER_SEC));
	}
    ds->LogAllCurrent();
    if(ds->getThreadState() == THREAD_STATE_RUNNING)
    	; // In which the logger quit due to a callback function returning KILL
}

DataService::DataService(const DataService& other):
		logObjects(other.logObjects), logThread(),
		threadState(THREAD_STATE_RUNNING), logPeriodMils(other.logPeriodMils), time(0), logIter(other.logIter < 0? -1:other.logIter+1)
{

}

DataService::~DataService()
{
	joinThread();
	/*for(auto i = logObjects.begin(); i != logObjects.end(); i++)
    {
		delete *i;
    }*/
    logObjects.clear();
}

const int DataService::LogAll()
{
	int ret = 0;
	feedTimeout();
	for(logIter = 0; logIter < logObjects.size() && ret >=0; logIter++)
	{
		ret |= logObjects[logIter]->Log();
		feedTimeout();
	}

	logIter = -1;
	return ret;
}

const int DataService::LogAllCurrent()
{
	int ret = 0;
	for(unsigned int i = 0; i < logObjects.size() && ret >= 0; i++)
		ret |= logObjects[i]->logCurrent();

	return ret;
}

void DataService::initThread(const DataService::DS_HANDLER& self)
{
	if(self.get() != this)
		return;

	logThread = thread(&DataService::DataThread, self);
}

void DataService::killThread()
{
	stopThread();
	logThread.detach();
}


const bool DataService::exceedsTimeout(unsigned int microseconds)
{
	if(logIter < 0)  // Not in the midst of logging, no chance of blocking, no need for time out
		return false;

	if(microseconds == 0) // Default case
		microseconds = getLogPeriod()*1000/logObjects.size();


	return time*1000*1000/CLOCKS_PER_SEC > microseconds;
}

const DataService::DS_HANDLER DataService::emergencyClone() const
{
	return Create<DataService>([this]() {return new DataService(*this);});
}

