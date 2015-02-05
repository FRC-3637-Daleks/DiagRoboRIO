/*
 * FileLogger.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#include "FileLogger.h"

FileLogger::FileLogger(const string &file, const string &command, const MILLISECONDS flp, const unsigned int f): LogService(false, flp, true, f), writer(0)
{
	createLogDir(command);
	stateOut.open(file, std::ios_base::out);
    runThread();
}

FileLogger::~FileLogger()
{
    logText()<<"[FILELOGGER][INFO] Closing file output streams"<<endl;
    logText()<<"[FILELOGGER][INFO] Deleting LogService"<<endl;
    joinThread();
	for(auto i = outStreams.begin(); i != outStreams.end(); i++)
	{
		delete *i;
	}
	outStreams.clear();
    logCurrent();
}

ofstream& FileLogger::makeLogStream(const string &file)
{
	outStreams.push_back(new ofstream(file, std::ios_base::out));
	return *outStreams.back();
}

void FileLogger::createLogDir(const string &command)
{
	if(system(command.c_str()) >= 0)
	{
		logText()<<"[FILELOGGER][INFO] `"<<command<<"` Directory made successfully"<<endl;
	}
}

const unsigned int FileLogger::makeInfo(const string &file)
{
	ofstream info(file, std::ios_base::out);
	info<<"BUILT:"<<__DATE__<<' '<<__TIME__<<endl;
	return 0;
}

void FileLogger::logText(const string &text)
{
	logText()<<text<<endl;
}

ostream& FileLogger::logText()
{
    if(doubleBuffer[writer].eof())
        doubleBuffer[writer].clear();
	doubleBuffer[writer].fill('0');
	doubleBuffer[writer].width(FRAME_TEXT_WIDTH);
	return doubleBuffer[writer]<<currentFrameTime()<<": ";
}

const int FileLogger::logCurrent()
{
	LogService::logCurrent();
    const short prev = writer;
	if(writer == 0) writer = 1;
    else if(writer == 1) writer = 0;
    if(doubleBuffer[prev].rdbuf()->in_avail() > 0)
    {
        doubleBuffer[prev]>>stateOut.rdbuf();
    }
	stateOut.flush();
	return 0;
}

const int FileLogger::LogAll()
{
    if(currentFrame() % getFramesUntilWrite() == 0)
        logCurrent();
	return LogService::LogAll();
}

