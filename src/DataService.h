/*
 * DataService.h
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#ifndef SRC_DATASERVICE_H_
#define SRC_DATASERVICE_H_

#include <ctime>
#include <memory>

#include "Defaults.h"
#include "Loggable.h"
#include "Watch_Logs.h"
#include "LogPreferences.h"

using std::vector;
using std::thread;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::shared_ptr;


/** Pure virtual base class for managing logging
 * Holds a vector of log objects. Derived classes should maintain data streams
 */

class DataService
{
public:
	typedef shared_ptr<DataService> DS_HANDLER;
protected:
    enum {THREAD_STATE_INIT, THREAD_STATE_RUNNING, THREAD_STATE_TERMINATE};

private:
	static void DataThread(DS_HANDLER ds);

public:
	static const DS_HANDLER Create(std::function<DataService * ()> factory);

private:
	vector<shared_ptr<Loggable>> logObjects;
	thread logThread;
	short threadState;
	unsigned int logPeriodMils;
	clock_t time;
	int logIter;

protected:  // Ensures dynamic allocation of DataServices
	DataService(const bool start=false, const unsigned int period=0): logThread(),
		threadState(start? THREAD_STATE_RUNNING:THREAD_STATE_INIT),
		logPeriodMils(period), time(0), logIter(0) {};

	DataService(const DataService& other);   /// Called by emergencyClone

public:
	virtual ~DataService();

protected:
	virtual const int LogAll();
    virtual const int LogAllCurrent();

protected:
    void appendLog(Loggable * const l) {if(l != nullptr && threadState != THREAD_STATE_RUNNING) logObjects.push_back(shared_ptr<Loggable>(l));};

private:
    void initThread(const DS_HANDLER& self);

protected:
    const char getThreadState() const {return threadState;};
    void setThreadState(const short state) {if(logThread.joinable()) threadState = state;};  /// Changes safe thread state
    void runThread() {setThreadState(THREAD_STATE_RUNNING);};	   /// Allows thread to start running
    void stopThread() {setThreadState(THREAD_STATE_TERMINATE);};   /// Safely changes thread state to stop running
    void killThread();	/// Detaches thread and sets state to stop running
    void joinThread() {stopThread(); if(logThread.joinable()) logThread.join();};   /// Waits for thread to finish
    void feedTimeout() {time = clock();};

public:
    /// Literally too lazy to reorganize the functions above with different access modifiers
    void startLogging() {runThread();};
    void stopLogging() {stopThread();};
    void killLogging() {killThread();};

public:
    const unsigned int getLogPeriod() const {return logPeriodMils;};
    const short getThreadState() const {return threadState;};
    const bool exceedsTimeout(unsigned int microseconds=0);   /// Returns true if a timeout has been exceeded in a state of logging. 0 indicates to use default timeout
    const int getCurrentIteration() const {return logIter;};
    virtual const DS_HANDLER emergencyClone() const;		/// Clones the DataService with all log objects except for the fail-point
};



#endif /* SRC_DATASERVICE_H_ */
