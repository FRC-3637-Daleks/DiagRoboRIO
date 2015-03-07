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

namespace DRR
{

using std::shared_ptr;
using std::string;

class LEVEL_t {
public:
	enum {EMER=0, ALERT, CRIT, ERR, WARN, NOTICE, INFO, DEBUG, NUM_LEVELS} value;
	static const char* text[NUM_LEVELS];

	LEVEL_t(const int v=INFO): value(v) {};
	LEVEL_t(const LEVEL_t& other)=default;
	constexpr operator const int () const {return value;};
};

class TextLog
{
private:
	static shared_ptr<TextLog> handler;

public:
	static void SetHandler(const shared_ptr<TextLog> &handle) {handler = handle;};
	static const int Log(const string &service, const LEVEL_t level, const string& message);

public:
	TextLog() {};
	virtual ~TextLog() {};

protected:
	virtual const int LogInternal(const string& message);
};


}



#endif /* SRC_TEXTLOG_H_ */
