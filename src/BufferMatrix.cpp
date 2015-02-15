/*
 * BufferMatrix.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: edward
 */

#include "BufferMatrix.h"

namespace DRR
{

BufferMatrix::BufferMatrix(const MILLISECONDS p): FramePusher(p)
{
}

BufferMatrix::BufferMatrix(BufferMatrix&& other): FramePusher(std::move(other))
{
}

const int BufferMatrix::Add(const Frame::KEY_t& key, const BUFFER_t buf)
{
	if(buf == nullptr)
		return -1;

	push_back(buf);
	FramePusher::Add(key, buf->Get());
	return 0;
}

template<typename T>
const typename PushValue<T>::FUNC_t BufferMatrix::Add(const Frame::KEY_t& key)
{
	auto buf = DataBuffer<T>::Create();
	Add(key, buf);
	return buf->GetPushFunctor();
}

const int BufferMatrix::Do()
{
	int ret;
	while((ret = FramePusher::Do()) == 0);
	return ret;
}


}


