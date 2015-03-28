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
#include <vector>

#include "PollValue.h"
#include "StreamHandle.h"

namespace DRR
{

using std::shared_ptr;
using std::string;
using std::vector;

class TextLog
{
private:
	static vector<shared_ptr<TextLog>> listeners;
	static shared_ptr<PollValue<long long>> stamp;

public:
	static void AddListener(const shared_ptr<TextLog> &handle) {listeners.push_back(handle);};
	static void SetFrameStamp(const shared_ptr<PollValue<long long>> stmp) {stamp = stmp;};
	static const int Log(const string &service, const string &instance, const string& message, const LEVEL_t level=LEVEL_t::INFO);
	static StreamHandle Log(const string &service, const string &instance, const LEVEL_t level=LEVEL_t::INFO);

protected:
	TextLog() {};

public:
	virtual ~TextLog() {};

protected:
	virtual const int LogInternal(const string& message);
};


}



#endif /* SRC_TEXTLOG_H_ */
