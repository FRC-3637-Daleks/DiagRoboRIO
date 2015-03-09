/*
 * LogService.h
 *
 *  Created on: Mar 5, 2015
 *      Author: edward
 */

#ifndef SRC_LOGSERVICE_H_
#define SRC_LOGSERVICE_H_

#include <functional>
#include "DashboardService.h"
#include "FileService.h"
#include "TextLogService.h"
#include "LogPreferences.h"

namespace DRR
{

class LogService
{
private:
	static LogPreferences preferences;
	static FileService file;
	static DashboardService dashboard;
	static TextLogService text;

public:
	static LogPreferences& Preferences() {return preferences;};

public:
	static const string AddID(const string& component, const int id);
	static const string MakeKey(const string& service, const string& component);

public:
	static const long GetRunTimeID();
	static const string GetLogPath();
	static const string GetRunTimeDirectory();
	static const string GetRunTimePath();

public:
	template<typename T>
	static const int AddLog(const string &service, const string &component, const std::function<T(void)> fn, const int dashData=-1);

	template<typename T>
	static const int AddLog(const string &service, const string &componenet, T (* const fn)(), const int dashData=-1);

	template<typename T, class SERVICE>
	static const int AddLog(const string& component, T (SERVICE::*fn)(), SERVICE * const obj, const int dashData=-1);

	static const int LogText(const string& service, const string& message, const LEVEL_t &level=LEVEL_t::INFO);

	static const int Start();
};

template<typename T>
inline const int LogService::AddLog(const string &service, const string &component, const std::function<T(void)> fn, const int dashData)
{
	if(file.GetMatrix() == nullptr)
		file.SetMatrix(preferences.file_fact(GetRunTimePath()+preferences.value_log_filename, preferences.log_period));
	auto poll = file.Add(MakeKey(service, component), fn);
	if(!poll)
		return -1;
	if(dashData >= 0)
	{
		if(dashboard.GetPusher() == nullptr)
			dashboard.SetPusher(preferences.dash_fact(preferences.dash_period));
		dashboard.Add(MakeKey(service, component), weak_ptr<PollValue<T>>(poll), dashData);
	}

	return 0;
}

template<typename T>
inline const int LogService::AddLog(const string &service, const string& component, T (* const fn)(), const int dashData)
{
	return AddLog<T>(service, component, std::function<T()>(fn), dashData);
}

template<typename T, class SERVICE>
inline const int LogService::AddLog(const string &component, T (SERVICE::*fn)(), SERVICE * const obj, const int dashData)
{
	return AddLog<T>(NameOf<SERVICE>::name(), component, std::bind(fn, obj), dashData);
}

}



#endif /* SRC_LOGSERVICE_H_ */
