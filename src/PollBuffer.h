/*
 * PollBuffer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_POLLBUFFER_H_
#define SRC_POLLBUFFER_H_

#include "PollValue.h"
#include "PushReference.h"
#include "DataBuffer.h"

namespace DRR
{

template<typename T>
class BufferPoll: public PollValue<T>, public PushReference<T>
{
public:
	typedef typename PollValue<T>::FUNC_t POLL_t;
	typedef typename PushReference<T>::FUNC_t PUSH_t;

public:
	static const shared_ptr<BufferPoll> Create(const POLL_t& poll, const PUSH_t& push)
	{
		return std::make_shared<BufferPoll>(poll, push);
	}

	static const shared_ptr<BufferPoll> Create(const POLL_t& poll, const DataBuffer<T> &db)
	{
		return Create(poll, db.GetPushFunctor());
	}

	static const shared_ptr<BufferPoll> Create(const POLL_t& poll, const shared_ptr<const DataBuffer<T>> db)
	{
		return Create(poll, *db);
	}

protected:
	BufferPoll(const POLL_t& poll, const PUSH_t& push): PollValue<T>(poll), PushReference<T>(&getPrevious(), push) {};
	BufferPoll(const POLL_t& poll, const DataBuffer<T>& db): BufferPoll(poll, db.GetPushFunctor()) {};
	BufferPoll(const POLL_t& poll, const shared_ptr<const DataBuffer<T>> db): BufferPoll(poll, *db) {};
	BufferPoll(const BufferPoll& other)=delete;

public:
	virtual ~BufferPoll() {};

public:
	/// Override of virtual Do functions defined in Pusher and Poller
	virtual const int Do() override
	{
		int ret = 0;
		if((ret |= Poll()) < 0)
			return ret;
		return ret | Push();
	}
};

}



#endif /* SRC_POLLBUFFER_H_ */
