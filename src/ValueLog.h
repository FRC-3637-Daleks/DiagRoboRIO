/*
 * ValueLog.h
 *
 *  Created on: Feb 4, 2015
 *      Author: Edward
 */

#ifndef SRC_VALUELOG_H_
#define SRC_VALUELOG_H_

#include <mutex>
#include <climits>
#include "Loggable.h"


template<typename DATA_TYPE>
class ValueLog: public Loggable
{
public:
	static Loggable::FAIL_COMMAND continueAnyway(const DATA_TYPE v) {return Loggable::CONTINUE;};

public:
	typedef std::function<DATA_TYPE(void)> FUNC_t;
	typedef std::function<Loggable::FAIL_COMMAND(DATA_TYPE)> LOG_EXTENSION_t;

private:
	FUNC_t fn;		///< Function called by Log which returns the value being logged.
	LOG_EXTENSION_t check;					///< Is called at every Log, defined by client
	DATA_TYPE prev;		///< Previous value called in Log
	std::mutex mutex;	///< Protects fn or check from being called by more than one thread

protected:
	const DATA_TYPE getPrev() const {return prev;};


public:
	/** Constructs from a function object, and extension function object
	 */
	ValueLog(const FUNC_t &f, LOG_EXTENSION_t c=continueAnyway):
		fn(f), check(c) {};
	virtual ~ValueLog() {};

public:
	/// Pushes a value to buf and logs current buffer if full capacity
	const int Log() override
	{
		if(mutex.try_lock())
		{
			prev = fn();
			if(check(prev) == KILL)
			{
				mutex.unlock();
				return -1;
			}
			mutex.unlock();
			return 0;
		}

		return 1;
	}

	const int logCurrent() override {return Loggable::logCurrent();};

public:
	FUNC_t makeExtension() const
	{
		return std::bind(&ValueLog<DATA_TYPE>::getPrev, this);
	}
};



#endif /* SRC_VALUELOG_H_ */
