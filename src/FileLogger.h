/*
 * FileLogger.h
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#ifndef SRC_FILELOGGER_H_
#define SRC_FILELOGGER_H_

#include "LogServices.h"

class FileLogger: public LogService
{
private:
	vector<ofstream*> outStreams;
	ofstream stateOut;
	stringstream doubleBuffer[2];
	short writer;

public:
	FileLogger(const string &file, const string &command, const MILLISECONDS flp, const unsigned int f);
	virtual ~FileLogger();

public:
	void createLogDir(const string &command) override;
	const unsigned int makeInfo(const string &file) override;
	virtual void logText(const string &text) override;
	virtual ostream& logText() override;

public:
	virtual const int LogAll() override;

protected:
	virtual ofstream& makeLogStream(const string &file) override;
	virtual const int logCurrent() override;
};



#endif /* SRC_FILELOGGER_H_ */
