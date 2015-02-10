/*
 * Buffer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_BUFFER_H_
#define SRC_BUFFER_H_

#include <memory>

#include "Pusher.h"
#include "Datum.h"

namespace DRR
{

using std::shared_ptr;

/** A Buffer is a generic Pusher which pops Data from a structure somewhere and pushes a pointer to each Datum to its pusher function
 *
 */

class Buffer: public PushValue<shared_ptr<const Datum>>
{
public:
	typedef PushValue<shared_ptr<const Datum>> PARENT_t;
	typedef typename PARENT_t::FUNC_t FUNC_t;

protected:	/// Protected in order to ensure that the Buffer is made from an inherited constructor function
	Buffer(const FUNC_t& fn): PushValue<shared_ptr<Datum>>(fn) {};
	Buffer(const Buffer& other)=delete;

public:
	virtual ~Buffer() {};

public:
	virtual const shared_ptr<Datum> Pop()=0;			///< To be overriden by the derived class where the actual Buffer is defined
	virtual const shared_ptr<Datum> GetValue() override final {return Pop();};	///< Calls Pop
};

}



#endif /* SRC_BUFFER_H_ */
