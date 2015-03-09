/*
 * TextLogService.h
 *
 *  Created on: Mar 7, 2015
 *      Author: 3637-DS-1
 */

#ifndef SRC_TEXTLOGSERVICE_H_
#define SRC_TEXTLOGSERVICE_H_

#include "DiagnosticService.h"
#include "Pusher.h"
#include "TextLog.h"

namespace DRR
{

class TextLogService: private DiagnosticService
{
private:
	ThreadList::TL_HANDLER textThread;

public:
	TextLogService();
	TextLogService(const shared_ptr<TextLog> &toInstall, const shared_ptr<Pusher> &toPush=nullptr, const MILLISECONDS mils=0.0);
	TextLogService(const string& file, const MILLISECONDS mils);
	TextLogService(TextLogService && other): textThread(std::move(other.textThread)) {};
	virtual ~TextLogService() {};

public:
	void AddService(const shared_ptr<TextLog> &toInstall, const shared_ptr<Pusher> &toPush=nullptr, const MILLISECONDS mils=0.0);
	void AddService(const string& file, const MILLISECONDS mils);

	const ThreadList::TL_HANDLER GetThread() const {return textThread;};

public:
	const int Log(const string &service, const string& message, const LEVEL_t level=LEVEL_t::INFO);
};




}



#endif /* SRC_TEXTLOGSERVICE_H_ */
