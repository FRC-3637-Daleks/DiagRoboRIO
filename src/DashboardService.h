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

namespace DRR
{

using std::weak_ptr;

class DashboardService: public DiagnosticService
{
private:
	shared_ptr<DashboardPusher> pusher;
	string path;

public:
	DashboardService(const shared_ptr<DashboardPusher>& push, const string& p = string("")): pusher(push), path(p) {AddThread(pusher);};

public:
	virtual ~DashboardService() {};

public:
	void SetPusher(const shared_ptr<DashboardPusher>& push)
	{
		pusher = push;
		AddThread(pusher);
	}

	const shared_ptr<DashboardPusher> GetPusher() const {return pusher;};

public:
	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const weak_ptr<PollValue<T>>& poll, const int data=0)
	{
		auto pushRef = pusher->Add(path.empty()? key:(path+'/'+key), poll, data);
		return pushRef;
	}

	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const T *val, const int data=0)
	{
		auto pushRef = pusher->Add(path.empty()? key:(path+'/'+key), val, data);
		return pushRef;
	}
};

}



#endif /* SRC_DASHBOARDSERVICE_H_ */
