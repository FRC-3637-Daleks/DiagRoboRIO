/*
 * Poller.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_POLLER_H_
#define SRC_POLLER_H_

#include "PushPullBase.h"

namespace DRR
{

/** Poller class is the interface for an object which retrieves a value from a known source
 * Base Class of ValuePoller
 */
class Poller: virtual public PushPullBase
{
public:
	virtual ~Poller() {};

private:
	virtual const int Do() override final {return Poll();};

public:
	virtual const int Poll()=0;	///< Poll function to be overriden by derived classes. Should fetch some sort of value.
};

}



#endif /* SRC_POLLER_H_ */
