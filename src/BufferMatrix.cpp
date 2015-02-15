/*
 * BufferMatrix.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: edward
 */

#include "BufferMatrix.h"

namespace DRR
{

BufferMatrix::BufferMatrix(const MILLISECONDS p): ThreadList(p)
{
}

BufferMatrix::BufferMatrix(BufferMatrix&& other): ThreadList(std::move(other)), currentFrame(other.currentFrame)
{
}

const int BufferMatrix::Add(const Frame::KEY_t& key, const BUFFER_t buf)
{
	if(buf == nullptr)
		return -1;

	const Frame::PAIR_t pair(key, buf->Get());
	if(pair.second == nullptr)
		return -1;

	push_back(buf);
	currentFrame.Add(pair);
	return 0;
}

template<typename T>
const typename PushValue<T>::FUNC_t BufferMatrix::Add(const Frame::KEY_t& key)
{
	auto buf = DataBuffer<T>::Create();
	Add(key, buf);
	return buf->GetPushFunctor();
}


}


