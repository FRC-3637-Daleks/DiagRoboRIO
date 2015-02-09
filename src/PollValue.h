/*
 * PollValue.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_POLLVALUE_H_
#define SRC_POLLVALUE_H_

#include <functional>
#include <mutex>
#include <memory>
#include "Poller.h"

namespace DRR
{

using std::mutex;
using std::shared_ptr;

template<typename T>
class PollValue: public Poller
{
public:
	typedef std::function<T()> FUNC_t;

public:
	/// PollValues most only come in the form of dynamically shared objects
	static const shared_ptr<PollValue<T> > Create(const FUNC_t& fn)
	{
		return std::make_shared<PollValue<T> >(fn);
	}

private:
	T previous;	///< Most recent call of Poll's return of pollFunc
	FUNC_t pollFunc;	/// The function called by Poll
	mutex sem;	/// Mutex which locks the pollFunc call from ever being called concurrently

protected:
	PollValue(const FUNC_t& fn): pollFunc(fn) {};
	PollValue(const PollValue<T>& other)=delete;

public:
	virtual ~PollValue() {};

public:
	/// Returns current value
	const T getPreviousValue() const {return previous;};

	/// Returns reference to current value
	const T& getPrevious() const {return previous;};

	/// Poll locks the pollFunc call in a semaphore and stores the result of pollFunc in previous
	virtual const int Poll() override
	{
		if(sem.try_lock())
		{
			try
			{
				previous = pollFunc();
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



#endif /* SRC_POLLVALUE_H_ */
