/*
 * LogService.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: edward
 */
#include <sys/stat.h>
#include "TextLogMQTT.h"
#include "LogService.h"

namespace DRR
{

LogPreferences LogService::preferences;
FileService LogService::file(nullptr);
DashboardService LogService::dashboard(nullptr);
TextLogService LogService::text;

const string LogService::MakeKey(const string& service, const string& component)
{
	return service+'/'+component;
}

const string LogService::MakeComponentNumber(const string& componenet, const int id)
{
	return componenet+'_'+DatumValue<int>(id).toString();
}

const string LogService::GetLogPath()
{
	static bool init = false;
	struct stat info;
	if(!init)
	{
		if(stat(preferences.log_home_path, &info) < 0)
		{
			mkdir(preferences.log_home_path,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}
	}
	init = true;
	return string(preferences.log_home_path);
}

const long LogService::GetRunTimeID()
{
	static long ret = -1;
	if(ret == -1)
	{
		using std::ios_base;
		std::fstream rtFile(GetLogPath()+"runtimeID", ios_base::in);
		rtFile>>ret;
		ret++;

		rtFile.close();
		rtFile.open(GetLogPath()+"runtimeID", ios_base::out | ios_base::trunc);
		rtFile<<ret;
	}

	return ret;
}

const string LogService::GetRunTimeDirectory()
{
	static string ret;
	if(ret.empty())
	{
		stringstream ss;
		ss.width(5);
		ss.fill('0');
		ss<<GetRunTimeID();
		ret = ss.str();
	}
	return ret;
}

const string LogService::GetRunTimePath()
{
	static string ret;
	if(ret.empty())
	{
		struct stat info;
		ret = GetLogPath()+GetRunTimeDirectory()+'/';
		if(stat(ret.c_str(), &info) < 0)
		{
			mkdir(ret.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}
	}

	return ret;
}

const int LogService::LogText(const string &service, const LEVEL_t &level, const string &message)
{
	if(text.GetThread() == nullptr)
	{
		if(preferences.text_log_filename != NULL)
			text.AddService(GetRunTimePath()+preferences.text_log_filename, preferences.log_period);
		if(preferences.text_dashboard_feed != NULL)
			text.AddService(TextLogMQTT::Create(preferences.text_dashboard_feed));
	}
	return text.Log(service, level, message);
}

const int LogService::Start()
{
	DiagnosticService::SetPollPeriod(preferences.poll_period);
	DiagnosticService::SetMonitorPeriod(preferences.monitor_period);
	if(!DiagnosticService::Init())
		return -1;
	return 0;
}

}


