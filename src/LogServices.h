/*
 * LogServices.h
 *
 *  Created on: Jan 18, 2015
 *      Author: edward
 */

#ifndef SRC_LOGSERVICES_H_
#define SRC_LOGSERVICES_H_

#include <sstream>
#include <thread>
#include <ctime>

#include "Config.h"
#include "Loggable.h"
#include "Watch_Logs.h"

using std::vector;
using std::thread;
using std::ofstream;
using std::stringstream;
using std::endl;

/** Pure virtual base class for managing logging
 * Holds a vector of log objects. Derived classes should maintain data streams
 */


class LogService
{
protected:
    enum {THREAD_STATE_INIT, THREAD_STATE_RUNNING, THREAD_STATE_TERMINATE};
    
private:
	static void LoggingThread(LogService * const ls);

private:
	vector<Loggable *> logObjects;
	unsigned int framesUntilWrite;
	unsigned int frames;
	thread logThread;
	char threadState;
	unsigned int logPeriodMils;

public:
	LogService(const bool start=false, const unsigned int period=0, const unsigned int f=DEFAULT_BUFFER_FRAMES):
		framesUntilWrite(f), frames(0), logThread(&LogService::LoggingThread, this),
		threadState(start? THREAD_STATE_RUNNING:THREAD_STATE_INIT), logPeriodMils(period) {};
	virtual ~LogService();

protected:
	virtual ostream& makeLogStream(const string &file)=0;
	virtual const int logCurrent()=0;

	virtual const int LogAll();
    virtual const int LogAllCurrent();

	const char getThreadState() const {return threadState;};
    void setThreadState(const char state) {threadState = state;};
    void runThread() {setThreadState(THREAD_STATE_RUNNING);};
    void stopThread() {setThreadState(THREAD_STATE_TERMINATE);};
    void joinThread() {stopThread(); if(logThread.joinable()) logThread.join();};

    const unsigned int currentFrame() const {return frames;};

public:
	const unsigned int currentFrameTime() const {return frames*logPeriodMils;};
    const unsigned int getFramesUntilWrite() const {return framesUntilWrite;};
    const unsigned int getLogPeriod() const {return logPeriodMils;};

	virtual void createLogDir(const string &command)=0;

	template<typename DATA_TYPE, class SUBSYSTEM_CLASS>
	void addLog(SUBSYSTEM_CLASS * const obj, DATA_TYPE (SUBSYSTEM_CLASS::*func)(), const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway);

	template<typename DATA_TYPE>
	void addLog(std::function<DATA_TYPE(void)> func, const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway);

	virtual void logText(const string &text)=0;
	virtual ostream& logText()=0;
};

template<typename DATA_TYPE, class SUBSYSTEM_CLASS>
inline void LogService::addLog(SUBSYSTEM_CLASS * const obj, DATA_TYPE (SUBSYSTEM_CLASS::*func)(), const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext)
{
	addLog<DATA_TYPE>(std::bind(func, obj), file, ext);
}

template<typename DATA_TYPE>
inline void LogService::addLog(std::function<DATA_TYPE(void)> func, const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext)
{
	logObjects.push_back(new ValueLog<DATA_TYPE>(makeLogStream(file), func, framesUntilWrite, ext));
	logText()<<"[LOGSERVICE][INFO] Created new log: "<<file<<endl;
}

class FileLogger: public LogService
{
private:
	vector<ofstream*> outStreams;
	ofstream stateOut;
	stringstream doubleBuffer[2];
	short writer;

public:
	FileLogger(const string &file, const string &command);
	virtual ~FileLogger();

public:
	void createLogDir(const string &command) override;
	virtual void logText(const string &text) override;
	virtual ostream& logText() override;

public:
	virtual const int LogAll() override;

protected:
	virtual ofstream& makeLogStream(const string &file) override;
	virtual const int logCurrent() override;
};

/*
class BinaryFileLogger: public FileLogger
{
public:
	BinaryFileLogger(const string &file, const string &command): FileLogger(file, command) {};
	virtual ~BinaryFileLogger() {};

protected:
	virtual ostream& makeLogStream(const string &file) override;
};
*/

#endif /* SRC_LOGSERVICES_H_ */
