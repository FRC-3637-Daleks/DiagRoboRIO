/*
 * BufferMatrix.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_BUFFERMATRIX_H_
#define SRC_BUFFERMATRIX_H_

#include <vector>

#include "FramePusher.h"
#include "DataBuffer.h"
#include "Buffer.h"

namespace DRR
{

class BufferMatrix: public FramePusher
{
public:
	typedef shared_ptr<Buffer> BUFFER_t;
	typedef vector<BUFFER_t> BUFFER_LIST_TYPE;
protected:
	BufferMatrix(const MILLISECONDS p);
	BufferMatrix(BufferMatrix&& other);

public:
	virtual ~BufferMatrix() {};

public:
	/// Creates a new key,buffer pair and adds it to the list, returning the success of adding it
	const int Add(const Frame::KEY_t &key, const BUFFER_t buf);

	/// Creates a new key,buffer pair and adds it to the list, returning the push functor needed to add to the polling object
	template<typename T>
	const typename PushValue<T>::FUNC_t Add(const Frame::KEY_t &key)
	{
		auto buf = DataBuffer<T>::Create();
		if(Add(key, buf) < 0)
			return [](T t){};	// Error case

		return buf->GetPushFunctor();
	};

public:
	virtual const int DoAll() override;
};

}



#endif /* SRC_BUFFERMATRIX_H_ */
