/*
 * DiagnosticService.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: edward
 */

#include <iostream>
#include "DiagnosticService.h"

namespace DRR
{

vector<shared_ptr<PushPullBase>> DiagnosticService::pollInit;

vector<ThreadList::TL_HANDLER> DiagnosticService::threads;

thread DiagnosticService::monitor(&DiagnosticService::Monitor);

ThreadList::THREAD_STATE DiagnosticService::state(ThreadList::INIT);

MILLISECONDS DiagnosticService::pollPeriod = DEFAULT_POLL_PERIOD;
MILLISECONDS DiagnosticService::monitorPeriod = DEFAULT_MONITOR_PERIOD;

void DiagnosticService::Monitor()
{
	while(state == ThreadList::INIT)
		std::this_thread::sleep_for(std::chrono::milliseconds(monitorPeriod));


	for(unsigned int i = 0; i < threads.size(); i++)
	{
		std::cout<<"Starting thread "<<i<<std::endl;
		threads[i]->Start();
		std::cout<<"Thread Started "<<i<<std::endl;
	}


	while(state == ThreadList::RUNNING)
	{
		for(unsigned int i = 0; i < threads.size(); i++)
		{
			// If the thread is running but exceeds its timeout, restart it
			if(threads[i]->exceedsTimeout() && threads[i]->GetThreadState() == ThreadList::RUNNING)
			{
				std::cout<<"Thread timed out. Average Period micros: "<<threads[i]->GetAveragePeriod().count()<<"Max Time in millis"<<threads[i]->GetMaxTime().count()<<std::endl;
				ThreadList::Restart(&threads[i]);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(monitorPeriod));
	}

	for(unsigned int i = 0; i < threads.size(); i++)
	{
		threads[i]->End();
	}
}

const bool DiagnosticService::Init()
{
	if(IsInitialized())
		return false;
	for(unsigned int i = 0; i < threads.size(); i++)
	{
		threads[i]->attachThread(threads[i]);
	}
	threads.push_back(ThreadList::Spawn(pollInit, pollPeriod));
	state = ThreadList::RUNNING;
	return true;
}

const bool DiagnosticService::AddPoll(const shared_ptr<Poller> poll)
{
	if(poll == nullptr)
		return false;

	if(state != ThreadList::INIT)
		return false;

	pollInit.push_back(poll);
	return true;
}

const bool DiagnosticService::AddThread(const shared_ptr<ThreadList> &pushThread)
{
	if(pushThread == nullptr)
		return false;

	threads.push_back(pushThread);
	return true;
}



}


