/*
 * Loggable.h
 *
 *  Created on: Jan 17, 2015
 *      Author: edward
 */

#ifndef SRC_LOGGABLE_H_
#define SRC_LOGGABLE_H_

#include <functional>
#include <string>
#include <vector>
#include <fstream>

#include "WPILib.h"

#include "Defaults.h"

using std::string;
using std::ostream;
using std::vector;

/** Base class for Loggable objects.
 * Derived objects should accept a bound function and store its return value in a buffer
 */
class Loggable
{
public:
	typedef enum {CONTINUE, KILL} FAIL_COMMAND;

public:
	Loggable() {};
	virtual ~Loggable() {};

public:
	/// Overriden function should record data in buffer or log it
	virtual const int Log()=0;

	/// If the Logger buffers, should be called at the end to flush buffered values
    virtual const int logCurrent()=0;
};

/// Default implementation
inline const int Loggable::logCurrent()
{
    return Log();
}

#endif /* SRC_LOGGABLE_H_ */
