#include <sys/stat.h>
#include "Logger.h"

/********* STATIC LOGGER DATA MEMBERS *************/

shared_ptr<LogService> Logger::service = nullptr;
string Logger::path;
LogPreferences Logger::preferences;

std::function<LogService *()> Logger::factory = []()
{
	return new FileLogger(Logger::GetFullPath()+Logger::GetPreferences().text_log_filename,
							Logger::GetMakeDirCommand(),
							Logger::GetPreferences().log_period,
							Logger::GetPreferences().n_buffer_frames);
};

/********** STATIC LOGGER CONSTANTS *****************/

const char* LEVEL_t::text[] = {
		"EMER", "ALERT", "CRIT", "ERR", "WARN", "NOTICE", "INFO", "DEBUG"
};


/******** STATIC LOGGER GET FUNCTIONS **********/

const string Logger::GetLogPath()
{
	struct stat info;
	if(stat(preferences.log_home_path, &info) < 0)
	{
		mkdir(preferences.log_home_path,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	return string(preferences.log_home_path);
}

const string Logger::GetRunTimeDirectory()
{
	using std::ios_base;
	static string runTimeID;
	if(runTimeID.empty())
	{
		unsigned int nRunTimeID = 0;
		std::fstream rtFile(GetLogPath()+"runtimeID", ios_base::in);
		rtFile>>nRunTimeID;
		nRunTimeID++;

		rtFile.close();
		rtFile.open(GetLogPath()+"runtimeID", ios_base::out | ios_base::trunc);
		rtFile<<nRunTimeID;

		stringstream ss;
		ss.width(5);
		ss.fill('0');
		ss<<nRunTimeID;
		runTimeID = ss.str();
	}
	return runTimeID;
}

const string Logger::GetFullPath()
{
	if(path.empty())
	{
		path = GetLogPath()+GetRunTimeDirectory()+"/";
	}
	return path;
}

const string Logger::GetMakeDirCommand()
{
	return string("mkdir ") + GetFullPath();
}

const string Logger::MakeComponentName(const string &COMP, const int ID)
{
	static stringstream ss;
	if(ID < 0)
		return COMP;
	ss.str("");
	ss<<COMP;
	ss<<'_';
	ss.width(2);
	ss.fill('0');
	ss<<ID;
	return ss.str();
}

const string Logger::MakeLogFileName(const string &SUBS, const string &COMP, const string &TYPE)
{
	return GetFullPath()+SUBS+'.'+COMP+'.'+TYPE;
}

LogService &Logger::GetInstance()
{
	if(service == nullptr)
		service = shared_ptr<LogService>(factory());
	return *service;
}

// Takes in Service, level, and state of a part of a robot and stores it in 'data'
const int Logger::LogState(const char * const SERV, const int LEV, const char * text) {
	GetInstance().logText()<<"["<<SERV<<"]["<<LEVEL_t::text[LEV]<<"] "<<text<<std::endl;
#ifndef DEBUG_MODE
	if(LEV != LEVEL_t::INFO)
#endif
		GetInstance().logStdout()<<"["<<SERV<<"] "<<text<<std::endl;
	return 0;
}

