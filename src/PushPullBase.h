/*
 * PushPullBase.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_PUSHPULLBASE_H_
#define SRC_PUSHPULLBASE_H_

namespace DRR
{

enum {SUCCESS=0, FAILURE=-1};

/// Base class interface for Poller and Pusher
class PushPullBase
{
public:
	virtual ~PushPullBase() {};

public:
	virtual const int Do()=0;
};

}



#endif /* SRC_PUSHPULLBASE_H_ */
