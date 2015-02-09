/*
 * Pusher.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_PUSHER_H_
#define SRC_PUSHER_H_

namespace DRR
{


/** Pusher class is the interface for an object which sends a value to a known source
 * Base Class of ReferencePusher
 */
class Pusher
{
public:
	virtual ~Pusher() {};

public:
	virtual const int Push()=0;	///< Push function to be overriden by derived classes. Should send some sort of value.
};

}



#endif /* SRC_PUSHER_H_ */
