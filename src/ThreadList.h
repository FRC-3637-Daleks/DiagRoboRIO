/*
 * ThreadList.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_THREADLIST_H_
#define SRC_THREADLIST_H_

#include <thread>
#include <memory>
#include <ctime>

#include "LogPreferences.h"
#include "DoList.h"

namespace DRR
{

using std::thread;

class ThreadList: public DoList
{
public:
	typedef enum {INIT, RUNNING, KILL} THREAD_STATE;
	typedef shared_ptr<ThreadList> TL_HANDLER;

public:
	/// Constructs a new ThreadList and attaches it to itself, returning the
	static const TL_HANDLER Spawn(const LIST_TYPE& listInit, const MILLISECONDS p);

	/// Copies the old thread into a new thread, detaching the old and return the new
	static const TL_HANDLER Restart(TL_HANDLER old);
	static void Restart(TL_HANDLER *handler);

private:
	/// Function which is run by the thread
	static void Thread(const TL_HANDLER list);

private:
	thread workThread;
	THREAD_STATE threadState;
	MILLISECONDS period;
	clock_t time;

protected:	// Should be called with special creator
	ThreadList(const LIST_TYPE& listInit, const MILLISECONDS p): DoList(listInit), threadState(INIT), period(p), time(clock()) {};

	ThreadList(const MILLISECONDS p): threadState(INIT), period(p), time(clock()) {};

	/// Makes sure old list is detached and no longer running
	ThreadList(ThreadList&& other): DoList(other), threadState(other.threadState),
			period(other.period), time(clock()) {other.killThread();};

public:
	virtual ~ThreadList() {};

private:  // internals
	void resetTime() {time = clock();};
	clock_t getElapsed() const {return time-clock();};
	MILLISECONDS getElapsedMs() const {return getElapsed()*1000/CLOCKS_PER_SEC;};
	MILLISECONDS getTimeLeftMs() const {return period-getElapsedMs();};

protected: // Thread Control
	void setThreadState(const THREAD_STATE state) {threadState = state;};
	void runThread() {setThreadState(RUNNING);};
	void endThread() {setThreadState(KILL);};
	void killThread();
	const bool joinThread();
	const bool attachThread(const TL_HANDLER self);

public:
	void Start() {runThread();};
	void End() {endThread();};
	void Kill() {killThread();};

public:	// Info
	const THREAD_STATE GetThreadState() const {return threadState;};
	const MILLISECONDS GetPeriod() const {return period;};
	const clock_t GetPeriodClocks() const {return GetPeriod()*CLOCKS_PER_SEC/1000;};
	const clock_t GetAveragePeriod() const {return GetPeriod()/size();};
	const clock_t GetMaxTime() const {return (GetIteration()+1)*GetAveragePeriod();};
	const bool exceedsTimeout(clock_t timeoutClocks=0);
};


}

#endif /* SRC_THREADLIST_H_ */
