/*
 * MosCutieService.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Edward
 */

#ifndef SRC_DASHBOARDSERVICE_H_
#define SRC_DASHBOARDSERVICE_H_

#include <memory>

#include "DashboardPusher.h"
#include "DiagnosticService.h"

#include "TextLogObject.h"

namespace DRR
{

using std::weak_ptr;

class DashboardService: public DiagnosticService, private TextLogObject<DashboardService>
{
private:
	using TextLogObject<DashboardService>::LogText;

private:
	shared_ptr<DashboardPusher> pusher;
	string path;

public:
	DashboardService(const shared_ptr<DashboardPusher>& push, const string& p = string("")):
		TextLogObject<DashboardService>(p), pusher(push), path(p)
	{
		LogText(LEVEL_t::INIT)<<"Created for path: "<<path;
		if(!AddThread(pusher))
			LogText(LEVEL_t::ALERT)<<"Could not Add a new thread for this pusher ("<<path<<")";
	};

public:
	virtual ~DashboardService() {LogText("Destroying");};

public:
	const string GetPath() const {return path;};
	void SetPath(const string& p) {path = p;};

public:
	void SetPusher(const shared_ptr<DashboardPusher>& push)
	{
		LogText("Installing New Pusher");
		pusher = push;
		AddThread(pusher);
	}

	const shared_ptr<DashboardPusher> GetPusher() const {return pusher;};

public:
	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const weak_ptr<PollValue<T>>& poll, const int data=-1)
	{
		auto pushRef = pusher->Add(path.empty()? key:(path+'/'+key), poll, data);
		if(pushRef == nullptr)
		{
			auto save = LogText(LEVEL_t::INVALID)<<"Add(key: "<<key<<", poll: ";
			auto pollLock = poll.lock();
			if(pollLock == nullptr)
				save<<="NULL";
			else
				save<<="non-null";
			save<<", data: "<<data;
		}
		else
			LogText()<<"Added "<<key;
		return pushRef;
	}

	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const T *val, const int data=-1)
	{
		auto pushRef = pusher->Add(path.empty()? key:(path+'/'+key), val, data);
		if(pushRef == nullptr)
		{
			auto save = LogText(LEVEL_t::INVALID)<<"Add(key: "<<key<<", val: ";
			if(val == NULL)
				save<<="NULL";
			else
				save<<="non-null";
			save<<", data: "<<data;
		}
		else
			LogText()<<"Added "<<key;
		return pushRef;
	}
};

}



#endif /* SRC_DASHBOARDSERVICE_H_ */
