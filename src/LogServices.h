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
#include "DataService.h"
#include "StreamLog.h"

class LogService: public DataService
{
private:
	ostream oldCout;
	ostream oldCerr;
	stringstream coutRedirect;
	stringstream cerrRedirect;
	unsigned int framesUntilWrite;
	unsigned int frames;

public:
	LogService(const bool start=false, const unsigned int period=0, const bool hijackSTDOUT=true, const unsigned int f=1);
	virtual ~LogService();

protected:
	virtual ostream& makeLogStream(const string &file)=0;
	virtual const int logCurrent()=0;

	virtual const int LogAll() override;

    const unsigned int currentFrame() const {return frames;};

public:
	const unsigned int currentFrameTime() const {return frames*getLogPeriod();};
    const unsigned int getFramesUntilWrite() const {return framesUntilWrite;};

	virtual void createLogDir(const string &command)=0;
	virtual const unsigned int makeInfo(const string &file)=0;

	template<typename DATA_TYPE, class SUBSYSTEM_CLASS>
	typename ValueLog<DATA_TYPE>::FUNC_t addLog(SUBSYSTEM_CLASS * const obj, DATA_TYPE (SUBSYSTEM_CLASS::*func)(), const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway);

	template<typename DATA_TYPE>
	typename ValueLog<DATA_TYPE>::FUNC_t addLog(std::function<DATA_TYPE(void)> func, const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway);

	virtual void logText(const string &text)=0;
	virtual ostream& logText()=0;
	void logStdout(const string &text);
	ostream& logStdout();
	void logStderr(const string &text);
	ostream& logStderr();
};

template<typename DATA_TYPE, class SUBSYSTEM_CLASS>
inline typename ValueLog<DATA_TYPE>::FUNC_t LogService::addLog(SUBSYSTEM_CLASS * const obj, DATA_TYPE (SUBSYSTEM_CLASS::*func)(), const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext)
{
	return addLog<DATA_TYPE>(std::bind(func, obj), file, ext);
}

template<typename DATA_TYPE>
inline typename ValueLog<DATA_TYPE>::FUNC_t LogService::addLog(std::function<DATA_TYPE(void)> func, const string &file, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext)
{
	ValueLog<DATA_TYPE> *l;
	appendLog(l = new StreamLog<DATA_TYPE>(makeLogStream(file), func, framesUntilWrite, ext));
	logText()<<"[LOGSERVICE][INFO] Created new log: "<<file<<endl;
	return l->makeExtension();
}

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
