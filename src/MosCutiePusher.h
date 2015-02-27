/*
 * MosCutiePusher.h
 *
 *  Created on: Feb 27, 2015
 *      Author: Edward
 */

#ifndef SRC_MOSCUTIEPUSHER_H_
#define SRC_MOSCUTIEPUSHER_H_

#include <memory>

#include "MosCutie.h"
#include "PollValue.h"
#include "PushReference.h"
#include "FramePusher.h"

namespace DRR
{

using std::weak_ptr;

class MosCutiePusher: public ThreadList
{
public:
	static const shared_ptr<MosCutiePusher> Create(const MILLISECONDS p)
	{
		return shared_ptr<MosCutiePusher>(new MosCutiePusher(p));
	}

protected:
	MosCutiePusher(const MILLISECONDS p): ThreadList(p) {};
	MosCutiePusher(MosCutiePusher&& other): ThreadList(std::move(other)) {};

public:
	virtual ~MosCutiePusher() {};

public:
	template<typename T>
	const PushReference<T> Add(const Frame::KEY_t key, const weak_ptr<PollValue<T>> &poll, const bool persist=false)
	{
		auto pusher(PushReference<T>::Create(poll, [key, persist](const T t) {
			return MosCutie::Publish(key, DatumValue<T>(t).toString(), persist);
		}));

		push_back(pusher);
		return pusher;
	};

	template<typename T>
	const PushReference<T> Add(const Frame::KEY_t key, const T *val, const bool persist=false)
	{
		auto pusher(PushReference<T>::Create(val, [key, persist](const T t) {
			return MosCutie::Publish(key, DatumValue<T>(t).toString(), persist);
		}));

		push_back(pusher);
		return pusher;
	}
};

}



#endif /* SRC_MOSCUTIEPUSHER_H_ */
