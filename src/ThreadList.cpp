/*
 * ThreadList.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#include "ThreadList.h"

namespace DRR
{

const ThreadList::TL_HANDLER ThreadList::Spawn(const LIST_TYPE& listInit, const MILLISECONDS p)
{
	TL_HANDLER ret(new ThreadList(listInit, p));
	ret->attachThread(ret);
	return ret;
}

const ThreadList::TL_HANDLER ThreadList::Restart(TL_HANDLER old)
{
	TL_HANDLER ret(new ThreadList(std::move(*old)));
	ret->attachThread(ret);
	return ret;
}

void ThreadList::Thread(const TL_HANDLER list)
{
	while(list->GetThreadState() != KILL)
	{
		list->resetTime();

		if(list->GetThreadState() == RUNNING)
		{
			if(list->DoAll() < 0)
				list->endThread();
		}
		if(list->getTimeLeftMs() > 0.0)
			std::this_thread::sleep_for(std::chrono::milliseconds(list->getTimeLeftMs()));
	}
}

void ThreadList::killThread()
{
	endThread();
	workThread.detach();
}

const bool ThreadList::joinThread()
{
	if(!workThread.joinable())
		return false;

	workThread.join();
	return true;
}

const bool ThreadList::attachThread(const TL_HANDLER self)
{
	if(this != self)
		return false;

	workThread = thread(&ThreadList::Thread, self);
	return true;
}

const bool ThreadList::exceedsTimeout(clock_t timeoutClocks)
{
	if(timeoutClocks == 0)
		timeoutClocks = GetMaxTime();
	return getElapsed() > timeoutClocks;
}

}

