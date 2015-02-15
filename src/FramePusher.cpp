/*
 * FramePusher.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: Edward
 */

#include "FramePusher.h"

namespace DRR
{

const int FramePusher::Do()
{
	int ret = ThreadList::Do();
	ret |= Push();
	return ret;
}

const int FramePusher::Add(const Frame::KEY_t& key, const Frame::DATA_t& d)
{
	Frame::PAIR_t pair(key, d);
	currentFrame.Add(pair);
	return 0;
}



}


