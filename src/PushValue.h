/*
 * PushValue.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_PUSHVALUE_H_
#define SRC_PUSHVALUE_H_

#include <functional>
#include <mutex>
#include <memory>

#include "Pusher.h"

namespace DRR
{

using std::mutex;
using std::shared_ptr;


template<typename T>
class PushValue: public Pusher
{
public:
	typedef std::function<void(T)> FUNC_t;

private:
	FUNC_t pushFunc; ///< Function called by push
	mutex sem;		///< Mutex which keeps the pushFunc call from ever being called concurrently

protected:
	PushValue(const FUNC_t fn): pushFunc(fn) {};
	PushValue(const PushValue& other)=delete;

public:
	virtual ~PushValue() {};

public:
	virtual const T GetValue()=0;
	virtual const int Push() override
	{
		if(sem.try_lock())
		{
			try
			{
				pushFunc(GetValue());
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



#endif /* SRC_PUSHVALUE_H_ */
