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
	typedef shared_ptr<DatumValue<T>> DATA_t;

public:
	static const shared_ptr<DataBuffer<T>> Create()
	{
		return std::make_shared<DataBuffer<T> >();
	}

private:
	queue<T> buf;	///< Dataqueue
	DATA_t data;


protected:
	DataBuffer(): data(new DatumValue<T>), Buffer(data) {};
	DataBuffer(const DataBuffer& other)=delete;

public:
	virtual ~DataBuffer() {};

public:
	virtual const int Push() override
	{
		if(buf.empty())
			return 1;
		else
		{
			data->Set(buf.back());
			buf.pop();
			return 0;
		}
	}

	const typename PushValue<T>::FUNC_t GetPushFunctor() const
	{
		return std::bind(&queue<T>::push, &buf, std::placeholders::_1);
	}
};


}



#endif /* SRC_DATABUFFER_H_ */
