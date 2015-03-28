/*
 * StreamHandle.h
 *
 *  Created on: Mar 9, 2015
 *      Author: 3637-DS-0
 */

#ifndef SRC_STREAMHANDLE_H_
#define SRC_STREAMHANDLE_H_

#include <sstream>
#include <string>

#include "DiagnosticService.h"

namespace DRR
{

using std::ostringstream;
using std::ostream;
using std::string;

class TextLog;


class LEVEL_t {
public:
	enum {EMER=0, ALERT, CRIT, ERR, WARN, NOTICE, INFO, DEBUG, NUM_LEVELS};
	static const char* text[NUM_LEVELS];

private:
	int value;

public:
	LEVEL_t(const int v=INFO): value(v) {};
	LEVEL_t(const LEVEL_t& other)=default;
	operator const int () const {return value;};
};

class StreamHandle
{
public:
	friend TextLog;

private:
	string service, instance;
	LEVEL_t level;
	ostringstream buf;
	bool pushed;

private:
	StreamHandle(const string &serv, const string &inst, const LEVEL_t lev): service(serv), instance(inst), level(lev), pushed(false) {};

public:
	StreamHandle(StreamHandle &&other);

public:
	virtual ~StreamHandle()
	{
		if(!pushed)
			Push();
	}

public:
	void Push();

	template<typename T>
	StreamHandle operator<<(const T& val)
	{
		if(pushed)
			return std::move(*this);
		buf<<val;
		return std::move(*this);
	}

	template<typename T>
	StreamHandle& operator<<= (const T& val)
	{
		return *this = *this<<val;
	}

	StreamHandle& operator= (StreamHandle && other)
	{
		if(this == &other)
			return *this;
		service = other.service;
		instance = other.instance;
		level = other.level;
		buf.str("");
		buf << other.buf.str();
		pushed = other.pushed;
		other.buf.str("");
		return *this;
	}

};


}



#endif /* SRC_STREAMHANDLE_H_ */
