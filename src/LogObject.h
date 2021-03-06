/*
 * LogObject.h
 *
 *  Created on: Mar 8, 2015
 *      Author: 3637-DS-1
 */

#ifndef SRC_LOGOBJECT_H_
#define SRC_LOGOBJECT_H_

#include "TextLogObject.h"
#include "LogService.h"

namespace DRR
{

template<class SERVICE>
class LogObject: public TextLogObject<SERVICE>
{
protected:
	LogObject() {InitTextLogService();};	///< nullptr Signifies that child class derives the object
	LogObject(const string &inst): TextLogObject<SERVICE>(inst) {InitTextLogService();};

public:
	LogObject(SERVICE * const obj): TextLogObject<SERVICE>(obj) {InitTextLogService();};
	LogObject(SERVICE * const obj, const string &inst): TextLogObject<SERVICE>(obj, inst) {InitTextLogService();};
	LogObject(LogObject&& other): TextLogObject<SERVICE>(std::move(other)) {};

public:
	virtual ~LogObject() {};

private:
	static void InitTextLogService()
	{
		LogService::InitTextLogging();
	}

public:
	template<typename T>
	static const int StaticAddLog(const string &component, T (*fn)(), const int dashData=-1)
	{
		return LogService::AddLog(LogObjectBase<SERVICE>::GetName(), component, fn, dashData);
	}

	template<typename T>
	static const int StaticAddLog(const string &component, const std::function<T()> &fn, const int dashData=-1)
	{
		return LogService::AddBindedLog<T>(LogObjectBase<SERVICE>::GetName(), component, fn, dashData);
	}

	template<typename T>
	const int AddLog(const string &component, T (SERVICE::*fn)(), const int dashData=-1)
	{
		return LogService::AddLog<T>(LogService::MakeKey(this->GetInstanceName(), component), fn, this->GetSelf(), dashData);
	}

	template<typename T>
	const int AddLog(const string &component, T (SERVICE::*fn)() const, const int dashData=-1)
	{
		return StaticAddLog<T>(component, std::bind(fn, this->GetSelf()), dashData);
	}

	/*
	template<typename T, class... Args>
	const int AddLog(const string &component, const std::function<T(SERVICE*, Args...)> &fn, Args... args, const int dashData=-1)
	{
		return LogService::AddLog(name, component, std::bind(fn, self, args...), dashData);
	}
	*/

	template<typename T>
	const int AddLog(const string &component, const std::function<T()> &fn, const int dashData=-1)
	{
		return LogService::AddBindedLog<T>(this->GetName(), LogService::MakeKey(this->GetInstanceName(), component), fn, dashData);
	}


};

}

#endif /* SRC_LOGOBJECT_H_ */
