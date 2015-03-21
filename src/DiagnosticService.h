/*
 * DiagnosticService.h
 *
 *  Created on: Feb 17, 2015
 *      Author: Edward
 */

#ifndef SRC_DIAGNOSTICSERVICE_H_
#define SRC_DIAGNOSTICSERVICE_H_

#include <thread>
#include <vector>
#include <memory>

#include "PollValue.h"
#include "ThreadList.h"
#include "FramePusher.h"


namespace DRR
{

using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::thread;

class DiagnosticService
{
private:
	static const long long Tick();	///< Returns an incrementing frame id
	static const long long Tock();	///< Returns the time since its first call in milliseconds

public:
	static const long long GetCurrentFrame();
	static const long long GetTimeElapsed();

	static const shared_ptr<PollValue<long long> > GetFramePoll() {return ticker;};
	static const shared_ptr<PollValue<long long> > GetTimePoll() {return tocker;};

private:
	static vector<shared_ptr<PushPullBase>> pollInit;
	static shared_ptr<PollValue<long long> > ticker, tocker;
	static vector<ThreadList::TL_HANDLER> threads;
	static thread monitor;
	static ThreadList::THREAD_STATE state;

private:
	static void Monitor();

private:
	static MILLISECONDS pollPeriod;
	static MILLISECONDS monitorPeriod;

public:
	static const bool Init();

	static const MILLISECONDS GetPollPeriod() {return pollPeriod;};
	static const MILLISECONDS GetMonitorPeriod() {return monitorPeriod;};
	static void SetPollPeriod(const MILLISECONDS p) {if(!IsInitialized()) pollPeriod = p;};
	static void SetMonitorPeriod(const MILLISECONDS p) {if(!IsInitialized()) monitorPeriod = p;};

protected:
	/// Adds poll to poller, returns success
	static const bool AddPoll(const shared_ptr<Poller> poll);

	/// Adds pushThread to threads, returns success
	static const bool AddThread(const ThreadList::TL_HANDLER &pushThread);

	static const bool IsInitialized() {return state != ThreadList::INIT;};

};

}




#endif /* SRC_DIAGNOSTICSERVICE_H_ */
