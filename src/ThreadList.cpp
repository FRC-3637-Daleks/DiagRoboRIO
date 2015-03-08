/*
 * ThreadList.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#include <iostream>
#include "ThreadList.h"

namespace DRR
{

const ThreadList::TL_HANDLER ThreadList::Create(const LIST_TYPE& listInit, const MILLISECONDS p)
{
	TL_HANDLER ret(new ThreadList(listInit, p));
	return ret;
}

const ThreadList::TL_HANDLER ThreadList::Spawn(const LIST_TYPE& listInit, const MILLISECONDS p)
{
	TL_HANDLER ret = ThreadList::Create(listInit, p);
	ret->attachThread(ret);
	return ret;
}

const ThreadList::TL_HANDLER ThreadList::Restart(TL_HANDLER old)
{
	TL_HANDLER ret(new ThreadList(std::move(*old)));
	ret->attachThread(ret);
	return ret;
}

void ThreadList::Restart(TL_HANDLER *handler)
{
	*handler = Restart(*handler);
}

void ThreadList::Thread(const TL_HANDLER list)
{
	time_point schedule = getNow();
	while(list->GetThreadState() != KILL)
	{
		schedule += list->period;
		list->resetTime();

		if(list->GetThreadState() == RUNNING)
		{
			if(list->DoAll() < 0)
				list->endThread();
		}
		if(list->getTimeLeft() > std::chrono::milliseconds::zero())
			std::this_thread::sleep_until(schedule);
		else
		{
			std::this_thread::yield();
			schedule = getNow();
		}
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
	if(this != self.get())
		return false;

	workThread = thread(&ThreadList::Thread, self);
	return true;
}

const bool ThreadList::AddToList(const shared_ptr<PushPullBase> item)
{
	if(threadState != INIT)
		return false;
	push_back(item);
	return true;
}

const bool ThreadList::exceedsTimeout(std::chrono::milliseconds timeoutClocks)
{
	if(GetIteration() < 0)
		return false;
	if(timeoutClocks == std::chrono::milliseconds::zero())
		timeoutClocks = GetMaxTime();
	return getElapsed() > timeoutClocks;
}

}


