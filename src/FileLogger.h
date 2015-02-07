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
public:
	typedef shared_ptr<FileLogger> FS_HANDLER;
	static const FS_HANDLER Create(const string &file, const string &command, const MILLISECONDS flp, const unsigned int f)
	{
		return DataService::Create<FileLogger>([file, command, flp, f]() {return new FileLogger(file, command, flp, f);});
	}

private:
	vector<shared_ptr<ofstream> > outStreams;
	shared_ptr<ofstream> stateOut;
	stringstream doubleBuffer[2];
	short writer;

protected:
	FileLogger(const string &file, const string &command, const MILLISECONDS flp, const unsigned int f);
	FileLogger(const FileLogger& other);

public:
	virtual const DS_HANDLER emergencyClone() const override;
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
