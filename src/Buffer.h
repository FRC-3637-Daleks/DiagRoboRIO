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

class Buffer: public Pusher
{
public:
	typedef shared_ptr<Datum> DATA_t;

private:
	DATA_t datumRef;

protected:	/// Protected in order to ensure that the Buffer is made from an inherited constructor function
	Buffer(const DATA_t& d): datumRef(d) {};
	Buffer(const Buffer& other)=delete;

public:
	const DATA_t Get() const {return datumRef;};

public:
	virtual ~Buffer() {};
};

}



#endif /* SRC_BUFFER_H_ */
