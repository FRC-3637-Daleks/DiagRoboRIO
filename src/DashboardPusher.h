/*
 * DashboardPusher.h
 *
 *  Created on: Mar 5, 2015
 *      Author: edward
 */

#ifndef SRC_DASHBOARDPUSHER_H_
#define SRC_DASHBOARDPUSHER_H_

#include <memory>

#include "MosCutie.h"
#include "PollValue.h"
#include "PushReference.h"
#include "FramePusher.h"

namespace DRR
{

using std::weak_ptr;

class DashboardPusher: public ThreadList
{
protected:
	DashboardPusher(const MILLISECONDS p): ThreadList(p) {};
	DashboardPusher(DashboardPusher&& other): ThreadList(std::move(other)) {};

public:
	virtual ~DashboardPusher() {};

private:
	virtual void DoPublish(const Frame::KEY_t& key, const string& value, const int data=0)=0;

public:

	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const weak_ptr<PollValue<T>> &poll, const int data=0)
	{
		auto pusher(PushReference<T>::Create(poll, [this, key, data](const T t) {
			return DoPublish(key, DatumValue<T>(t).toString(), data);
		}));

		push_back(pusher);
		return pusher;
	};

	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const T *val, const int data=0)
	{
		auto pusher(PushReference<T>::Create(val, [this, key, data](const T t) {
			return DoPublish(key, DatumValue<T>(t).toString(), data);
		}));

		push_back(pusher);
		return pusher;
	}
};

}

#endif /* SRC_DASHBOARDPUSHER_H_ */
