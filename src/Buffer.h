/*
 * Buffer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_BUFFER_H_
#define SRC_BUFFER_H_

#include <memory>

#include "PushValue.h"
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
	typedef shared_ptr<const Datum> DATA_t;
	typedef PushValue<DATA_t> PARENT_t;
	typedef typename PARENT_t::FUNC_t FUNC_t;

protected:	/// Protected in order to ensure that the Buffer is made from an inherited constructor function
	Buffer(const FUNC_t& fn): PARENT_t(fn) {};
	Buffer(const Buffer& other)=delete;

public:
	virtual ~Buffer() {};

public:
	virtual const DATA_t Pop()=0;			///< To be overriden by the derived class where the actual Buffer is defined
	virtual const DATA_t GetValue() override final {return Pop();};	///< Calls Pop
};

}



#endif /* SRC_BUFFER_H_ */
