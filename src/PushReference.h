/*
 * PushReference.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_PUSHREFERENCE_H_
#define SRC_PUSHREFERENCE_H_

#include <functional>
#include <mutex>
#include <memory>

#include "PollValue.h"
#include "Pusher.h"

namespace DRR
{

using std::mutex;
using std::shared_ptr;
using std::weak_ptr;

template<typename T>
class PushReference: public Pusher
{
public:
	typedef std::function<void(T)> FUNC_t;

public:
	static const shared_ptr<PushReference<T> > Create(const T* val, const FUNC_t& fn)
	{
		return std::make_shared<PushReference<T> >(fn, ref);
	}

private:
	const T *ref;	///< Pointer to data which is to be pushed
	weak_ptr<PollValue<T> > refObj;	///< Weak pointer to the referring object
	FUNC_t pushFunc; ///< Function called by push
	mutex sem;		///< Mutex which keeps the pushFunc call from ever being called concurrently

protected:
	PushReference(const T *val, const FUNC_t fn): ref(val), refObj(nullptr), pushFunc(fn) {};
	PushReference(const weak_ptr<PollValue<T> > obj, const FUNC_t fn): ref(&refObj->getPrevious()), refObj(obj), pushFunc(fn) {};
	PushReference(const PushReference& other)=delete;

public:
	virtual ~PushReference() {};

public:
	virtual const int Push() override
	{
		if(refObj.expired() || refObj == nullptr || ref == NULL)	// Invalid states
			return -1;

		if(sem.try_lock())
		{
			try
			{
				pushFunc(*ref);
			}
			catch(...)
			{
				sem.unlock();
				return -1;
			}

			sem.unlock();
		}

		return 0;
	}

};


}



#endif /* SRC_PUSHREFERENCE_H_ */
