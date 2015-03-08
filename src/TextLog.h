/*
 * TextLog.h
 *
 *  Created on: Mar 6, 2015
 *      Author: edward
 */

#ifndef SRC_TEXTLOG_H_
#define SRC_TEXTLOG_H_

#include <memory>
#include <string>

#include "PollValue.h"

namespace DRR
{

using std::shared_ptr;
using std::string;

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

class TextLog
{
private:
	static shared_ptr<TextLog> handler;
	static shared_ptr<PollValue<long long>> stamp;

public:
	static void SetHandler(const shared_ptr<TextLog> &handle) {handler = handle;};
	static void SetFrameStamp(const shared_ptr<PollValue<long long>> stmp) {stamp = stmp;};
	static const int Log(const string &service, const LEVEL_t level, const string& message);

public:
	TextLog() {};
	virtual ~TextLog() {};

protected:
	virtual const int LogInternal(const string& message);
};


}



#endif /* SRC_TEXTLOG_H_ */
