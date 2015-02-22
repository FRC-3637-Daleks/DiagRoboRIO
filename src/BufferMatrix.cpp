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


const int BufferMatrix::DoAll()
{
	int ret;
	while((ret = ThreadList::DoAll()) == 0);
	return ret | Push();
}


}


