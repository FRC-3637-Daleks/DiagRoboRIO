/*
 * Poller.h
 *
 *  Created on: Feb 9, 2015
 *      Author: root
 */

#ifndef SRC_POLLER_H_
#define SRC_POLLER_H_

namespace DRR
{

/** Poller class is the interface for an object which retrieves a value from a known source
 * Base Class of ValuePoller
 */
class Poller
{
public:
	virtual const int Poll()=0;	///< Poll function to be overriden by derived classes. Should fetch some sort of value.
};

}



#endif /* SRC_POLLER_H_ */
