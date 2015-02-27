/*
 * MosCutieService.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Edward
 */

#ifndef SRC_MOSCUTIESERVICE_H_
#define SRC_MOSCUTIESERVICE_H_

#include <memory>

#include "MosCutiePusher.h"
#include "DiagnosticService.h"

namespace DRR
{

using std::weak_ptr;

class MosCutieService: public DiagnosticService
{
private:
	shared_ptr<MosCutiePusher> pusher;
	string path;

public:
	MosCutieService(const string& p, const MILLISECONDS t): pusher(MosCutiePusher::Create(t)), path(p) {AddThread(pusher);};
	MosCutieService(const MILLISECONDS t): MosCutieService("", t) {};

public:
	virtual ~MosCutieService() {};

public:
	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const weak_ptr<PollValue<T>>& poll, const bool persist=false)
	{
		auto pushRef = pusher->Add(path+'/'+key, poll, persist);
		return pushRef;
	}

	template<typename T>
	const shared_ptr<PushReference<T>> Add(const Frame::KEY_t key, const T *val, const bool persist=false)
	{
		auto pushRef = pusher->Add(path+'/'+key, val, persist);
		return pushRef;
	}
};




}



#endif /* SRC_MOSCUTIESERVICE_H_ */
