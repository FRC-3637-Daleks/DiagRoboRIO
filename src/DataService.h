/*
 * DataService.h
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#ifndef SRC_DATASERVICE_H_
#define SRC_DATASERVICE_H_


#include "Defaults.h"
#include "Loggable.h"
#include "Watch_Logs.h"
#include "LogPreferences.h"

using std::vector;
using std::thread;
using std::ofstream;
using std::stringstream;
using std::endl;


/** Pure virtual base class for managing logging
 * Holds a vector of log objects. Derived classes should maintain data streams
 */

class DataService
{
protected:
    enum {THREAD_STATE_INIT, THREAD_STATE_RUNNING, THREAD_STATE_TERMINATE};

private:
	static void LoggingThread(DataService * const ls);

private:
	vector<Loggable *> logObjects;
	thread logThread;
	short threadState;
	unsigned int logPeriodMils;

public:
	DataService(const bool start=false, const unsigned int period=0):
		logThread(&DataService::LoggingThread, this), threadState(start? THREAD_STATE_RUNNING:THREAD_STATE_INIT), logPeriodMils(period) {};
	virtual ~DataService();

protected:
	virtual const int LogAll();
    virtual const int LogAllCurrent();

protected:
    void appendLog(Loggable * const l) {if(l != nullptr) logObjects.push_back(l);};

protected:
    const char getThreadState() const {return threadState;};
    void setThreadState(const char state) {threadState = state;};
    void runThread() {setThreadState(THREAD_STATE_RUNNING);};
    void stopThread() {setThreadState(THREAD_STATE_TERMINATE);};
    void joinThread() {stopThread(); if(logThread.joinable()) logThread.join();};

public:
    const unsigned int getLogPeriod() const {return logPeriodMils;};
};



#endif /* SRC_DATASERVICE_H_ */
