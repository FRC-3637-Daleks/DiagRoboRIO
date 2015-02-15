/*
 * BufferMatrix.h
 *
 *  Created on: Feb 9, 2015
 *      Author: edward
 */

#ifndef SRC_BUFFERMATRIX_H_
#define SRC_BUFFERMATRIX_H_

#include <vector>

#include "DataBuffer.h"
#include "Frame.h"
#include "Buffer.h"
#include "ThreadList.h"

namespace DRR
{

class BufferMatrix: public ThreadList
{
public:
	typedef shared_ptr<Buffer> BUFFER_t;
	typedef vector<BUFFER_t> BUFFER_LIST_TYPE;

private:
	Frame currentFrame;

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
	const typename PushValue<T>::FUNC_t Add(const Frame::KEY_t &key);

public:
	/// Gets the current frame
	const Frame GetCurrentFrame() const {return currentFrame;};
};

}



#endif /* SRC_BUFFERMATRIX_H_ */
