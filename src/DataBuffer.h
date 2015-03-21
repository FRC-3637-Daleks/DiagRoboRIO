/*
 * DataBuffer.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_DATABUFFER_H_
#define SRC_DATABUFFER_H_

#include <iostream>
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
		return shared_ptr<DataBuffer<T>>(new DataBuffer());
	}

private:
	DATA_t data;
	queue<T> buf;	///< Dataqueue


protected:
	DataBuffer(): Buffer(nullptr), data(shared_ptr<DatumValue<T>>(new DatumValue<T>)) {Set(data);};
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
			data->Set(buf.front());
			buf.pop();
			return 0;
		}
	}

	const typename PushValue<T>::FUNC_t GetPushFunctor()
	{
		return [this](T val) {buf.push(val);};
		//return std::bind<void(T)>(static_cast<void(queue<T>::*)(const T&)>(&queue<T>::push), &buf, std::placeholders::_1);
	}
};

template<typename T>
class DataBuffer<const T>: public DataBuffer<T>
{

};


}



#endif /* SRC_DATABUFFER_H_ */
