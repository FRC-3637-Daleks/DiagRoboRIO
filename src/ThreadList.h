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
#include <chrono>

#include "LogPreferences.h"
#include "DoList.h"

namespace DRR
{

using std::thread;

class ThreadList: public DoList
{
private:
	typedef std::chrono::time_point<std::chrono::system_clock> time_point;

public:
	typedef enum {INIT, RUNNING, KILL} THREAD_STATE;
	typedef shared_ptr<ThreadList> TL_HANDLER;

public:
	/// Constructs a new ThreadList and attaches it to itself, returning the thread
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
	std::chrono::milliseconds period;
	time_point last;

protected:	// Should be called with special creator
	ThreadList(const LIST_TYPE& listInit, const MILLISECONDS p): DoList(listInit), threadState(INIT), period(p), last(getNow()) {};

	ThreadList(const MILLISECONDS p): threadState(INIT), period(p), last(getNow()) {};

	/// Makes sure old list is detached and no longer running
	ThreadList(ThreadList&& other): DoList(other), threadState(other.threadState),
			period(other.period), last(getNow()) {other.killThread();};

public:
	virtual ~ThreadList() {};

private:  // internals
	static const time_point getNow() {return std::chrono::system_clock::now();};
	void resetTime() {last = getNow();};
	const std::chrono::milliseconds getElapsed() const {return std::chrono::duration_cast<std::chrono::milliseconds>(getNow() - last);};
	const std::chrono::milliseconds getTimeLeft() const {return std::chrono::milliseconds(period)-getElapsed();};

protected: // Thread Control
	void setThreadState(const THREAD_STATE state) {threadState = state;};
	void runThread() {setThreadState(RUNNING);};
	void endThread() {setThreadState(KILL);};
	void killThread();
	const bool joinThread();

public:
	const bool attachThread(const TL_HANDLER self);

public:
	void Start() {runThread();};
	void End() {endThread();};
	void Kill() {killThread();};

public:	// Info
	const THREAD_STATE GetThreadState() const {return threadState;};
	const std::chrono::milliseconds GetPeriod() const {return period;};
	const std::chrono::microseconds GetAveragePeriod() const {return std::chrono::microseconds(GetPeriod())/size();};
	const std::chrono::milliseconds GetMaxTime() const {return std::chrono::duration_cast<std::chrono::milliseconds>((GetIteration()+1)*GetAveragePeriod());};
	const bool exceedsTimeout(const std::chrono::milliseconds timeoutClocks=std::chrono::milliseconds::zero());
};


}

#endif /* SRC_THREADLIST_H_ */
