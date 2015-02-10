/*
 * DataBuffer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_DATABUFFER_H_
#define SRC_DATABUFFER_H_

#include <queue>

#include "Buffer.h"
#include "DatumValue.h"
#include "PushValue.h"

namespace DRR
{

using std::queue;

/** DataBuffer is an extension of Buffer which defines a buffer as a queue.
 */
template<typename T>
class DataBuffer: public Buffer
{
public:
	static const shared_ptr<DataBuffer<T> > Create(const FUNC_t& fn)
	{
		return std::make_shared<DataBuffer<T> >(fn);
	}

private:
	queue<T> buf;	///< Dataqueue

protected:
	DataBuffer(const FUNC_t& fn): Buffer(fn) {};
	DataBuffer(const DataBuffer& other)=delete;

public:
	virtual ~DataBuffer() {};

public:
	virtual const DATA_t Pop() override
	{
		if(buf.empty())
			return nullptr;
		else
		{
			T value = buf.back();
			buf.pop();
			return std::make_shared<DatumValue<T>>(value);
		}
	}

	const typename PushValue<T>::FUNC_t GetPushFunctor() const
	{
		return std::bind(&queue<T>::push, &buf, std::placeholders::_1);
	}
};


}



#endif /* SRC_DATABUFFER_H_ */
