/*
 * LogObject.h
 *
 *  Created on: Mar 8, 2015
 *      Author: 3637-DS-1
 */

#ifndef SRC_LOGOBJECT_H_
#define SRC_LOGOBJECT_H_

#include "LogService.h"

namespace DRR
{

template<class SERVICE>
class LogObject
{
private:
	string name;
	SERVICE *self;

protected:
	LogObject(): name(NameOf<SERVICE>::name()), self(dynamic_cast<SERVICE*>(this)) {};
	LogObject(const int ID): name(LogService::AddID(NameOf<SERVICE>::name(), ID)), self(dynamic_cast<SERVICE>(this)) {};

public:
	LogObject(SERVICE * const obj): name(NameOf<SERVICE>::name()), self(obj) {};
	LogObject(SERVICE * const obj, const int ID): name(LogService::AddID(NameOf<SERVICE>::name(), ID)), self(obj) {};

public:
	virtual ~LogObject() {};

public:
	template<typename T>
	const int AddLog(const string &component, T (SERVICE::*fn)(), const int dashData=-1)
	{
		return LogService::AddLog(component, fn, self, dashData);
	}

	template<typename T, class... Args>
	const int AddLog(const string &component, const std::function<T(SERVICE*, Args...)> &fn, Args... args, const int dashData=-1)
	{
		return LogService::AddLog(name, component, std::bind(fn, self, args...), dashData);
	}

	const int LogText(const string& message, const LEVEL_t &level=LEVEL_t::INFO)
	{
		return LogService::LogText(name, message, level);
	}

};




}



#endif /* SRC_LOGOBJECT_H_ */
