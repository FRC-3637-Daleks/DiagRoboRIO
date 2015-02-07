#include <sys/stat.h>
#include "Logger.h"

/********* STATIC LOGGER DATA MEMBERS *************/

shared_ptr<LogService> Logger::service = nullptr;
string Logger::path;
LogPreferences Logger::preferences;

std::function<shared_ptr<LogService>()> Logger::factory = []()
{
	return FileLogger::Create(Logger::GetFullPath()+Logger::GetPreferences().text_log_filename,
							Logger::GetMakeDirCommand(),
							Logger::GetPreferences().log_period,
							Logger::GetPreferences().n_buffer_frames);
};

/********** STATIC LOGGER THREAD DATA ***************/
int Logger::threadState(Logger::THREAD_STATE_INIT);
std::thread Logger::monitorThread(&Logger::MonitorThread);


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
		service = factory();
	return *service;
}

void Logger::RestartService()
{
	if(service == nullptr)
	{
		GetInstance();
		return;
	}

	service = std::dynamic_pointer_cast<LogService>(service->emergencyClone());
	if(GetThreadState() == THREAD_STATE_RUNNING)
		GetInstance().startLogging();
}

/*********** Monitor Thread **************/
void Logger::MonitorThread()
{
	while(GetThreadState() == THREAD_STATE_INIT);   // Awaiting start signal

	GetInstance().startLogging();

	int failed = 0;

	while(GetThreadState() == THREAD_STATE_RUNNING && failed >= 0)
	{
		if(GetInstance().exceedsTimeout())
		{
			int iter = GetInstance().getCurrentIteration();	// Fail Point
			stringstream ss;
			ss<<"Log of object #"<<iter<<" exceeded timeout";
			LogState("Logger", LEVEL_t::CRIT, ss.str());
			LogState("Logger", LEVEL_t::ALERT, string("Detaching Log Service thread"));
			RestartService();
			LogState("Logger", LEVEL_t::INFO, string("New Log Service thread started"));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(preferences.monitor_period));
	}
}


// Takes in Service, level, and state of a part of a robot and stores it in 'data'
const int Logger::LogState(const char * const SERV, const int LEV, const string& text) {
	GetInstance().logText()<<"["<<SERV<<"]["<<LEVEL_t::text[LEV]<<"] "<<text<<std::endl;
#ifndef DEBUG_MODE
	if(LEV != LEVEL_t::INFO)
#endif
		GetInstance().logStdout()<<"["<<SERV<<"] "<<text<<std::endl;
	return 0;
}

