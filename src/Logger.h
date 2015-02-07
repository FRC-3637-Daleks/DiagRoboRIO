// Just a test comment

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdlib.h>
#include <cctype>
#include <time.h>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <iostream>

#include "LogPreferences.h"
#include "Defaults.h"
#include "LogServices.h"
#include "FileLogger.h"
#include "DataService.h"
#include "mosquitto.h"

using std::shared_ptr;

class LEVEL_t {
public:
	enum {EMER=0, ALERT, CRIT, ERR, WARN, NOTICE, INFO, DEBUG};
	static const char* text[];
};


class Logger {
private:
	static shared_ptr<LogService> service;
	static std::function<shared_ptr<LogService>()> factory;
	static string path;
	static LogPreferences preferences;

public:
	static const LogPreferences& GetPreferences() {return preferences;};
	static void SetPreferences(const LogPreferences& prefs) {preferences = prefs;};

public:
	static const string GetLogPath();
	static const string GetRunTimeDirectory();
	static const string GetMakeDirCommand();
	static const string GetFullPath();

	/// Generates string of form COMP_ID
	static const string MakeComponentName(const string &COMP, const int ID=-1);

	/// Generates string of form SUBS.COMP.TYPE
	static const string MakeLogFileName(const string &SUBS, const string &COMP, const string &TYPE);

private:
	static LogService &GetInstance();

public:
	static void StartLogging() {GetInstance().startLogging();};


	template<class DATA_TYPE>
	static typename ValueLog<DATA_TYPE>::FUNC_t MakeLogValue(const char * SUBS, const char * COMP, DATA_TYPE (*fn)(), const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway) {
		return MakeLogValue(SUBS, COMP, std::function<DATA_TYPE(void)>(fn), ext);
	}

	template<class DATA_TYPE>
	static typename ValueLog<DATA_TYPE>::FUNC_t MakeLogValue(const char * const SUBS, const char * const COMP, std::function<DATA_TYPE(void)> fn, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway) {
		return GetInstance().addLog(fn, MakeLogFileName(string(SUBS), string(COMP), string(typeid(DATA_TYPE).name())), ext);
	}

	template<typename DATA_TYPE, class SUB_TYPE>
	static typename ValueLog<DATA_TYPE>::FUNC_t MakeLogValue(const char * const SUBS, const char * const COMP, SUB_TYPE *obj, DATA_TYPE (SUB_TYPE::*fn)(), const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway) {
		return GetInstance().addLog(obj, fn, MakeLogFileName(string(SUBS), string(COMP), string(typeid(DATA_TYPE).name())), ext);
	}

public:
	/// This should be called before any other function of Logger is called.
	static void SetFactoryFunction(std::function<shared_ptr<LogService>()> fact) {factory = fact;};

public:
	static const int LogState(const char * const SERV, const int LEV, const string &text);
	static const int LogState(const char * const SERV, const int LEV, const char * const text) {return LogState(SERV, LEV, string(text));}

	template<typename DATA_TYPE, class SUB_TYPE>
	static typename ValueLog<DATA_TYPE>::FUNC_t MakeLogValue(const char * const COMP, SUB_TYPE *obj, DATA_TYPE (SUB_TYPE::* fn)(), const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway)
	{
		string str(typeid(SUB_TYPE).name());
		//for(auto i = str.begin(); i != str.end(); i++) *i = toupper(*i);   // Makes name upper case
		return MakeLogValue(str.substr(2).c_str(), COMP, obj, fn, ext);
	}

	/// The subsystem used must have a static function GetComponenentName which returns a c-string based on a id
	template<typename DATA_TYPE, class SUB_TYPE>
	static typename ValueLog<DATA_TYPE>::FUNC_t MakeLogValue(const int COMP, SUB_TYPE *obj, DATA_TYPE (SUB_TYPE::* fn)(), const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway)
	{
		return MakeLogValue(SUB_TYPE::GetComponentName(COMP), obj, fn, ext);
	}

private:
	string name;

protected:
	Logger(): name(typeid(this).name()) {};

	const int LogState(const int LEV, const string &text) {return LogState(name.c_str(), LEV, text);};

	template<typename DATA_TYPE>
	typename ValueLog<DATA_TYPE>::FUNC_t MakeLogValue(const char * const COMP, std::function<DATA_TYPE(void)> fn, const typename ValueLog<DATA_TYPE>::LOG_EXTENSION_t ext=ValueLog<DATA_TYPE>::continueAnyway)
	{
		return MakeLogValue(name.c_str(), COMP, fn, ext);
	}

};

#endif /* LOGGER_H_ */
